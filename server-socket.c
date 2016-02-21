#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

void handleSignal(int signo) {
  if (signo == SIGCHLD) {
    printf("Handle SIGCHILD\n");
  }
}

int main(int argc, char *argv[]) {

  signal(SIGCHLD, handleSignal);

  // even though the man page for socket mentions PF which stands for Protocol Family.
  // AF stands for Address family. This is a historical left over where once they thought
  // that a single protocol family might support multiple address families. Actually, if you
  // look in /usr/include/sys/socket.h and take a look at at PF_INET you'll find:
  // #define PF_INET AF_INET
  //
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd == -1) {
    perror("Cound not create socket");
    exit(EXIT_FAILURE);
  }
  printf("sockfd = %d\n", sockfd);
  // a socket (identified by sockfd here) is assumed to be an active socket, which means that
  // is a client socket that will be used with a connect function call.
  struct in_addr inaddr;
  if (inet_pton(AF_INET, "127.0.0.1", &inaddr) <= 0) {
    perror("Cound not populate struct in_addr");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in saddr = {.sin_family = AF_INET, .sin_port = htons(9999), .sin_addr = htonl(INADDR_ANY)};
  // assign a protocol addres to the socket using bind:
  if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) != 0) {
    perror("Cound not bind to socket");
    exit(EXIT_FAILURE);
  }
  char p[INET_ADDRSTRLEN];
  printf("Bound to %s:%d\n", inet_ntop(AF_INET, &saddr.sin_addr, p, sizeof(p)), ntohs(saddr.sin_port));
  // at this point you should be able to run: $ lsof -i :9999
  // now make the active socket a passive socket so that the kernel should accept incoming request
  // directed to this socket. For this socket the kernel mantains two quees:
  // 1. incomplete connections queue.
  // This queue contains an entry for each SYN that has arrived. The server is waiting for the completion of the
  // three way handshake. The sockets (client connections) in this queue are in the SYN_RCVD state.
  // So, the server receives the initial SYN from the client, creates an new entry in the queue and then responds
  // with the second segment of the threeway handshake (SYN/ACK).
  //
  // 2. completed connections queue.
  // Contains an entry for each client for which the threeway handshake has completed. These client sockets are in the
  // ESTABLISHED state. A server process calls accept the first entry in this queue is returned, or it the queue is empty
  // the process is put to sleep until an entry is placed onto the completed queue.
  // 
  // So what is this backlog argument about?
  // This seems to never have been defined properly accourding to "The Sockets Networking API: UNIX Network Programming Volume 1
  // Second Edition".
  // man 2 listen says:
  // "The backlog parameter defines the maximum length for the queue of pending connections", but does not say if a pending connection
  // is one in the incomplete queue or in the completed queue, or both.
  // Berkley-derived impls add a fudge factor where the backlog value is multiplied by 1.5
  // One thing to not is that if a SYN arrives and queues are full, TCP ignores the SYN and does not send a RST because the issue should
  // be a temporary and the client TCP will restransmit the SYN.
  // My understanding of all this is that the backlog is used to limit the number of completed connections to stop the kernel from accepting
  // new connection requests on a socket when the application process is not accepting them.
  int backlog = 5;
  if (listen(sockfd, backlog) != 0) {
    perror("Cound not listen to socket");
    exit(EXIT_FAILURE);
  }

  for ( ;;) {
    // this sockadd_in struct will be filled in by the kernel upon accepting the socket
    struct sockaddr_in caddr;
    // the size is a value-result parameter, on return it will contain the actual bytes of the returned address.
    socklen_t len = sizeof(caddr);
    printf("acceptings...\n");
    int csockfd = accept(sockfd, (struct sockaddr *) &caddr, &len);
    pid_t pid;
    if ((pid = fork()) == 0) {
      printf("Client Socket (fd = %d) accepted from to %s:%d\n", csockfd, inet_ntop(AF_INET, &caddr.sin_addr, p, sizeof(p)), ntohs(caddr.sin_port));
      write(csockfd, "bajja\n", 7);
      // optionally close the socket descriptor. When this child process exits the kernel will close all open descriptors.
      close(csockfd);
      exit(0);
    }
    // Every socket has a ref count maintained in the file table entry. This is the number of descriptors that are
    // currently open that refer to the socket. After fork() returns both the parent and the child share the csockdf, but
    // the could in the table is now 2. When the call below is executed the count is simply decremented.
    close(csockfd);
  }

  exit(EXIT_SUCCESS);
}

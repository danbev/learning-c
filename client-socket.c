#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int port = 9999;
  char *host = "127.0.0.1";
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  socklen_t len;
  if (sockfd == -1) {
    perror("Could not create socket");
    exit(EXIT_FAILURE);
  }
  printf("Created socket: %d\n", sockfd);
  struct sockaddr_in addr = {};
  // we zero out the members of the addr struct. Like a constructor that initializes all members to
  // their default values, we need to make sure that all members of the struct have default values 
  // and not just garbage that happens to be the members location in memory.
  // bzero(&addr, sizeof(addr)); would also work as I think would initializing the struct:
  // struct sockaddr_in addr = {};
  memset(&addr, 0, sizeof(addr));

  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, host, &addr.sin_addr);

  // so we have an active socket which we can use to connect:
  if (connect(sockfd, (const struct sockaddr *) &addr, sizeof(addr)) != 0) {
    printf("Could not connect. Errno: %d: %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }
  char p[INET_ADDRSTRLEN];
  printf("Connected to host %s:%d\n", inet_ntop(AF_INET, &addr, p, INET_ADDRSTRLEN), ntohs(addr.sin_port));
  char buf[256];
  int n = 0;
  while ( (n = read(sockfd, buf, sizeof(buf))) > 0) {
    printf("Read %d bytes str from server: %s\n", n, buf);
  }
  printf("Last read %d \n", n);
  close(sockfd);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <linux/netlink.h>
#include <linux/rtnetlink.h>

struct nlmsg {
  nlmsghdr hdr;
  rtmsg msg;
  rtattr dst;
};

int main(int argc, char** argv) {
  printf("Routing Table socket example (man 7 rtnetlink)\n");
  int fd;
  addrinfo hints{};                                                                 
  addrinfo *result;                                                               
                                                                                    
  hints.ai_family = AF_UNSPEC;                                                      
  hints.ai_socktype = SOCK_DGRAM;                                                   
                                                                                    
  if (getaddrinfo("127.0.0.1", "7777", &hints, &result) != 0) {
    printf("Could not get addrinfo: %s\n", strerror(errno));
    return -1;
  }

  printf("addrinfo.ai_family: %d\n", result->ai_family);
  printf("addrinfo.ai_socktype: %d\n", result->ai_socktype);
  printf("addrinfo.ai_protocol: %d\n", result->ai_protocol);
  printf("addrinfo.ai_canonname: %s\n", result->ai_canonname);

  struct sockaddr_in* remote = (struct sockaddr_in*)result->ai_addr;
  char *ip = inet_ntoa(remote->sin_addr);
  printf("IP: %s\n", ip);

  struct sockaddr_nl local;
  local.nl_family = AF_NETLINK;

  fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
  if (fd == -1) {
    printf("Could not create RTNETLINK socket: %s\n", strerror(errno));
    close(fd);
    exit(EXIT_FAILURE);
  }

  local.nl_pid = getpid();

  if (bind(fd, (sockaddr *)&local, sizeof(local)) == -1) {
    printf("Could not bind: %s\n", strerror(errno));
  }

  printf("local.nl_family: %d\n", local.nl_family);
  printf("local.nl_pid: %d\n", local.nl_pid);

  // sendmessage
  struct nlmsg m;
  m.hdr.nlmsg_type = RTM_GETROUTE; // Receive information about a network route
  m.hdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
  m.msg.rtm_family = AF_INET; // We are interested in IPV4
  m.dst.rta_type = RTA_DST; // RT Attribute Destination

  /*
  m.dst.rta_len = RTA_LENGTH(sizeof(remote_addr.su.in.sin_addr));
  memcpy(RTA_DATA(&nlmsg.dst), &remote_addr.su.in.sin_addr,
           sizeof(remote_addr.su.in.sin_addr));
  */
  m.hdr.nlmsg_len = NLMSG_LENGTH(sizeof(m.msg) + m.dst.rta_len);

  sockaddr_nl sa{};
  sa.nl_family = AF_NETLINK;

  iovec iov{&m, m.hdr.nlmsg_len};
  msghdr msg{};
  msg.msg_name = &sa;
  msg.msg_namelen = sizeof(sa);
  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;

  ssize_t nwrite;

  do {
    nwrite = sendmsg(fd, &msg, 0);
  } while (nwrite == -1 && errno == EINTR);

  if (nwrite == -1) {
    printf("Could not sendmsg: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  unsigned int buf[8192];
  iovec iov2 = {buf, 8192};

  sockaddr_nl sa2{};
  msghdr msg2{};

  msg2.msg_name = &sa2;
  msg2.msg_namelen = sizeof(sa2);
  msg2.msg_iov = &iov2;
  msg2.msg_iovlen = 1;

  ssize_t nread;

  do {
    nread = recvmsg(fd, &msg2, 0);
  } while (nread == -1 && errno == EINTR);

  if (nread == -1) {
    printf("Could not recvmsg: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  in_addr in;
  for (nlmsghdr *hdr = (nlmsghdr *) buf; NLMSG_OK(hdr, nread); hdr = NLMSG_NEXT(hdr, nread)) {
    printf("header lnmsg_len: %d\n", hdr->nlmsg_len);
    printf("header lnmsg_type: %d\n", hdr->nlmsg_type);
    printf("header lnmsg_flags: %d\n", hdr->nlmsg_flags);
    printf("header lnmsg_seq: %d\n", hdr->nlmsg_seq);
    printf("header lnmsg_pid: %d\n", hdr->nlmsg_pid);

    switch (hdr->nlmsg_type) {
    case NLMSG_DONE:
      printf("No data was returned from kernel.\n");
      exit(EXIT_FAILURE);
    case NLMSG_NOOP:
      continue;
    case NLMSG_ERROR:
      printf("netlink error: %s\n", strerror(((nlmsgerr *)NLMSG_DATA(hdr))->error));
      exit(EXIT_FAILURE);
    }
    int attrlen = hdr->nlmsg_len - NLMSG_SPACE(sizeof(rtmsg)); 
    for (rtattr *rta = ((rtattr *)NLMSG_DATA(hdr) + sizeof(rtmsg)); RTA_OK(rta, attrlen); rta = RTA_NEXT(rta, attrlen)) {
      printf("rta->rta_type: %d\n", rta->rta_type);
      printf("rta->rta_len: %d\n", rta->rta_len);
      if (rta->rta_type != RTA_PREFSRC) {
        continue;
      }
      size_t in_addrlen;

      switch (((rtmsg *)NLMSG_DATA(hdr))->rtm_family) {
      case AF_INET:
        in_addrlen = sizeof(in_addr);
        break;
      case AF_INET6:
        in_addrlen = sizeof(in6_addr);
        break;
      default:
        assert(0);
      }

      if (RTA_LENGTH(in_addrlen) != rta->rta_len) {
        return -1;
      }

      memcpy(&in, RTA_DATA(rta), in_addrlen);
    }

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &in, str, INET_ADDRSTRLEN);
    printf("Address: %s\n", str);
  }


  close(fd);
  return 0;
}

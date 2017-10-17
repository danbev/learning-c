#include <stdio.h>   // fprintf
#include <string.h>  // memset
#include <stdlib.h>  // exit
#include <netdb.h>   // getaddreinfo

int main(int argc, char *argv[]) {
  struct addrinfo hints, *info, *p;
  int res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_NUMERICSERV;
  hints.ai_socktype = SOCK_STREAM;
  // using "0" will segfault if there is not internet connection
  if ((res = getaddrinfo("nodejs.org", "0", &hints, &info)) != 0) {
    fprintf(stderr, "Error: %s, (%d)\n", gai_strerror(res), res);
    exit(1);
  }
  fprintf(stdout, "flags %d\n", info->ai_flags);
  fprintf(stdout, "family %d\n", info->ai_family);
  fprintf(stdout, "socktype %d\n", info->ai_socktype);
  fprintf(stdout, "protocol %d\n", info->ai_protocol);
  fprintf(stdout, "addrlen %d\n", info->ai_addrlen);
  fprintf(stdout, "canonname %s\n", info->ai_canonname);
}

#include <stdio.H>
#include <arpa/inet.h>

int main(void) {
  struct in_addr * a;
  //  ascii to network byte ordered binary
  if (inet_aton("127.0.0.1", a)) {
    // inet_ntoa network byte ordered binary to ascii
    printf("Was valid ip adress: %s\n", inet_ntoa(*a));
  }
  return 0;
}


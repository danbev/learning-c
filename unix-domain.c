#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <strings.h>

int main(int argc, char** argv) {
    int sockfd;
    socklen_t len;
    struct sockaddr_un addr, addr2;
    char *path = "/tmp/danbev";

    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    printf("sockdf: %d\n", sockfd);
    unlink(path);

    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    bind(sockfd, (const struct sockaddr*) &addr, SUN_LEN(&addr));
    
    len = sizeof(addr2);
    getsockname(sockfd, (struct sockaddr*) &addr2, &len);
    printf("bound %s of length %d\n", addr.sun_path, len);
    return 0;
}

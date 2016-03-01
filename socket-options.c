#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // IPPROTO_TCP
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
    printf("main....\n");
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int optvalue = 1;
    socklen_t optlen = sizeof(optvalue);
    setsockopt(fd, SOL_SOCKET, SO_DEBUG, &optvalue, sizeof(optvalue));
    if (getsockopt(fd, SOL_SOCKET, SO_DEBUG, &optvalue, &optlen) == -1) {
        printf("Could not get socket option. Error was %s\n", strerror(errno));
    } else {
        printf("SO_DEBUG value =  %d\n", optvalue);
    }
    return 0;
}

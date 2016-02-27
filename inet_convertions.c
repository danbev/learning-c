#include <stdio.h>
#include <arpa/inet.h>

int main(void) {
    /*
    * the struct in_addr is defined in /usr/include/netinet/in.h which is included
    * by arpa/inet.h. This struct only has a single member which is in_addr_t which is 
    * defined in /usr/include/sys/_types/_in_addr_t.h
    * struct in_addr {
    *     in_addr_t s_addr;
    * }
    *
    * This is only a type def:
    * typedef __uint32_t      in_addr_t;      // base type for internet address 
    */
    struct in_addr a;
    //  presentation to network byte ordered binary
    char p[INET_ADDRSTRLEN];
    if (inet_pton(AF_INET, "127.0.0.1", &a)) {
    // inet_ntoa network byte ordered binary to ascii
        printf("Network byte order: %d\n", a.s_addr);
        inet_ntop(AF_INET, &a, p, sizeof(p));
        printf("Presentation: %s\n", p);
    }

    struct sockaddr_in s = {.sin_family = AF_INET, .sin_port = 9999, .sin_addr = a};
    printf("sockaddre_in.sin_family: %d\n", s.sin_family);
    printf("sockaddre_in.sin_port: %d\n", s.sin_port);
    printf("sockaddre_in.sin_addr.s_addr: %s\n", inet_ntop(AF_INET, &s.sin_addr, p, sizeof(p)));
    struct sockaddr *sa = (struct sockaddr *) &s;
    return 0;
}


#include <netdb.h>
#include <stdio.h>

int main(int argc, char** argv) {
    printf("main...\n");
    // the resolver will make a UDP request to the local name server
    // this might in turn call other name servers
    // the resolver is configured with a system dependant config file, 
    // /etc/resolv.conf
    struct hostent *h = gethostbyname("www.google.com");
    printf("official name: %s \n", h->h_name);
    printf("aliases : %s \n", h->h_aliases);
    return 0;
}

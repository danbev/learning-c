#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: resolv hostname\n");
        return -1;
    }
    // the resolver will make a UDP request to the local name server
    // this might in turn call other name servers
    // the resolver is configured with a system dependant config file, 
    // /etc/resolv.conf
    struct hostent *h = gethostbyname(*(argv+1));
    if (h == NULL) {
        herror("Could not gethostbyname:");
        return -1;
    }
    printf("official name: %s \n", h->h_name);
    for (char **a = h->h_aliases; *a != NULL; a++) {
        printf("alias : %s \n", *a);
    }
    return 0;
}

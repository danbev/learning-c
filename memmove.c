#include <stdio.h>
#include <string.h>

int main () {
   char dest[] = "Fletch";
   const char src[]  = "Rosen";

   printf("Before memmove dest = %s, src = %s\n", dest, src);
   memmove(dest, src, 6);
   printf("After memmove dest = %s, src = %s\n", dest, src);

   return(0);
}

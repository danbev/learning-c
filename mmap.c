#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  int fd, ret;
  size_t len;
  struct stat st;
  char buf[150];

  printf("Reading file mmap.txt\n");
  if ((fd = open("mmap.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) < 0) {
    perror("Error in file opening");
    return EXIT_FAILURE;
  }

  if ((ret = fstat(fd,&st)) < 0) {
      perror("Error in fstat");
      return EXIT_FAILURE;
  }

  len = st.st_size;
  printf("Read length %d\n", len);

  size_t pagesize = getpagesize();

  printf("pagesize: %d\n", pagesize);

  char* v_addr1 = mmap(NULL, len, PROT_READ|PROT_WRITE|PROT_EXEC,
                      MAP_SHARED, fd, 0);

  printf("v_addr1: %p\n", v_addr1);
  printf("v_addr1 value: %s\n", v_addr1);

  char* v_addr2 = mmap(NULL, len, PROT_READ|PROT_WRITE|PROT_EXEC,
                      MAP_SHARED, fd, 0);
  printf("v_addr2: %p\n", v_addr2);
  printf("v_addr2 value: %s\n", v_addr2);

  return 0;
}

//  7f 98 31 32 80 00

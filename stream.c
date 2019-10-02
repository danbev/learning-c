#include <stdio.h>

int main(int argc, char** argv) {
  FILE* fd;
  fd = fopen("data", "w");
  if (!fd) {
    perror ("fopen");
    return 1;
  }

  struct user {
    char name[50];
    int age;
  } u;
  
  struct user users[3] = {
    {"Fletch", 38},
    {"Dr.Rosen", 48},
    {"Sinelinden", 28},
  };

  int n_items = 3;
  if (!fwrite(&users, sizeof (struct user), n_items, fd)) {
    perror ("fwrite");
    return 1;
  }

  if (fclose(fd)) {
    perror ("fclose");
    return 1;
  }

  fd = fopen ("data", "r");
  if (!fd) {
    perror ("fopen");
    return 1;
  }

  n_items = 2;
  struct user read_users[n_items];
  if (!fread(&read_users, sizeof (struct user), n_items, fd)) {
    perror ("fread");
    return 1;
  }

  if (fclose(fd)) {
    perror ("fclose");
    return 1;
  }

  for (int i = 0; i < sizeof(read_users)/sizeof(read_users[0]); i++) {
    printf ("name=\"%s\" age=%d\n", read_users[i].name, read_users[i].age);
  }

  return 0;
}

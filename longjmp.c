#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void func() {
  printf("In func. Calling longjump which uses the saves information prevsiously by setjmp to return control to that point \n");
  // longjmp will restore the registers to the state they were in when setjmp
  // was called.
  longjmp(env, 1);

  printf("Not gonna be printed.\n");
}

int main(int argc, char** argv) {
  if (setjmp(env)) {
    printf("setjmp called. registeres restored to previous state\n");
  } else {
    printf("setjmp called. registeres saved (rsp, rip,...)  and availabe to be rewound\n");
    func();
  }

  return 0;
}

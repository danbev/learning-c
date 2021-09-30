#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void func() {
  printf("In func. Calling longjmp which uses the saves information previously"
     " by setjmp to return control to that point \n");
  // longjmp will restore the registers to the state they were in when setjmp
  // was called. This could be used to simulate a catch block were when some
  // operation went wrong we want control to rewind to the point when setjmp
  // was called.
  longjmp(env, 1);

  printf("Not gonna be printed.\n");

}

int main(int argc, char** argv) {
  // This call will save registers (rsp, rip, ..) into the buffer env. This
  // could be used to implement a try/catch statement where this call would
  // be used 
  if (setjmp(env)) {
    // longjump was called with a return value of 1, which means that control
    // was returned to this point, actually the line above.
    printf("setjmp called. registers restored to previous state\n");
  } else {
    printf("setjmp called. registers saved (rsp, rip,...)  and availabe to be rewound\n");
    func();
  }

  return 0;
}

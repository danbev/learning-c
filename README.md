## Learning C
The sole purpose of this project is to learn c and experiment with various system calls.


### Inheritance
A simple example of how struct inheritance works in C
```shell
$ make inherit
$ ./inherit
```

### kqueue example.
A simple example that uses kqueue to monitor a file named ```test.txt``` for updates and deletion.

```shell
$ make kqueue
$ touch test.txt
$ ./kq
```
You can now update ```test.txt``` to and notice that the program will log that this has happend.
Deleting the file will cause the program to exit.

### pthreads example
A simple example using pthreads
```shell
$ make pthreads
$ ./pthreads
```

### variadic example
Example of using variable arguments to a function
```shell
$ make variadic
$ ./var
```

### Header files on Mac
If you go searching for headers files on Mac and look in ```/usr/include``` you might find that directory empty. 
You'll need to install the command line tools using:
```shell
$ xcode-select --install
```

### Socket server and client
```shell
$ make server-socket
$ ./server-socket
````

```shell
$ make client-socket
$ ./client-socket
```

When the client disconnects there are zombies left on the server side:
```shell
$ ps -t ttys018 -o pid,ppid,tty,stat,args,wchan
  PID  PPID TTY      STAT ARGS            WCHAN
  15071   381 ttys018  Ss   -/bin/bash      -
  89040 15071 ttys018  S+   ./server-socket -
  89044 89040 ttys018  Z+   (server-socket) -
  89054 89040 ttys018  Z+   (server-socket) -
  89057 89040 ttys018  Z+   (server-socket) -
  89060 89040 ttys018  Z+   (server-socket) -
  89062 89040 ttys018  Z+   (server-socket) -
  89064 89040 ttys018  Z+   (server-socket) -
  89066 89040 ttys018  Z+   (server-socket) -
```
These need to be cleand up properly. This was before any signal handlers were added to the example.


### Signals
Just to try out signal handling.

```shell
  $ make signals
  $ ./signals
```

From a different shell run:
```shell
  $ ps -ef |grep signal
  $ kill -USR1 pid
  $ kill -USR2 pid


### c-ares
Just notes about building c-ares

    autoreconf --install
    ./configure
    make


### __attribute__((constructor))
This is can be used to have code run before the main function has been entered.
This works for executables and for dynamically linked libraries. For dynmically 
linked libraries the code will be called before the library is loaded and you
also have the equivalent destructor called when the library gets unloaded (or
when the main has exited).

One case I came accross was that I wanted to link my executable to a static library
and still be able to have the constructors/deconstructors called. But just linking
the executable with the static library will not work. 
There is an example of this called [ctor](./src/ctor.cc). 

Comparing the symbols for the both we see the following:

    $ nm ctor-static
    0000000100000000 T __mh_execute_header
    0000000100000f60 T _main
                     U _printf
                     U dyld_stub_binder
    $ nm ctor
    0000000100000000 T __mh_execute_header
    0000000100000f30 T _main
    0000000100000f60 T _pre_func
                     U _printf
                     U dyld_stub_binder

`ctor-static` does not include the pre_func. This is most probably due to that is not used and hence
not included and not executed. Unreferenced symbols are not included in the output binary.

Is there a way to specify that every thing from the static library be included?

    clang -o ctor-static -Wl,-force_load,libctor.a ctor.c

    $ nm ctor-static
    0000000100000000 T __mh_execute_header
    0000000100000f50 T _main
    0000000100000f30 T _pre_func
                     U _printf
                     U dyld_stub_binder


### Socket address
If we take a look at `sockaddr` in [socket.h](/Applications/Xcode.app//Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/sys/socket.h)
we can find:
```c
struct sockaddr {
  __uint8_t       sa_len;         /* total length */
  sa_family_t     sa_family;      /* [XSI] address family */
  char            sa_data[14];    /* [XSI] addr value (actually larger) */
};
```
Now, take a look at sockaddr_in in `netinet/in.h`:
```c
struct sockaddr_in {
  __uint8_t       sin_len;
  sa_family_t     sin_family;
  in_port_t       sin_port;
  struct  in_addr sin_addr;
  char            sin_zero[8];
};
```
So if you have a pointer to a sockaddr_in you could cast it to a sockaddr:
```
struct sockaddr* addr_;
  struct sockaddr_in addr;
  int port = 8888;
  int r = uv_ip4_addr("127.0.0.1", port, &addr);
  addr_ = (struct sockaddr*) &addr;
  printf("addr_.sa_family:%d\n", addr_->sa_family);
  printf("addr.sin_family:%d\n", addr.sin_family);
```

```c
struct sockaddr_storage {
  __uint8_t       ss_len;         /* address length */
  sa_family_t     ss_family;      /* [XSI] address family */
  char                    __ss_pad1[_SS_PAD1SIZE];
  __int64_t       __ss_align;     /* force structure storage alignment */
  char                    __ss_pad2[_SS_PAD2SIZE];
};
``` 

### Pointer to pointer
Lets say you have a function that needs to reassign a pointer that it is passed.
If the function only takes a pointer to the object this is only a copy of the pointer:
```c
    int* org =  new int{10};
    func(org);

    void fun(int* ptr) { ...};
```

Now, func will get a copy of org (pointing to the same int. But changing that
pointer to point somewhere else does not affect But, if we pass a pointer to the
org the we can update that value which will update our original as we are changing what it
points to:
```c
    void fun(int** ptr) { ...};
```
```
 Pointer        Pointer         Variable
   a              b                int
+-------+      +--------+      +--------+
|address| ---->|address | ---->| value  |
+-------+      +--------+      +--------+
```
```c++
int c = 18;
int* b = &c;
int** a = &b;

std::cout << "c=" << c << '\n';
std::cout << "b=" << b << '\n';
std::cout << "a=" << a << '\n';

std::cout << "a value=" << *a << '\n';
std::cout << "b value=" << *b << '\n';
```
```console
c=18
b=0x7ffee49c605c
a=0x7ffee49c6050

a value=0x7ffee4ebe05c
b value=18
```
Notice that the value in a is the address of b.

Now take the signature of main:
```c++
int main(int argc, char** argv) {
```
```
 argv           char*            
+-------+      +--------+      +--------+
|address| ---->|address | ---->|progname|
+-------+      +--------+      +--------+
```

```console
$ lldb -- ptp one two three
(lldb) expr argv
(char **) $1 = 0x00007ffeefbfefd8
(lldb) memory read -f x -s 8 -c 8 0x00007ffeefbfefb8
0x7ffeefbfefb8: 0x00007ffeefbff288 0x00007ffeefbff2d3
0x7ffeefbfefc8: 0x00007ffeefbff2d7 0x00007ffeefbff2db

(lldb) expr *argv
(char *) $1 = 0x00007ffeefbff288 "/Users/danielbevenius/work/c++/learningc++11/src/fundamentals/pointers/ptp"
```
We can visualize this:
```


      char**                      char*            
+------------------+       +------------------+       +--------+
|0x00007ffeefbfefb8| ----> |0x00007ffeefbff288| ----> |progname|
+------------------+       +------------------+       +--------+
                           +------------------+       +--------+
                           |0x00007ffeefbff2d3| ----> | "one"  |
                           +------------------+       +--------+
                           +------------------+       +--------+
                           |0x00007ffeefbff2d7| ----> | "two"  |
                           +------------------+       +--------+
                           +------------------+       +--------+
                           |0x00007ffeefbff2db| ----> | "three"|
                           +------------------+       +--------+
```
So we can see that we have a pointer char** that contains `0x00007ffeefbff288`.
Remember that this memory location only contains pointers, and the type of pointers
it can store are char*, which are of size 8 bits on my machine. We can change it
to point to other char*, but the nice thing is that we can simply increment it
to go through all of them:
```console
(lldb) expr *(argv+1)
(char *) $16 = 0x00007ffeefbff2d3 "one"
(lldb) expr *(argv+2)
(char *) $17 = 0x00007ffeefbff2d7 "two"
two
(lldb) expr *(argv+3)
(char *) $18 = 0x00007ffeefbff2db "three"
```

Looking at the memory layout again:
```console
(lldb) memory read -f x -s 8 -c 4 0x00007ffeefbfefb8
0x7ffeefbfefb8: 0x00007ffeefbff288 0x00007ffeefbff2d3
0x7ffeefbfefc8: 0x00007ffeefbff2d7 0x00007ffeefbff2db
```
Now, `argv` has the memory address `0x7ffeefbfefb8` starts off containing the 
memory address `0x00007ffeefbff2888`. Using addition and subtraction of we change
the address it contains. By using +1 we are saying that is should point to a
memory address of the current plus 8 (as these are char* (pointers) of size 8):
```console
(lldb) expr *(argv+1)
(char *) $28 = 0x00007ffeefbff2d3 "one"
So, we should be able to read `0x00007ffeefbff2d3`:
(lldb) memory read  -f C -s 1 -c 3 0x00007ffeefbff2d3
0x7ffeefbff2d3: one
(lldb) memory read  -f C -s 1 -c 3 0x00007ffeefbff2d7
0x7ffeefbff2d7: two
(lldb) memory read  -f C -s 1 -c 5 0x00007ffeefbff2db
0x7ffeefbff2db: three
```

#### writev
```c
struct iovec {
  char* iov_base;  // Base address
  size_t iov_len;  
};
```

### Ringbuffer


### perror
[perror.c](perror.c) contains an example of using perror.
```
#include <errno.h>
```
The error codes can be found in `/usr/include/sys/errno.h`.

`sys_nerr` is defined in `stdlib.h`
`sys_errlist` is an array of character strings that provides a mapping from errno 
values to error messages
```console
$ man 3 perror
```

### FILE
StandardI/O routines do not operate directly on file descriptors but use their
own unique identifier (file pointer):
```
typedef FILE:
```
This is defined in `/usr/include/_stdio.h`
Standard I/O was originally written as macros. Not only `FILE` but all of the
methods in the library were implemented as a set of macros. The style at the 
time, which remains common to this day, is to give macros all-caps names. As
the C language progressed and standard I/O was ratified as an official part,
most of the methods were reimplemented as proper functions and FILE became
 a typedef. But the uppercase remains.
`FILE` is an opaque data type so it's implementation is hidden, so we don't know
how it is implemented and we only use it to pass into functions that accept it.



The function `fdopen()` converts an already open file descriptor (fd) to a stream:

### fwrite
```c
size_t fwrite (void *buf, size_t size, size_t nr, FILE *stream);
on my mac:
size_t fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
```
Example can be found in [stream.c](stream.c).


### restrict keyword
Is mainly used in pointer declarations as type qualifiers.
It doesn’t add any new functionality. It is only a way for programmer to inform
about an optimizations that compiler can make
When we use restrict with a pointer ptr, it tells the compiler that ptr is the
only way to access the object pointed by it and compiler doesn’t need to add 
any additional checks.


### API
The API acts only to ensure that if both pieces of software follow the API, 
they are source compatible; that is, that the user of the API will successfully
compile against the implementation of the API.

### ABI
ABIs are concerned with issues such as calling conventions, byte ordering, 
register use, system call invocation, linking, library behavior, and the binary
object format. The calling convention, for example, defines how functions are
invoked, how arguments are passed to functions, which registers are preserved
and which are mangled, and how the caller retrieves the return value.


### LD_LIBRARY_PATH, LIBRARY_PATH
`LIBRARY_PATH` is searched at link time.

`LD_LIBRARY_PATH` is searched when the program starts.  On macos this would
instead be `DYLD_LIBRARY_PATH` as the dynamic linker is `dyld`.
```console
$ man dyld
```

### CMake
There is a bacic cmake example in [cmake-example](cmake-example).

To configure cmake:
```console
$ mkdir -p build
$ cd build
$ cmake ..
-- The C compiler identification is AppleClang 11.0.0.11000033
-- Check for working C compiler: /Users/danielbevenius/work/ccache/ccache
-- Check for working C compiler: /Users/danielbevenius/work/ccache/ccache -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/danielbevenius/work/c/learning-c/cmake-example/build
```
This will generate the cmake configuration in the build director. This can also
be done using `cmake -H. -Bbuild`.

We can now compile, staying in the build directory:
```console
$ cmake --build .
Scanning dependencies of target hello
[ 50%] Building C object CMakeFiles/hello.dir/src/hello.c.o
[100%] Linking C executable hello
[100%] Built target hello
```
```console
$ ./hello
cmake example...
```

cmake will create a Makefile by default on mac. We can list the targets using:
```console
$ cmake --build . --target help
The following are some of the valid targets for this Makefile:
... all (the default if no target is provided)
... clean
... depend
... rebuild_cache
... edit_cache
... hello
... src/hello.o
... src/hello.i
... src/hello.s
```
So we can do:
```console
$ make clean
$ make hello
```
or :
```console
$ cmake --build . --target hello
```

### System calls
```console
$ man -k . | grep '(2)'
```


### dtruss 
`main` only has a main function that returns 22:
```console
$ sudo dtruss main
SYSCALL(args) 		 = return
open("/dev/dtracehelper\0", 0x2, 0xFFFFFFFFE4D91D00)		 = 3 0
ioctl(0x3, 0x80086804, 0x7FFEE4D91B10)		 = 0 0
close(0x3)		 = 0 0
access("/AppleInternal/XBS/.isChrooted\0", 0x0, 0x0)		 = -1 Err#2
bsdthread_register(0x7FFF76582400, 0x7FFF765823F0, 0x2000)		 = 1073742047 0
sysctlbyname(kern.bootargs, 0xD, 0x7FFEE4D90F60, 0x7FFEE4D90F50, 0x0)		 = 0 0
issetugid(0x0, 0x0, 0x0)		 = 0 0
ioctl(0x2, 0x4004667A, 0x7FFEE4D90764)		 = 0 0
mprotect(0x10AE73000, 0x1000, 0x0)		 = 0 0
mprotect(0x10AE7A000, 0x1000, 0x0)		 = 0 0
mprotect(0x10AE7B000, 0x1000, 0x0)		 = 0 0
mprotect(0x10AE82000, 0x1000, 0x0)		 = 0 0
mprotect(0x10AE71000, 0x90, 0x1)		 = 0 0
mprotect(0x10AE83000, 0x1000, 0x1)		 = 0 0
mprotect(0x10AE71000, 0x90, 0x3)		 = 0 0
mprotect(0x10AE71000, 0x90, 0x1)		 = 0 0
getentropy(0x7FFEE4D908B0, 0x20, 0x0)		 = 0 0
getpid(0x0, 0x0, 0x0)		 = 19135 0
stat64("/AppleInternal\0", 0x7FFEE4D913D0, 0x0)		 = -1 Err#2
csops(0x4ABF, 0x7, 0x7FFEE4D90F00)		 = -1 Err#22
proc_info(0x2, 0x4ABF, 0xD)		 = 64 0
csops(0x4ABF, 0x7, 0x7FFEE4D90740)		 = -1 Err#22
```

### autotools

#### autoconf
Is responsible for translating configure.ac which is a mix of m4 and shell
scripting and producing a configure shell script.

configure.ac is written in M4sh (based on both m4 and sh hence the name). The
syntax is very similar to sh but with autoconf macros thown into the mix.

`AS_IF` 
```sh
AS_IF([test], [true], [false])
```
This will be translated into:
```sh
if test; then
  true
else
  false
fi
```

If we have the need for if..then..elif..else:
```sh
AS_IF([test1], [true], [test2], [true2], [false])
```
Will be translated into:
```sh
if test1; then
  true
elif test2; then
  true2
else
  false
fi
```

We can also have case statements:
```sh
AS_CASE([$variable], [foo*], [run1], [bar*], [run2], [catchall])

case $variable in
  foo*) run1 ;;
  bar*) run2 ;;
  *) catchall ;;
esac
```

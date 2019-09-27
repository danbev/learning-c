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


### Ringbuffer


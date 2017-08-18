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



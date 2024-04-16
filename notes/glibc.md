## GNU C Library (glibc)
Is a C library which contains functions that provide low-level functionality to
the operating system which are available on all Linux systems.

### Compability
``` 
  Build system                     Target system 1
  app [glibc version 2.31]  ---->  app [glibc version 2.35]  OK

  Build system                     Target system 2
  app [glibc version 2.35]  ---->  app [glibc version 2.31]  Not OK
```
The above is trying to convey that an application built on a system and linking
to glibc 2.31 can be run on a system that has a later version of glibc.
But, if the application is built/linked with a later version of glibc than the
target system has then this is incompatible.

On solution to this is to build the application on a system that has an older
version of glibc which should then work alright on systems as their version of
glibc is most probably newer.

### Finding the glibc version
Finding the version of glibc on a system:
```console
$ ldd floats
	linux-vdso.so.1 (0x00007ffe5dd2c000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f97f5121000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f97f5326000)
```
Then we can use the following command to find the version of glibc:
```console
$ /lib64/libc.so.6 --version
GNU C Library (GNU libc) stable release version 2.38.
Copyright (C) 2023 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
Compiled by GNU CC version 13.2.1 20231205 (Red Hat 13.2.1-6).
libc ABIs: UNIQUE IFUNC ABSOLUTE
Minimum supported kernel: 3.2.0
For bug reporting instructions, please see:
<https://www.gnu.org/software/libc/bugs.html>.
```

### Ubuntu versions
Lets find the version of glibc on Ubuntu 20.04:
```console
$ docker pull ubuntu:20.04
$ docker run -it --rm ubuntu:20.04 /bin/bash

root@7c7c87971494:/# cat /etc/os-release 
NAME="Ubuntu"
VERSION="20.04.6 LTS (Focal Fossa)"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 20.04.6 LTS"
VERSION_ID="20.04"
VERSION_CODENAME=focal
UBUNTU_CODENAME=focal

root@7c7c87971494:/# /lib/x86_64-linux-gnu/libc.so.6 --version
GNU C Library (Ubuntu GLIBC 2.31-0ubuntu9.14) stable release version 2.31.
Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
Compiled by GNU CC version 9.4.0.
libc ABIs: UNIQUE IFUNC ABSOLUTE
For bug reporting instructions, please see:
<https://bugs.launchpad.net/ubuntu/+source/glibc/+bugs>.
```

And lets find the version of glibc on Ubuntu 22.04.4:
```console
$ docker run -ti --rm ubuntu /bin/bash
root@4fb11ead643d:/# cat /etc/os-release 
PRETTY_NAME="Ubuntu 22.04.4 LTS"
NAME="Ubuntu"
VERSION_ID="22.04"
VERSION="22.04.4 LTS (Jammy Jellyfish)"
VERSION_CODENAME=jammy

root@4fb11ead643d:/# /lib/x86_64-linux-gnu/libc.so.6 --version
GNU C Library (Ubuntu GLIBC 2.35-0ubuntu3.6) stable release version 2.35.
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
Compiled by GNU CC version 11.4.0.
libc ABIs: UNIQUE IFUNC ABSOLUTE
For bug reporting instructions, please see:
<https://bugs.launchpad.net/ubuntu/+source/glibc/+bugs>.
````
So we can see that Ubuntu 20.04 has glibc version 2.31 and Ubuntu 22.04 has
glibc version 2.35.

### Demonstrating the compability issue
This section attemps to demonstrate the compability issue with glibc versions.

First, we will build a docker container for Ubuntu 20.04:
```console
$ cd glibc-exploration
$ docker build . -t ununtu-c-20-04
```

Let run this container and build a simple application:
```console
$ docker run -it -v $(pwd)/work:/workspace:Z ununtu-c-20-04

root@4d805088d2d2:/workspace# g++ -o main-20 src/main.cpp 
root@4d805088d2d2:/workspace# ./main-20 
glibc exploration..
root@4d805088d2d2:/workspace# file main-20 
main-20: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=37c62719fab40952ed816e1bd6954d4d15c0cc06, for GNU/Linux 3.2.0, not stripped
```

Now, lets to the same but for Ubuntu 22.04:
```console
$ docker build -f Dockerfile_22 . -t ununtu-c-22-04
```

```
$ docker run -it -v $(pwd)/work:/workspace:Z ununtu-c-22-04
g++ -o main-22 src/main.cpp
```

So with those in place and if we attach to the ubuntu 22 container, we can
try running the binary that was built on the ubuntu 20 container:
```console
$ docker run -it -v $(pwd)/work:/workspace:Z ununtu-c-22-04
root@10940b54c095:/workspace# ./main-20
glibc exploration..

root@10940b54c095:/workspace# ./main-22
glibc exploration..
```
This is running an application that was linked with an older version of glibc
which we claimed above should work and it does.

Now, lets attach to the ubuntu 20 container and try running the binaries:
```console
$ docker run -it -v $(pwd)/work:/workspace:Z ununtu-c-20-04
root@63c852c16891:/workspace# ./main-20 
glibc exploration..

root@63c852c16891:/workspace# ./main-22 
./main-22: /lib/x86_64-linux-gnu/libc.so.6: version `GLIBC_2.34' not found (required by ./main-22)
```
And I believe this is the compability issue that we were talking about.

### Using musl instead of glibc
musl is an alternative to glibc which is designed to be lightweight and
efficient. It can enable statically linked binaries to be built and run on
different systems without the compability issues that glibc has (even statically
linked executables).

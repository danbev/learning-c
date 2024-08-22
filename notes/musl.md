## musl


### building 
Building https://github.com/richfelker/musl-cross-make:
```console
$ git clone https://github.com/richfelker/musl-cross-make
$ cd musl-cross-make
$ make TARGET=x86_64-linux-musl
$ make TARGET=x86_64-linux-musl install
```
This will install into `output`.

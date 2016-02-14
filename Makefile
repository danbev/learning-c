all: kq inherit pthreads var memset memcmp inet_conv fs

kq: kqueue.c
	clang -o kq -g kqueue.c

inherit: inherit.c
	clang -o inherit -g inherit.c

pthreads: pthreads.c
	clang -pthread -o pthreads -g pthreads.c

var: variadic.c
	clang -o var -g variadic.c

memset: memset.c
	clang -o memset -g memset.c

memcmp: memcmp.c
	clang -o memcmp -g memcmp.c

inet_conv: inet_convertions.c
	clang -o inet_conv -g inet_convertions.c

fs: fs.c
	clang -o fs -g fs.c
  
.PHONY: clean

clean: 
	rm -f kq inherit pthreads var memset memcmp inet_conv fs

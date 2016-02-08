all: kq inherit pthreads var

kq: kqueue.c
	clang -o kq -g kqueue.c

inherit: inherit.c
	clang -o inherit -g inherit.c

pthreads: pthreads.c
	clang -pthread -o pthreads -g pthreads.c

var: variadic.c
	clang -o var -g variadic.c
  
.PHONY: clean

clean: 
	rm -f kq inherit pthreads var

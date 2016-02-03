all: kq inherit pthreads

kq: kqueue.c
	clang -o kq -g kqueue.c

inherit: inherit.c
	clang -o inherit -g inherit.c

pthreads: pthreads.c
	clang -pthread -o pthreads -g pthreads.c
  
.PHONY: clean

clean: 
	rm -f kq inherit pthreads

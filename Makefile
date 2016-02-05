all: kq inherit pthreads ellipsis

kq: kqueue.c
	clang -o kq -g kqueue.c

inherit: inherit.c
	clang -o inherit -g inherit.c

pthreads: pthreads.c
	clang -pthread -o pthreads -g pthreads.c

ellipsis: ellipsis.c
	clang -o el -g ellipsis.c
  
.PHONY: clean

clean: 
	rm -f kq inherit pthreads ellipsis

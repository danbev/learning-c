all: kq fioclex inherit pthreads var memset memcmp inet_conv fs cp server-socket client-socket signals select socket-options resolv strings array unix-domain macro function-pointer pthread-mutex pthread-sema pthread-sigwait sigaction

kq: kqueue.c
	clang -o kq -g kqueue.c

inherit: inherit.c
	clang -o inherit -g inherit.c

var: variadic.c
	clang -o var -g variadic.c

memset: memset.c
	clang -o memset -g memset.c

memcmp: memcmp.c
	clang -o memcmp -g memcmp.c

inet_conv: inet_convertions.c
	clang -o inet_conv -g inet_convertions.c

cp: cp.c
	clang -o cp -g cp.c

fs: fs.c
	clang -o fs -g fs.c

fioclex: fioclex.c
	clang -o fioclex -g fioclex.c

server-socket: server-socket.c
	clang -o server-socket -g server-socket.c

client-socket: client-socket.c
	clang -o client-socket -g client-socket.c

signals: signals.c
	clang -o signals -g signals.c

select: select.c
	clang -o select -g select.c

socket-options: socket-options.c
	clang -o socket-options -g socket-options.c

resolv: resolv.c
	clang -o resolv -g resolv.c

strings: strings.c
	clang -o strings -g strings.c

array: array.c
	clang -o array -g array.c

unix-domain: unix-domain.c
	clang -o unix-domain -g unix-domain.c

macro: macro.cc
	clang -o macro -g macro.cc -D"DEF1"=0 -D"DEF2"=0

macropre: macro.cc
	clang -E -g macro.cc

function-pointer: function-pointer.c
	clang -o function-pointer -g function-pointer.c

pthread-mutex: pthread-mutex.c
	clang -o pthread-mutex -g pthread-mutex.c

pthread-sema: pthread-sema.c
	clang -o pthread-sema -g pthread-sema.c

pthread-sigwait: pthread-sigwait.c
	clang -o pthread-sigwait -g pthread-sigwait.c

pthreads-once: pthreads-once.c
	clang -pthread -o pthreads-once -g pthreads-once.c

sigaction: sigaction.c
	clang -o sigaction -g sigaction.c

ctor: ctor.c
	clang -c ctor2.c -o ctor2.o
	ar ru libctor.a ctor2.o
	#clang -o ctor-static -g ctor.c -L. -lctor
	clang -o ctor-static -Wl,-force_load,libctor.a ctor.c
	#clang -o ctor-static -Wl,--force_load,libctor.a ctor.c
	clang -o ctor -g ctor.c ctor2.c

no-return: no-return.c
	clang -o $@ -g $<

.PHONY: clean tcpdump

clean: 
	rm -f fioclex kq inherit pthreads-once var memset memcmp inet_conv fs cp client-socket server-socket select signals socket-options resolv strings array unix-domain macro function-pointer pthread-sema pthread-sigwait sigaction

tcpdump: 
	sudo tcpdump -nnvvXS -i lo0 port 9999


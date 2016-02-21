all: kq inherit pthreads var memset memcmp inet_conv fs cp server-socket socket-client signals

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

cp: cp.c
	clang -o cp -g cp.c

fs: fs.c
	clang -o fs -g fs.c

server-socket: server-socket.c
	clang -o server_socket -g server-socket.c

socket-client: socket-client.c
	clang -o socket-client -g socket-client.c

signals: signals.c
	clang -o signals -g signals.c

.PHONY: clean tcpdump

clean: 
	rm -f kq inherit pthreads var memset memcmp inet_conv fs cp server_socket

tcpdump: 
	sudo tcpdump -nnvvXS -i lo0 port 9999


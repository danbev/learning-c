all: kq fioclex inherit pthreads var memset memcmp inet_conv fs cp server-socket client-socket signals select socket-options resolv strings array unix-domain macro function-pointer pthread-mutex pthread-sema pthread-sigwait sigaction

kq: kqueue.c
	${CC} -o kq -g kqueue.c

inherit: inherit.c
	${CC} -o inherit -g inherit.c

var: variadic.c
	${CC} -o var -g variadic.c

memset: memset.c
	${CC} -o memset -g memset.c

memcmp: memcmp.c
	${CC} -o memcmp -g memcmp.c

inet_conv: inet_convertions.c
	${CC} -o inet_conv -g inet_convertions.c

cp: cp.c
	${CC} -o cp -g cp.c

fs: fs.c
	${CC} -o fs -g fs.c

fioclex: fioclex.c
	${CC} -o fioclex -g fioclex.c

server-socket: server-socket.c
	${CC} -o server-socket -g server-socket.c

client-socket: client-socket.c
	${CC} -o client-socket -g client-socket.c

signals: signals.c
	${CC} -o signals -g signals.c

select: select.c
	${CC} -g -o $@ $<

socket-options: socket-options.c
	${CC} -o socket-options -g socket-options.c

resolv: resolv.c
	${CC} -o resolv -g resolv.c

strings: strings.c
	${CC} -o strings -g strings.c

array: array.c
	${CC} -o array -g array.c

unix-domain: unix-domain.c
	${CC} -o unix-domain -g unix-domain.c

macro: macro.cc
	${CC} -o macro -g macro.cc -D"DEF1"=0 -D"DEF2"=0

macropre: macro.cc
	${CC} -E -g macro.cc

function-pointer: function-pointer.c
	${CC}++ -std=c++11 -o function-pointer -g function-pointer.c

pthread-mutex: pthread-mutex.c
	${CC} -o pthread-mutex -g pthread-mutex.c

pthread-sema: pthread-sema.c
	${CC} -o pthread-sema -g pthread-sema.c

pthread-sigwait: pthread-sigwait.c
	${CC} -o pthread-sigwait -g pthread-sigwait.c

pthreads-once: pthreads-once.c
	gcc -pthread -o pthreads-once -g pthreads-once.c

pthreads-once-deadlock: pthreads-once-deadlock.c
	gcc -pthread -o $@ -g $<

sigaction: sigaction.c
	${CC} -o sigaction -g sigaction.c

ctor: ctor.c
	${CC} -c ctor2.c -o ctor2.o
	ar ru libctor.a ctor2.o
	#${CC} -o ctor-static -g ctor.c -L. -lctor
	${CC} -o ctor-static -Wl,-force_load,libctor.a ctor.c
	#${CC} -o ctor-static -Wl,--force_load,libctor.a ctor.c
	${CC} -o ctor -g ctor.c ctor2.c

no-return: no-return.c
	${CC} -o $@ -g $<

addrinfo: addrinfo.c
	${CC} -o $@ -g $<

ringbuffer: ringbuffer.c
	${CC} -o $@ -g $<

.PHONY: clean tcpdump

clean: 
	rm -f fioclex kq inherit pthreads-once var memset memcmp inet_conv fs cp client-socket server-socket select signals socket-options resolv strings array unix-domain macro function-pointer pthread-sema pthread-sigwait sigaction ringbuffer

tcpdump: 
	sudo tcpdump -nnvvXS -i lo0 port 9999

.PHONY: print
print: 
ifeq ($(something),"bajja")
	@echo $(something)
else
	@echo "not defined"
endif

something:="bajja"

define run-args
@echo "run-args args is $1"
endef

.PHONY: args
args:
	@echo "BUILDTYPE=$(BUILDTYPE:%=Release)"
	$(call run-args,"bajja")

.PHONY: node
node: deps
	@echo "running node..."

deps: 
	@echo "deps..."

echo: 
	echo $(jobs) $*

file-dep: somefile
	@echo "running $@..."

somefile: somevar=Release
somefile: 
	@echo "from second somefile target. somevar=$(somevar)" $@

libev: libev.c
	${CC} -lev -o $@ -g $<

.PHONY: check
check: tests/first_test.c
	${CC} -O0 -g $< first.c -I. -o tests/first_test -lcunit

OPTIONAL_VAR ?= Something
.PHONY: warn
warn:
	$(warning Just an example of a warnings which can be used for debugging)
	@echo ${OPTIONAL_VAR}

im-example: 123456.intermediate

.INTERMEDIATE: 123456.intermediate
123456.intermediate: depfile
	@echo "im.dep running intermedate...."
	touch 123456.intermediate

depfile: 
	@echo "making depfile..."

comma: comma.c
	${CC} -o $@ -g $<

asan-heap: asan-heap-use-after-freed.c
	${CC} -g3 -o $@ -fsanitize=address $<

tm: tm.c
	${CXX} -Wall -fgnu-tm -O3 -o $@ $<

fem: fem.c
	${CXX} -Wall -fgnu-tm -O3 -o $@ $<

netlink: netlink.c
	${CXX} -Wall -fgnu-tm -O3 -o $@ $<

epoll: epoll.c
	${CC} -g -o $@ $<

longjmp: longjmp.c
	${CC} -g -o $@ $<

bitop: bitop.c
	${CC} -g -o $@ $<

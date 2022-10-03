CFLAGS +=-I/usr/include/dbus-1.0/ -I/usr/lib64/dbus-1.0/include/ -L/usr/lib64/ -ldbus-1

out/%: src/%.c | out
	${CC} ${CFLAGS} $< -g -o $@ 

.PHONY: out
out:
	@mkdir -p out

.PHONE: clean
clean:
	${RM} -rf out

.PHONE: cp-dbus-config
cp-dbus-config:
	@sudo cp dbus.conf /etc/dbus-1/system.d

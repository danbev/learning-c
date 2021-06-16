main: libmain.a libutil.a main.cc libdso.so
	#${CXX} -s -L. -o $@ main.cc -lmain -lmain
	#${CXX} -s -L. -o $@ main.cc -lutil -lmain
	#${CXX} -s -L. -o $@ main.cc -lmain -ldso -Wl,-rpath,.
	#${CXX} -s -L. -o $@ main.cc -lmain -ldso -Wl,-rpath,.
	${CXX} -s -L. -o $@ main.cc -ldso -lmain -Wl,-rpath,.

libmain.a: mainlib.o
	${AR} rc -o $@ $<

mainlib.o: mainlib.cc
	${CXX} -c -o $@ $<

libutil.a: util.o
	${AR} rc -o $@ $<

main.o: util.cc
	${CXX} -c -o $@ $<

libdso.so: dso.o
	#${CXX} -Wl,--version-script=dso.ld --shared $< -o $@ -Wl,-Bsymbolic
	${CXX} -Wl,--version-script=dso.ld --shared $< -o $@ -rdynamic

dso.o: dso.cc
	${CXX} -fPIC -o $@ -c $<

.PHONY clean:
clean:
	${RM} *.a *.so libdso.so *.o main
	

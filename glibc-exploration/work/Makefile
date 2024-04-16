CXXFLAGS = -static-libstdc++ -static-libgcc
LDFLAGS = -static
CXX = g++

main-static: src/main.cpp
	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@

MUSL=/home/danielbevenius/work/c/musl-cross-make
MUSL_CXX=${MUSL}/output/bin/x86_64-linux-musl-g++
main-musl: CXX = ${MUSL_CXX}
main-musl: src/main.cpp
	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@

CXXFLAGS = -static-libstdc++ -static-libgcc
LDFLAGS = -static
CXX = g++

main: src/main.cpp
	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@

MUSL=/home/danielbevenius/work/c/musl-cross-make
MUSL_CXX=${MUSL}/output/bin/x86_64-linux-musl-g++
main-musl: CXX = ${MUSL_CXX}
main-musl: src/main.cpp
	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@

.PHONY: app-image
app-image: MAIN=main
app-image: APP_NAME=Main
app-image: main app-image-build

.PHONY: app-image-musl
app-image-musl: MAIN=main-musl
app-image-musl: APP_NAME=Main_Musl
app-image-musl: main-musl app-image-build

.PHONY: app-image-build
app-image-build:
	mkdir -p Main.AppDir/usr/share/applications
	mkdir -p Main.AppDir/usr/share/icons/hicolor/scalable/apps
	mkdir -p Main.AppDir/usr/bin
	cp Main.desktop Main.AppDir/
	cp main.svg Main.AppDir/
	cp ${MAIN} Main.AppDir/usr/bin/
	cp AppRun Main.AppDir/
	./appimagetool-x86_64.AppImage Main.AppDir
	mv Main-x86_64.AppImage ${APP_NAME}.AppImage
	chmod 744 ${APP_NAME}.AppImage

.PHONY: clean
clean:
	rm -rf Main.AppDir
	rm -f main main-musl

.PHONY: install-musl
install-musl:
	sudo dnf install musl-gcc

.PHONY: install-static-lib
install-static-lib:
	sudo dnf install libstdc++-static

.PHONY: install-appimagetool
install-appimagetool:
	wget https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage
	chmod +x appimagetool-x86_64.AppImage

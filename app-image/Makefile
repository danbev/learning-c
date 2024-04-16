
main: src/main.cpp
	g++ -static-libstdc++ -static-libgcc $< -o $@

install-static-lib:
	sudo dnf install libstdc++-static

.PHONY: app-image
app-image: main
	mkdir -p Main.AppDir/usr/share/applications
	mkdir -p Main.AppDir/usr/share/icons/hicolor/scalable/apps
	mkdir -p Main.AppDir/usr/bin
	cp Main.desktop Main.AppDir/
	cp main.svg Main.AppDir/
	cp main Main.AppDir/usr/bin/
	cp AppRun Main.AppDir/
	./appimagetool-x86_64.AppImage Main.AppDir
	chmod 744 Main-x86_64.AppImage

.PHONY: install-appimagetool
install-appimagetool:
	wget https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage
	chmod +x appimagetool-x86_64.AppImage

.PHONY: clean
clean:
	rm -rf Main.AppDir
	rm -f main

MAIN=maker.sh
LIBS=./clibs/*.h
LD2=linker.c

all:
	@echo "Building..."
	@mkdir -p dist
	@cp -r $(LIBS) dist/lib
	@cp -r $(MAIN) dist
	@mv dist/maker.sh dist/nmake
	@chmod +x dist/nmake
	gcc -o $(LD2) dist/ld2

install:
	@echo "Installing..."
	@cp dist/nmake /usr/bin/nmake
	@cp $(LD2) /usr/bin/ld2
	@cp -r dist/lib /usr/lib/nmake
	@echo "Add /usr/bin/nmake to your PATH"

uninstall:
	@echo "Uninstalling..."
	@rm -rf /usr/bin/nmake
	@rm -rf /usr/bin/ld2
	@rm -rf /usr/lib/nmake

clean:
	@echo "Cleaning..."
	@rm -rf dist
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lX11
TARGET := build/fromia-gui
MAIN_SRC := main.cxx
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

all:
	@if [ ! -d build ]; then mkdir build; fi
	g++ -o build/fromia-gui main.cxx -Wall -Wextra -lX11 -std=c++11
	@echo "Build successful!"

apps: all
	@echo "Building apps..."
	$(CC) -o build/FWorkspace FileBrowser/main.c $(CFLAGS) $(LDFLAGS)
	$(CC) -o build/TextEdit GEditor/main.c $(CFLAGS) $(LDFLAGS)
	gcc -o build/Terminal GTerm/main.cpp $(CFLAGS) $(LDFLAGS) -std=c++11
	@echo "Apps built successfully!"
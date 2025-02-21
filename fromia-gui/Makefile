CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lX11
TARGET := build/fromia-gui
MAIN_SRC := main.cpp
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

all:
	@mkdir build
	$(CC) -o $(TARGET) $(MAIN_SRC) $(OBJ) $(CFLAGS) $(LDFLAGS) -std=c++
	@echo "Build successful!"

apps: all
	@echo "Building apps..."
	$(CC) -o build/FWorkspace FileBrowser/main.c $(CFLAGS) $(LDFLAGS)
	$(CC) -o build/TextEdit GEditor/main.c $(CFLAGS) $(LDFLAGS)
	$(CC) -o build/Terminal GTerm/main.cpp $(CFLAGS) $(LDFLAGS) -std=c++
	@echo "Apps built successfully!"
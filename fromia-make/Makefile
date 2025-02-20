# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Target binary
TARGET := fromia-make

# Source files
SRCS := main.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Install directories
PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
INCLUDEDIR := $(PREFIX)/include/Fromia

# Header files directory (relative to the Makefile)
HEADER_SRC := ../clibs

# Find all header files in HEADER_SRC
HEADERS := $(wildcard $(HEADER_SRC)/*.h)

# Build rules
.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build successful! -> $(TARGET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install: $(TARGET)
	@echo "Installing $(TARGET) to $(BINDIR)..."
	@mkdir -p $(BINDIR)
	@cp $(TARGET) $(BINDIR)/
	@chmod 755 $(BINDIR)/$(TARGET)
	@echo "$(TARGET) has been installed successfully!"

	@echo "Installing headers to $(INCLUDEDIR)..."
	@mkdir -p $(INCLUDEDIR)
	@cp $(HEADERS) $(INCLUDEDIR)/
	@chmod 644 $(INCLUDEDIR)/*.h
	@echo "Headers have been installed successfully to $(INCLUDEDIR)!"

uninstall:
	@echo "Uninstalling $(TARGET) from $(BINDIR)..."
	@rm -f $(BINDIR)/$(TARGET)
	@echo "$(TARGET) has been removed!"

	@echo "Removing installed headers from $(INCLUDEDIR)..."
	@rm -rf $(INCLUDEDIR)
	@echo "Headers have been removed from $(INCLUDEDIR)!"

clean:
	@rm -f $(OBJS) $(TARGET)
	@echo "Cleaned up build files."

#!/bin/bash

# Function to print status of a dependency
check_dependency() {
    local name="$1"
    local msg="$2"

    echo -n "Checking for $name... "
    if eval "$msg"; then
        echo "found"
    else
        echo "not found"
    fi
}

# Check for libobjc++ using ldconfig to see if its shared library is present.
echo -n "Checking for libobjc++ library... "
if ldconfig -p | grep -q libobjc++; then
    echo "found"
else
    echo "not found"
fi

# Check if gcc is installed
if command -v gcc >/dev/null 2>&1; then
    echo "gcc found"
else
    echo "gcc not found"
fi

# Check if make is installed
if command -v make >/dev/null 2>&1; then
    echo "make found"
else
    echo "make not found"
fi

make -f ./fromia-make/Makefile
sudo make -f ./fromia-make/Makefile install

# Check if the installation was successful
if command -v fromia-make >/dev/null 2>&1; then
    echo "Installation successful"
else
    echo "Installation failed"
fi
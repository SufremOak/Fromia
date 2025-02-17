# Metadata
#name: "Example Script"
#author: "Fromia Developer"
#version: "1.0"

# Script logic
print("Hello from Fromia Runtime!")

# Call custom compiled C++ code
call_function("custom_function")

# Embedded C++ code
#cpp {
#include <iostream>

extern "C" void custom_function() {
    std::cout << "This is custom C++ code executed from the script!" << std::endl;
}
#}

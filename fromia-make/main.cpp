#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <map> // Missing header for std::map
#include <stdexcept>
#include <vector> // For potential vector usage in the future

// Function to parse the Fromia Makefile
std::map<std::string, std::string> parseFromiaMakefile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open Fromia Makefile: " + filename);
    }

    std::map<std::string, std::string> config;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string key, value;

        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value)) {
            config[key] = value;
        }
    }

    return config;
}

// Function to build the project
void buildProject(const std::map<std::string, std::string>& config) {
    std::string projectName = config.at("project_name");
    std::string sourceDir = config.at("source_directory");
    std::string outputBinary = config.at("output_binary");

    std::cout << "Building project: " << projectName << "\n";
    std::cout << "Source directory: " << sourceDir << "\n";
    std::cout << "Output binary: " << outputBinary << "\n";

    // Example compilation command
    std::string compileCommand = "g++ -std=c++17 -O2 -o " + outputBinary + " " + sourceDir + "/*.cpp";
    int result = std::system(compileCommand.c_str());

    if (result != 0) {
        throw std::runtime_error("Compilation failed!");
    }

    std::cout << "Build completed successfully.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: fromia-make <Fromia Makefile>\n";
        return 1;
    }

    std::string fromiaMakefile = argv[1];

    try {
        auto config = parseFromiaMakefile(fromiaMakefile);
        buildProject(config);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}

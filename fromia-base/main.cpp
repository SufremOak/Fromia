#include "Fromia/fromia.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

class FromiaRuntime {
public:
    static void runCrex(const std::string& crexPath) {
        // Check if the provided path exists and is a directory
        if (!fs::exists(crexPath) || !fs::is_directory(crexPath)) {
            Fromia::log("Error: .crex file not found or invalid structure.");
            return;
        }

        // Locate the Info.conf file in the Resources folder
        std::string infoPath = crexPath + "/Resources/Info.conf";
        if (!fs::exists(infoPath)) {
            Fromia::log("Error: Info.conf not found in Resources.");
            return;
        }

        // Parse Info.conf for runtime configuration
        auto config = parseConfig(infoPath);
        if (config.empty()) {
            Fromia::log("Error: Failed to parse Info.conf.");
            return;
        }

        // Locate the binary file
        std::string binaryPath = crexPath + "/" + config["Executable"];
        if (!fs::exists(binaryPath)) {
            Fromia::log("Error: Executable file not found in .crex structure.");
            return;
        }

        // Execute the binary
        Fromia::log("Launching application: " + config["Name"]);
        Fromia::log("Binary Path: " + binaryPath);
        Args::cmdRun(binaryPath);
    }

private:
    static std::map<std::string, std::string> parseConfig(const std::string& filePath) {
        std::map<std::string, std::string> config;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            Fromia::log("Error: Unable to open Info.conf.");
            return config;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue; // Skip comments and empty lines
            size_t delimiterPos = line.find('=');
            if (delimiterPos == std::string::npos) continue; // Skip malformed lines

            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            config[key] = value;
        }

        file.close();
        return config;
    }
};

main <void> {
    if (argc != 2) {
        Fromia::log("Usage: fromia_runtime <path_to_crex>");
        Fromia::End;
    }

    std::string crexPath = argv[1];
    FromiaRuntime::runCrex(crexPath);
    Fromia::End;
}

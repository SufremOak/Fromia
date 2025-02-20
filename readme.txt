888'Y88                      e   e     ,e,         
888 ,'Y 888,8,  e88 88e     d8b d8b        ,Y88b 
888C8   888    d888 888b   e Y8b Y8b   888   8 888 
888     888    Y888 888P  d8b Y8b Y8b  888 ,ee 888 
888     888      88 88   d888b Y8b Y8b 888  88 888 
======

Fromia is a modern runtime and library system combining the best features of C++, Objective-C, and NeXTStep-like design principles. It introduces a new hybrid syntax for application development and supports the execution of .crex (Chromia Executable) applications.

This README provides an overview of Fromia, its components, and instructions for installation and usage.

---

FEATURES
--------
- Hybrid syntax between C++ and Objective-C for cleaner, more modern development.
- Built-in support for .crex application format with a structured resource and binary hierarchy.
- Runtime environment inspired by NeXTStep/GWorkspace.
- Includes core libraries for:
  - `Fromia::Foundation` - Basic utilities and data structures.
  - `Fromia::GClass` - GUI components for application development.
  - `Fromia::GFilesystem` - Filesystem operations.
- Custom build tool: `fromia-make` for managing Fromia projects.
- Fully open-source and extensible.

---

INSTALLATION
------------
To build and install Fromia, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/SufremOak/Fromia.git
   cd Fromia
   ```
2. Build fromia-make:
   ```bash
   cd fromia-make
   make && sudo make install
   ```
3. Build fromia-base (Runtime):
   ```bash
    cd runtime
    make
   ```

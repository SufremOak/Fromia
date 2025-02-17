import os
import re
import subprocess
import ctypes
import platform
import argparse


class FromiaRuntime:
    def __init__(self, verbose=False):
        self.env = {}
        self.verbose = verbose

    def log(self, message):
        if self.verbose:
            print(f"[Fromia Log] {message}")

    def execute_script(self, script_path, compile_only=False, show_info=False, custom_env=None):
        with open(script_path, 'r') as script_file:
            script = script_file.read()

        # Parse the script
        metadata = self.parse_metadata(script)
        script_logic, cpp_code = self.parse_script(script)

        # Handle --info flag
        if show_info:
            self.display_info(metadata)
            return

        # Handle --compile-only flag
        if compile_only:
            if cpp_code:
                compiled_lib = self.compile_cpp_code(cpp_code)
                self.log(f"Embedded C++ code compiled to: {compiled_lib}")
            else:
                self.log("No embedded C++ code to compile.")
            return

        # Set custom environment variables
        if custom_env:
            for key, value in custom_env.items():
                self.env[key] = value

        # Compile C++ code if present
        compiled_lib = None
        if cpp_code:
            compiled_lib = self.compile_cpp_code(cpp_code)

        # Interpret script logic
        self.interpret_script_logic(script_logic, compiled_lib)

    def parse_metadata(self, script):
    metadata = {}  # Make sure this line is properly indented
    for line in script.splitlines():
        if line.startswith("#") and ":" in line:  # Check if the line starts with '#' and contains a colon
            try:
                key, value = line[1:].split(":", 1)
                metadata[key.strip()] = value.strip()
            except ValueError:
                self.log(f"Invalid metadata line: {line}")
    return metadata



    def parse_script(self, script):
        cpp_match = re.search(r"#cpp\s*{(.*?)}", script, re.DOTALL)
        if cpp_match:
            cpp_code = cpp_match.group(1)
            script_logic = script.replace(cpp_match.group(0), "")
            return script_logic, cpp_code
        return script, None

    def compile_cpp_code(self, cpp_code):
        temp_cpp = "temp_code.cpp"
        with open(temp_cpp, 'w') as cpp_file:
            cpp_file.write(cpp_code)

        shared_lib = "temp_code.so" if platform.system() != "Windows" else "temp_code.dll"
        compiler = "gcc"
        compile_cmd = [
            compiler, temp_cpp, "-shared", "-lstdc++", "-fPIC", "-o", shared_lib
        ]
        subprocess.run(compile_cmd, check=True)
        os.remove(temp_cpp)
        return shared_lib

    def interpret_script_logic(self, script_logic, compiled_lib):
        for line in script_logic.splitlines():
            line = line.strip()
            if line.startswith("print("):
                message = line[6:-1].strip('"')
                self.log(message)
            elif line.startswith("call_function("):
                function_name = line[14:-1].strip('"')
                if compiled_lib:
                    self.call_compiled_function(compiled_lib, function_name)
                else:
                    self.log(f"Error: No compiled library found for function '{function_name}'")

    def call_compiled_function(self, compiled_lib, function_name):
        lib = ctypes.CDLL(compiled_lib)
        func = getattr(lib, function_name)
        func()

    def display_info(self, metadata):
        self.log("Script Metadata:")
        for key, value in metadata.items():
            self.log(f"  {key}: {value}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Fromia Runtime for Chromia Scripts")
    parser.add_argument("script", help="Path to the .cr script to run")
    parser.add_argument("--info", action="store_true", help="Display script metadata")
    parser.add_argument("--compile-only", action="store_true", help="Compile embedded C++ code only, without running the script")
    parser.add_argument("--verbose", action="store_true", help="Enable verbose logging")
    parser.add_argument("--env", nargs="*", help="Set custom environment variables (e.g., KEY=VALUE)")

    args = parser.parse_args()

    # Parse custom environment variables
    custom_env = {}
    if args.env:
        for env_var in args.env:
            key, value = env_var.split("=", 1)
            custom_env[key] = value

    runtime = FromiaRuntime(verbose=args.verbose)
    runtime.execute_script(
        script_path=args.script,
        compile_only=args.compile_only,
        show_info=args.info,
        custom_env=custom_env,
    )

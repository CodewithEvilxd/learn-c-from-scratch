# 🛠️ Lesson 2: Environment Setup & First Program
## Setting up C Development Environment

---

## 🎯 Learning Objectives

- Install and configure C compiler
- Set up development environment
- Write and compile first C program
- Understand compilation process
- Troubleshoot common setup issues

---

## 💻 System Requirements

### **Minimum Requirements**
- **Operating System:** Windows 7+, macOS 10.12+, Ubuntu 16.04+
- **RAM:** 2GB minimum, 4GB recommended
- **Storage:** 2GB free space
- **Processor:** Any modern CPU

### **Recommended Setup**
- **RAM:** 8GB or more
- **Storage:** SSD with 10GB free space
- **Monitor:** 1920x1080 resolution or higher

---

## 🔧 Installing C Compiler

### **Option 1: GCC on Windows (MinGW-w64)**

#### **Step 1: Download MinGW-w64**
```bash
# Visit: https://www.mingw-w64.org/
# Or use MSYS2: https://www.msys2.org/
# Download mingw-w64-install.exe
```

#### **Step 2: Install MinGW-w64**
1. Run the installer
2. Select architecture: x86_64 (64-bit) or i686 (32-bit)
3. Select installation directory (e.g., `C:\mingw64`)
4. Select packages to install:
   - ✅ gcc (C Compiler)
   - ✅ g++ (C++ Compiler)
   - ✅ gdb (Debugger)
   - ✅ make (Build tool)
   - ✅ pkg-config (Package configuration)

#### **Step 3: Add to PATH**
```bash
# Method 1: Using System Properties
# 1. Right-click "This PC" → Properties
# 2. Advanced system settings → Environment Variables
# 3. Edit PATH variable → Add: C:\mingw64\bin

# Method 2: Using Command Prompt (temporary)
set PATH=%PATH%;C:\mingw64\bin

# Method 3: Using PowerShell (temporary)
$env:Path += ";C:\mingw64\bin"
```

#### **Step 4: Verify Installation**
```bash
# Open Command Prompt and type:
gcc --version
g++ --version
gdb --version
make --version

# Test compilation
gcc --help
```

### **Option 2: GCC on Windows (MSYS2)**

#### **Step 1: Download MSYS2**
```bash
# Visit: https://www.msys2.org/
# Download the installer
```

#### **Step 2: Install MSYS2**
1. Run the installer
2. Complete installation
3. Update package database:
```bash
pacman -Syu
```

#### **Step 3: Install GCC**
```bash
# Install GCC and development tools
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-gdb
pacman -S make
```

#### **Step 4: Add to PATH**
```bash
# MSYS2 automatically adds to PATH
# Or manually add: C:\msys64\mingw64\bin
```

### **Option 3: Visual Studio Build Tools (Windows)**

#### **Step 1: Download Visual Studio**
```bash
# Visit: https://visualstudio.microsoft.com/
# Download Visual Studio Community (free)
```

#### **Step 2: Install with C++ Build Tools**
1. Run installer
2. Select "Desktop development with C++"
3. Install

#### **Step 3: Use Developer Command Prompt**
```bash
# Open "Developer Command Prompt for VS"
cl /?

# Compile program
cl hello.c
```

### **Option 4: GCC on Linux (Ubuntu/Debian)**

#### **Step 1: Update Package List**
```bash
sudo apt update
```

#### **Step 2: Install Essential Build Tools**
```bash
# Install build-essential (includes GCC, make, etc.)
sudo apt install build-essential

# Install additional development tools
sudo apt install gcc gdb make valgrind
sudo apt install gcc-multilib  # For 32-bit compilation
```

#### **Step 3: Install Development Libraries**
```bash
# Install common development libraries
sudo apt install libncurses5-dev
sudo apt install libgtk-3-dev
sudo apt install libsdl2-dev
```

#### **Step 4: Verify Installation**
```bash
gcc --version
make --version
gdb --version
ldd --version
```

### **Option 5: GCC on macOS**

#### **Step 1: Install Command Line Tools**
```bash
# Install Apple's command line tools
xcode-select --install
```

#### **Step 2: Install Homebrew**
```bash
# Install Homebrew package manager
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### **Step 3: Install GCC**
```bash
# Install GCC
brew install gcc

# Install additional tools
brew install gdb
brew install make
brew install valgrind
```

#### **Step 4: Verify Installation**
```bash
gcc --version
g++ --version
gdb --version
```

### **Option 6: Clang Compiler**

#### **Step 1: Install Clang**
```bash
# Ubuntu/Debian
sudo apt install clang

# macOS
brew install llvm

# Windows (via MSYS2)
pacman -S mingw-w64-x86_64-clang
```

#### **Step 2: Use Clang**
```bash
# Compile with Clang
clang hello.c -o hello

# With warnings
clang -Wall hello.c -o hello

# Static analysis
clang --analyze hello.c
```

### **Option 7: TinyCC (TCC) - Fast Compiler**

#### **Step 1: Install TCC**
```bash
# Ubuntu/Debian
sudo apt install tcc

# Or download from: https://bellard.org/tcc/
```

#### **Step 2: Use TCC**
```bash
# Fast compilation
tcc hello.c -o hello

# Run directly (no linking needed)
tcc -run hello.c
```

### **Option 2: GCC on Linux (Ubuntu/Debian)**

#### **Step 1: Update Package List**
```bash
sudo apt update
```

#### **Step 2: Install Build Essentials**
```bash
sudo apt install build-essential
```

#### **Step 3: Install Additional Tools**
```bash
sudo apt install gcc gdb make
```

#### **Step 4: Verify Installation**
```bash
gcc --version
make --version
gdb --version
```

### **Option 3: GCC on macOS**

#### **Step 1: Install Command Line Tools**
```bash
xcode-select --install
```

#### **Step 2: Install Homebrew (Optional but Recommended)**
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### **Step 3: Install GCC**
```bash
brew install gcc
```

#### **Step 4: Verify Installation**
```bash
gcc --version
g++ --version
```

---

## 🖥️ Choosing an IDE/Code Editor

### **Option 1: Visual Studio Code (Recommended)**

#### **Step 1: Download VS Code**
```bash
# Visit: https://code.visualstudio.com/
# Download and install for your platform
```

#### **Step 2: Install Essential Extensions**
1. Open VS Code
2. Go to Extensions (Ctrl+Shift+X)
3. Install these extensions:
   - **C/C++** by Microsoft (official)
   - **C/C++ Extension Pack** by Microsoft
   - **Code Runner** for quick execution
   - **CMake Tools** for project management

#### **Step 3: Advanced VS Code Configuration**
```json
// settings.json
{
  "C_Cpp.default.compilerPath": "gcc",
  "C_Cpp.default.cStandard": "c11",
  "C_Cpp.default.cppStandard": "c++17",
  "C_Cpp.default.includePath": [
    "${workspaceFolder}/include",
    "/usr/include",
    "/usr/local/include"
  ],
  "C_Cpp.default.defines": [
    "_DEBUG",
    "UNICODE"
  ],
  "code-runner.executorMap": {
    "c": "gcc $fullFileName -o $fileNameWithoutExt && ./$fileNameWithoutExt",
    "cpp": "g++ $fullFileName -o $fileNameWithoutExt && ./$fileNameWithoutExt"
  },
  "code-runner.saveFileBeforeRun": true,
  "code-runner.clearPreviousOutput": true
}
```

#### **Step 4: Create VS Code Tasks**
```json
// .vscode/tasks.json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "cppbuild",
      "label": "C/C++: gcc build active file",
      "command": "/usr/bin/gcc",
      "args": [
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": [
        "$gcc"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "detail": "Task generated by Debugger."
    }
  ]
}
```

#### **Step 5: Debug Configuration**
```json
// .vscode/launch.json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "gcc - Build and debug active file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "C/C++: gcc build active file"
    }
  ]
}
```

### **Option 2: CLion (Professional IDE)**

#### **Step 1: Download CLion**
```bash
# Visit: https://www.jetbrains.com/clion/
# Download and install (30-day free trial)
```

#### **Step 2: Configure Toolchains**
1. Open CLion
2. Go to File → Settings → Build, Execution, Deployment → Toolchains
3. Add MinGW, Cygwin, or WSL toolchain
4. Configure CMake

#### **Step 3: Create New Project**
1. File → New Project
2. Select "C Executable"
3. Configure project settings

### **Option 3: Eclipse CDT**

#### **Step 1: Download Eclipse CDT**
```bash
# Visit: https://www.eclipse.org/cdt/
# Download Eclipse IDE for C/C++ Developers
```

#### **Step 2: Install CDT**
1. Run Eclipse installer
2. Select "Eclipse IDE for C/C++ Developers"
3. Complete installation

#### **Step 3: Configure Workspace**
1. Set workspace directory
2. Configure compiler settings
3. Install additional plugins if needed

### **Option 4: Code::Blocks**

#### **Step 1: Download Code::Blocks**
```bash
# Visit: http://www.codeblocks.org/
# Download with MinGW included
```

#### **Step 2: Install and Configure**
1. Run installer
2. Choose installation with MinGW
3. Complete installation
4. Launch Code::Blocks

#### **Step 3: Create New Project**
1. File → New → Project
2. Select "Console application"
3. Choose C language
4. Configure project settings

### **Option 5: Vim/Neovim with Plugins**

#### **Step 1: Install Vim/Neovim**
```bash
# Ubuntu/Debian
sudo apt install vim
sudo apt install neovim

# macOS
brew install vim
brew install neovim
```

#### **Step 2: Install Plugins**
```vim
" .vimrc configuration
syntax on
set number
set autoindent
set tabstop=4
set shiftwidth=4
set expandtab

" C-specific settings
autocmd FileType c setlocal cindent
autocmd FileType c setlocal comments=sr:/*,mb:*,ex:*/
```

#### **Step 3: Install Language Server**
```bash
# Install clangd for code completion
sudo apt install clangd-12
```

### **Option 6: Emacs with C Mode**

#### **Step 1: Install Emacs**
```bash
# Ubuntu/Debian
sudo apt install emacs

# macOS
brew install emacs
```

#### **Step 2: Configure C Mode**
```emacs-lisp
;; .emacs configuration
(require 'cc-mode)
(add-hook 'c-mode-hook
          (lambda ()
            (c-set-style "linux")
            (setq c-basic-offset 4)
            (c-toggle-auto-newline 1)))
```

### **Option 7: Sublime Text**

#### **Step 1: Download Sublime Text**
```bash
# Visit: https://www.sublimetext.com/
# Download and install
```

#### **Step 2: Install Package Control**
1. Open Sublime Text
2. Install Package Control
3. Install C/C++ packages

#### **Step 3: Configure Build System**
```json
// C.sublime-build
{
  "cmd": ["gcc", "${file}", "-o", "${file_path}/${file_base_name}"],
  "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir": "${file_path}",
  "selector": "source.c",
  "variants": [
    {
      "name": "Run",
      "cmd": ["bash", "-c", "gcc '${file}' -o '${file_path}/${file_base_name}' && '${file_path}/${file_base_name}'"]
    }
  ]
}
```

### **Option 8: Atom (Deprecated)**

#### **Step 1: Download Atom**
```bash
# Visit: https://atom.io/
# Note: Atom is deprecated, consider VS Code instead
```

#### **Step 2: Install Packages**
1. Install platformio-ide-terminal
2. Install language-c
3. Install build-tools

### **Option 2: Code::Blocks**

#### **Step 1: Download Code::Blocks**
```bash
# Visit: http://www.codeblocks.org/
# Download with MinGW included
```

#### **Step 2: Install and Configure**
1. Run installer
2. Choose installation with MinGW
3. Complete installation
4. Launch Code::Blocks

### **Option 3: Dev-C++**

#### **Step 1: Download Dev-C++**
```bash
# Visit: https://sourceforge.net/projects/dev-cpp/
# Download latest version
```

#### **Step 2: Install**
1. Run installer
2. Choose complete installation
3. Launch Dev-C++

---

## 📝 Writing Your First C Program

### **Step 1: Create Source File**
```c
// hello.c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    printf("Welcome to C Programming!\n");
    return 0;
}
```

### **Step 2: Compile the Program**
```bash
# Using GCC compiler
gcc hello.c -o hello

# This creates an executable file named 'hello'
```

### **Step 3: Run the Program**
```bash
# Windows
hello.exe

# Linux/macOS
./hello
```

### **Expected Output:**
```
Hello, World!
Welcome to C Programming!
```

---

## 🔍 Understanding the Compilation Process

### **What is Compilation?**
Compilation is the process of converting human-readable C code into machine-readable binary code.

### **Detailed Compilation Steps:**

#### **1. Preprocessing**
```bash
# Command: gcc -E hello.c
# What it does:
# - Processes #include directives
# - Expands macros (#define)
# - Removes comments
# - Processes conditional compilation
```

#### **2. Compilation**
```bash
# Command: gcc -S hello.c
# What it does:
# - Converts C code to assembly language
# - Performs syntax checking
# - Optimizes code (if requested)
# - Generates .s file (assembly code)
```

#### **3. Assembly**
```bash
# Command: gcc -c hello.c
# What it does:
# - Converts assembly to machine code
# - Generates .o file (object file)
# - Contains binary instructions
```

#### **4. Linking**
```bash
# Command: gcc hello.o -o hello
# What it does:
# - Links object files with libraries
# - Resolves external references
# - Creates final executable
```

### **Complete Compilation Command**
```bash
# Single command for all steps
gcc hello.c -o hello

# With debugging information
gcc hello.c -o hello -g

# With all warnings
gcc hello.c -o hello -Wall

# Optimized compilation
gcc hello.c -o hello -O2
```

---

## 🐛 Troubleshooting Common Issues

### **Issue 1: "gcc command not found"**

#### **Windows Solution:**
```bash
# Check if MinGW is in PATH
echo %PATH%

# Add MinGW to PATH
set PATH=%PATH%;C:\MinGW\bin

# Or reinstall MinGW
```

#### **Linux/macOS Solution:**
```bash
# Install GCC
sudo apt install gcc  # Ubuntu/Debian
brew install gcc      # macOS with Homebrew

# Check installation
which gcc
gcc --version
```

### **Issue 2: Compilation Errors**

#### **Common Error: Missing Semicolon**
```c
// Error
printf("Hello")

// Fix
printf("Hello");
```

#### **Common Error: Undefined Reference**
```c
// Error: forgot to include header
int main() {
    printf("Hello");  // Error: printf not declared
    return 0;
}

// Fix
#include <stdio.h>
int main() {
    printf("Hello");
    return 0;
}
```

### **Issue 3: Runtime Errors**

#### **Segmentation Fault**
```c
// Common causes:
int *ptr = NULL;
*ptr = 10;  // Segmentation fault

// Fix: Check for NULL
if (ptr != NULL) {
    *ptr = 10;
}
```

### **Issue 4: File Not Found**
```bash
# Error: No such file or directory
gcc hello.txt -o hello

# Fix: Use correct file extension
gcc hello.c -o hello
```

---

## ⚙️ GCC Compiler Options

### **Essential GCC Flags**

| Flag | Description | Example |
|------|-------------|---------|
| `-o <file>` | Specify output filename | `gcc hello.c -o myprogram` |
| `-c` | Compile only (no linking) | `gcc -c hello.c` |
| `-g` | Include debugging information | `gcc -g hello.c -o hello` |
| `-O0` | No optimization (default) | `gcc -O0 hello.c -o hello` |
| `-O1` | Basic optimization | `gcc -O1 hello.c -o hello` |
| `-O2` | Advanced optimization | `gcc -O2 hello.c -o hello` |
| `-O3` | Aggressive optimization | `gcc -O3 hello.c -o hello` |
| `-Os` | Optimize for size | `gcc -Os hello.c -o hello` |

### **Warning and Diagnostic Flags**

| Flag | Description | Example |
|------|-------------|---------|
| `-Wall` | Enable most warnings | `gcc -Wall hello.c -o hello` |
| `-Wextra` | Extra warnings | `gcc -Wextra hello.c -o hello` |
| `-Werror` | Treat warnings as errors | `gcc -Werror hello.c -o hello` |
| `-Wpedantic` | Strict ISO C compliance | `gcc -pedantic hello.c -o hello` |
| `-Wno-<warning>` | Disable specific warning | `gcc -Wno-unused-variable hello.c` |
| `-fdiagnostics-color=always` | Colored diagnostic messages | `gcc -fdiagnostics-color=always hello.c` |

### **Include and Library Flags**

| Flag | Description | Example |
|------|-------------|---------|
| `-I<dir>` | Add include directory | `gcc -I./include hello.c -o hello` |
| `-L<dir>` | Add library directory | `gcc -L./lib hello.c -lmylib -o hello` |
| `-l<lib>` | Link with library | `gcc hello.c -lm -o hello` |
| `-static` | Static linking | `gcc -static hello.c -o hello` |
| `-shared` | Create shared library | `gcc -shared -o libmylib.so mylib.c` |
| `-fPIC` | Position-independent code | `gcc -fPIC -c hello.c -o hello.o` |

### **Architecture and Platform Flags**

| Flag | Description | Example |
|------|-------------|---------|
| `-m32` | Compile for 32-bit | `gcc -m32 hello.c -o hello` |
| `-m64` | Compile for 64-bit | `gcc -m64 hello.c -o hello` |
| `-march=<arch>` | Target specific architecture | `gcc -march=native hello.c -o hello` |
| `-mtune=<cpu>` | Tune for specific CPU | `gcc -mtune=generic hello.c -o hello` |
| `-fpic` | Position-independent code | `gcc -fpic -c hello.c -o hello.o` |

### **Language Standard Flags**

| Flag | Description | Example |
|------|-------------|---------|
| `-std=c89` | ANSI C (C89) standard | `gcc -std=c89 hello.c -o hello` |
| `-std=c99` | C99 standard | `gcc -std=c99 hello.c -o hello` |
| `-std=c11` | C11 standard | `gcc -std=c11 hello.c -o hello` |
| `-std=c18` | C18 standard | `gcc -std=c18 hello.c -o hello` |
| `-std=gnu89` | GNU C89 with extensions | `gcc -std=gnu89 hello.c -o hello` |
| `-std=gnu11` | GNU C11 with extensions | `gcc -std=gnu11 hello.c -o hello` |

### **Advanced GCC Flags**

| Flag | Description | Example |
|------|-------------|---------|
| `-fsanitize=address` | Address sanitizer | `gcc -fsanitize=address hello.c -o hello` |
| `-fsanitize=undefined` | Undefined behavior sanitizer | `gcc -fsanitize=undefined hello.c -o hello` |
| `-fstack-protector` | Stack protection | `gcc -fstack-protector hello.c -o hello` |
| `-D<macro>` | Define macro | `gcc -DDEBUG hello.c -o hello` |
| `-U<macro>` | Undefine macro | `gcc -UDEBUG hello.c -o hello` |
| `-E` | Preprocess only | `gcc -E hello.c -o hello.i` |
| `-S` | Compile to assembly | `gcc -S hello.c -o hello.s` |

### **Common GCC Command Patterns**

```bash
# Basic compilation with warnings
gcc -Wall -Wextra -std=c11 hello.c -o hello

# Debug build
gcc -g -O0 -Wall hello.c -o hello_debug

# Release build
gcc -O2 -DNDEBUG hello.c -o hello_release

# Compile multiple files
gcc -c main.c -o main.o
gcc -c utils.c -o utils.o
gcc main.o utils.o -o program

# Link with external libraries
gcc hello.c -I/usr/include -L/usr/lib -lmysqlclient -o hello

# Cross-compilation
gcc -march=armv7-a -mfpu=vfpv3 hello.c -o hello_arm

# Profile-guided optimization
gcc -fprofile-generate hello.c -o hello
./hello  # Run to generate profile
gcc -fprofile-use hello.c -o hello_optimized

# Code coverage
gcc -fprofile-arcs -ftest-coverage hello.c -o hello
./hello
gcov hello.c  # Generate coverage report
```

### **GCC Environment Variables**

```bash
# Set default compiler flags
export CFLAGS="-Wall -Wextra -std=c11"
export CXXFLAGS="-Wall -Wextra -std=c++17"

# Set include paths
export C_INCLUDE_PATH="/usr/local/include:/opt/include"

# Set library paths
export LIBRARY_PATH="/usr/local/lib:/opt/lib"
export LD_LIBRARY_PATH="/usr/local/lib:/opt/lib"

# Use specific GCC version
export CC="gcc-9"
export CXX="g++-9"
```

### **GCC Configuration Files**

```bash
# Create .gccrc file in home directory
# ~/.gccrc
-Wall
-Wextra
-std=c11
-O2

# Use configuration file
gcc @~/.gccrc hello.c -o hello
```

### **Troubleshooting GCC Issues**

```bash
# Check GCC version and capabilities
gcc --version
gcc -v

# List all available options
gcc --help
gcc --help=optimizers
gcc --help=warnings

# Check include paths
gcc -xc -E -v /dev/null

# Check library paths
gcc -print-search-dirs

# Verbose compilation
gcc -v hello.c -o hello
```

---

## 📁 Project Structure Setup

### **Recommended Directory Structure**
```
c_projects/
├── src/           # Source files (.c)
├── include/       # Header files (.h)
├── build/         # Compiled objects (.o)
├── bin/           # Executables
├── lib/           # Custom libraries
└── docs/          # Documentation
```

### **Creating Project Structure**
```bash
# Create directories
mkdir c_projects
cd c_projects
mkdir src include build bin lib docs

# Create a simple Makefile
touch Makefile
```

### **Sample Makefile**
```makefile
# Simple Makefile for C projects
CC = gcc
CFLAGS = -Wall -g
TARGET = program

all: $(TARGET)

$(TARGET): src/main.o
    $(CC) $(CFLAGS) -o bin/$(TARGET) build/main.o

src/main.o: src/main.c
    $(CC) $(CFLAGS) -c src/main.c -o build/main.o

clean:
    rm -f build/*.o bin/$(TARGET)

run: $(TARGET)
    ./bin/$(TARGET)
```

---

## 🎯 Practice Exercises

### **Exercise 1: Basic Compilation**
1. Create a C file named `test.c`
2. Write a program that prints your name
3. Compile it using GCC
4. Run the executable
5. Try different GCC flags

### **Exercise 2: Multiple Files**
1. Create `main.c` and `functions.c`
2. Define a function in `functions.c`
3. Call it from `main.c`
4. Compile both files together

### **Exercise 3: Makefile Practice**
1. Create a Makefile for a simple project
2. Add rules for compilation, cleaning, and running
3. Test all Makefile targets

### **Exercise 4: Error Debugging**
1. Intentionally create compilation errors
2. Fix them one by one
3. Learn from error messages

---

## 🧠 Quiz: Test Your Knowledge

### **Question 1:**
What does the GCC flag `-Wall` do?
a) Creates a wall around the program
b) Enables all compiler warnings
c) Compiles for all platforms
d) Links all libraries

### **Question 2:**
Which command compiles a C program without linking?
a) `gcc -o program hello.c`
b) `gcc -c hello.c`
c) `gcc -Wall hello.c`
d) `gcc -g hello.c`

### **Question 3:**
What is the correct file extension for C source files?
a) `.cpp`
b) `.java`
c) `.c`
d) `.py`

### **Question 4:**
Which IDE is recommended for beginners?
a) Vim
b) Emacs
c) Visual Studio Code
d) Command Line

---

## 🔗 Additional Resources

### **Online Compilers**
- [OnlineGDB](https://www.onlinegdb.com/online_c_compiler)
- [JDoodle](https://www.jdoodle.com/c-online-compiler)
- [Replit](https://replit.com/languages/c)

### **Documentation**
- [GCC Manual](https://gcc.gnu.org/onlinedocs/)
- [C Standard Library](https://en.cppreference.com/w/c)
- [Visual Studio Code Docs](https://code.visualstudio.com/docs)

### **Learning Resources**
- [Learn C Programming](https://www.programiz.com/c-programming)
- [C Tutorial](https://www.tutorialspoint.com/cprogramming/)
- [GeeksforGeeks C](https://www.geeksforgeeks.org/c-programming-language/)

---

## 🎯 Next Steps

**Great job!** You've successfully:
- ✅ Installed a C compiler
- ✅ Set up your development environment
- ✅ Written and compiled your first C program
- ✅ Learned about the compilation process
- ✅ Troubleshot common issues

**Next Lesson Preview:**
- Lexical structure and tokens
- Keywords, identifiers, and constants
- Comments and escape sequences
- Basic program structure

---

**🚀 Ready to dive deeper into C programming?**

[⬅️ Previous: Introduction](01_Introduction_to_C.md) | [Next: Lexical Structure ➡️](03_Lexical_Structure.md)
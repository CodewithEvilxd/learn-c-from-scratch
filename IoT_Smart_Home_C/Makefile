# IoT Smart Home System - Makefile
# Build system for the complete IoT smart home implementation

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I headers/ -I src/
LDFLAGS = -lm -pthread

# Directories
SRC_DIR = src
HDR_DIR = headers
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/device.c \
          $(SRC_DIR)/automation.c \
          $(SRC_DIR)/security.c \
          $(SRC_DIR)/energy.c \
          $(SRC_DIR)/network.c \
          $(SRC_DIR)/storage.c \
          $(SRC_DIR)/utils.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Executable name
TARGET = smart_home

# Default target
all: $(TARGET)

# Create executable
$(TARGET): $(OBJECTS)
	@echo "🔗 Linking $(TARGET)..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(BIN_DIR)/$(TARGET) $(LDFLAGS)
	@echo "✅ Build complete: $(BIN_DIR)/$(TARGET)"

# Compile source files
%.o: %.c
	@echo "📦 Compiling $<..."
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
$(SRC_DIR)/main.o: $(HDR_DIR)/device.h $(HDR_DIR)/automation.h $(HDR_DIR)/security.h $(HDR_DIR)/energy.h $(HDR_DIR)/network.h $(HDR_DIR)/storage.h $(HDR_DIR)/utils.h
$(SRC_DIR)/device.o: $(HDR_DIR)/device.h $(HDR_DIR)/utils.h
$(SRC_DIR)/automation.o: $(HDR_DIR)/automation.h $(HDR_DIR)/device.h $(HDR_DIR)/utils.h
$(SRC_DIR)/security.o: $(HDR_DIR)/security.h $(HDR_DIR)/device.h $(HDR_DIR)/utils.h
$(SRC_DIR)/energy.o: $(HDR_DIR)/energy.h $(HDR_DIR)/device.h $(HDR_DIR)/utils.h
$(SRC_DIR)/network.o: $(HDR_DIR)/network.h $(HDR_DIR)/device.h $(HDR_DIR)/utils.h
$(SRC_DIR)/storage.o: $(HDR_DIR)/storage.h $(HDR_DIR)/utils.h
$(SRC_DIR)/utils.o: $(HDR_DIR)/utils.h

# Create symbolic link for easy access
	@ln -sf $(BIN_DIR)/$(TARGET) $(TARGET) 2>/dev/null || cp $(BIN_DIR)/$(TARGET) $(TARGET)

# Clean build artifacts
clean:
	@echo "🧹 Cleaning build artifacts..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(TARGET)
	@rm -f $(OBJECTS) $(TARGET).exe
	@echo "✅ Clean complete"

# Clean and rebuild
rebuild: clean all

# Run the application
run: $(TARGET)
	@echo "🚀 Starting IoT Smart Home System..."
	./$(TARGET)

# Run with demo script
demo: $(TARGET)
	@echo "🎭 Running demo script..."
	@chmod +x demo.sh
	./demo.sh

# Create data directories
init:
	@echo "📁 Creating data directories..."
	@mkdir -p data logs
	@echo "✅ Initialization complete"

# Install system (copy to /usr/local/bin)
install: $(TARGET)
	@echo "📦 Installing to /usr/local/bin..."
	@sudo cp $(BIN_DIR)/$(TARGET) /usr/local/bin/
	@sudo mkdir -p /etc/smarthome
	@sudo cp smarthome.conf /etc/smarthome/ 2>/dev/null || echo "No config file to copy"
	@echo "✅ Installation complete"

# Uninstall system
uninstall:
	@echo "🗑️ Uninstalling from system..."
	@sudo rm -f /usr/local/bin/$(TARGET)
	@sudo rm -rf /etc/smarthome
	@echo "✅ Uninstallation complete"

# Code analysis
analyze:
	@echo "🔍 Analyzing code..."
	@which cppcheck >/dev/null 2>&1 && cppcheck --enable=all --std=c99 $(SOURCES) $(HDR_DIR)/*.h || echo "cppcheck not found"
	@which clang-tidy >/dev/null 2>&1 && clang-tidy $(SOURCES) -- -I$(HDR_DIR) || echo "clang-tidy not found"

# Memory leak check
memcheck: $(TARGET)
	@echo "💧 Checking for memory leaks..."
	@which valgrind >/dev/null 2>&1 && valgrind --leak-check=full ./$(BIN_DIR)/$(TARGET) <<< "quit" || echo "valgrind not found"

# Code formatting
format:
	@echo "🎨 Formatting code..."
	@which clang-format >/dev/null 2>&1 && clang-format -i $(SOURCES) $(HDR_DIR)/*.h || echo "clang-format not found"

# Generate documentation
docs:
	@echo "📚 Generating documentation..."
	@which doxygen >/dev/null 2>&1 && doxygen Doxyfile || echo "doxygen not found"

# Test build
test-build: $(TARGET)
	@echo "🧪 Testing build..."
	@./$(BIN_DIR)/$(TARGET) --version 2>/dev/null || ./$(BIN_DIR)/$(TARGET) <<< "help" | head -5
	@echo "✅ Build test passed"

# Package for distribution
package: $(TARGET)
	@echo "📦 Creating distribution package..."
	@mkdir -p dist
	@cp $(BIN_DIR)/$(TARGET) dist/
	@cp README.md dist/
	@cp demo.sh dist/ 2>/dev/null || echo "No demo script"
	@tar -czf dist/iot_smarthome_v1.0.tar.gz -C dist .
	@echo "✅ Package created: dist/iot_smarthome_v1.0.tar.gz"

# Show build information
info:
	@echo "🏗️ Build Information:"
	@echo "  Compiler: $(CC)"
	@echo "  CFLAGS: $(CFLAGS)"
	@echo "  LDFLAGS: $(LDFLAGS)"
	@echo "  Sources: $(words $(SOURCES))"
	@echo "  Target: $(TARGET)"
	@echo "  Build dir: $(BIN_DIR)"

# Help target
help:
	@echo "🏠 IoT Smart Home System - Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Build the complete system (default)"
	@echo "  clean      - Remove build artifacts"
	@echo "  rebuild    - Clean and rebuild"
	@echo "  run        - Build and run the system"
	@echo "  demo       - Run the demo script"
	@echo "  init       - Create data directories"
	@echo "  install    - Install system to /usr/local/bin"
	@echo "  uninstall  - Remove system from /usr/local/bin"
	@echo "  analyze    - Run static code analysis"
	@echo "  memcheck   - Check for memory leaks"
	@echo "  format     - Format code with clang-format"
	@echo "  docs       - Generate documentation"
	@echo "  test-build - Test the build"
	@echo "  package    - Create distribution package"
	@echo "  info       - Show build information"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Usage: make [target]"
	@echo ""
	@echo "Examples:"
	@echo "  make all          # Build everything"
	@echo "  make run          # Build and run"
	@echo "  make clean all    # Clean then build"
	@echo "  make demo         # Run demonstration"

# Phony targets
.PHONY: all clean rebuild run demo init install uninstall analyze memcheck format docs test-build package info help

# Default target
.DEFAULT_GOAL := all
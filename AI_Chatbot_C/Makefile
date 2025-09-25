# AI Chatbot in C - Makefile
# Comprehensive build system for the AI chatbot project

CC = gcc
CFLAGS = -Wall -Wextra -O2 -I headers/
LDFLAGS = -lm
TARGET = chatbot
SRC_DIR = src
OBJ_DIR = obj
HDR_DIR = headers

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
HEADERS = $(wildcard $(HDR_DIR)/*.h)

# Default target
all: $(TARGET)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET) *.log

# Clean everything including data files
clean-all: clean
	rm -rf data/*.db data/*.txt

# Run the chatbot
run: $(TARGET)
	./$(TARGET)

# Run in interactive mode
interactive: $(TARGET)
	./$(TARGET)

# Run tests (if implemented)
test: $(TARGET)
	@echo "Running tests..."
	# Add test commands here

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: clean all

# Release build
release: CFLAGS += -O3 -DNDEBUG
release: clean all

# Install (copy to system)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	chmod +x /usr/local/bin/$(TARGET)

# Uninstall
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Show project info
info:
	@echo "AI Chatbot in C"
	@echo "==============="
	@echo "Source files: $(words $(SRCS))"
	@echo "Header files: $(words $(HEADERS))"
	@echo "Object files: $(words $(OBJS))"
	@echo "Compiler: $(CC)"
	@echo "Flags: $(CFLAGS)"

# Create data directory and sample files
init-data:
	mkdir -p data
	@echo "# Sample Knowledge Base" > data/knowledge_base.txt
	@echo "What is AI?,Artificial Intelligence is the simulation of human intelligence in machines.,technology,90" >> data/knowledge_base.txt
	@echo "What is programming?,Programming is writing instructions for computers to solve problems.,technology,85" >> data/knowledge_base.txt
	@echo "# Sample memory file will be created automatically" > data/memory.db.sample

# Help target
help:
	@echo "AI Chatbot Build System"
	@echo "======================="
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Build the chatbot (default)"
	@echo "  clean        - Remove build files"
	@echo "  clean-all    - Remove all generated files"
	@echo "  run          - Build and run the chatbot"
	@echo "  interactive  - Run in interactive mode"
	@echo "  test         - Run tests"
	@echo "  debug        - Build with debug symbols"
	@echo "  release      - Build optimized release"
	@echo "  install      - Install to system"
	@echo "  uninstall    - Remove from system"
	@echo "  info         - Show project information"
	@echo "  init-data    - Create sample data files"
	@echo "  help         - Show this help"
	@echo ""
	@echo "Usage examples:"
	@echo "  make                # Build the project"
	@echo "  make run           # Build and run"
	@echo "  make clean && make # Clean and rebuild"
	@echo "  make debug         # Build with debug info"

.PHONY: all clean clean-all run interactive test debug release install uninstall info init-data help
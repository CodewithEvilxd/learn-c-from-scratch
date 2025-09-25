# Blockchain Voting System Makefile
# Compiles the complete blockchain voting system in C

CC = gcc
CFLAGS = -Wall -Wextra -O2 -I headers/
LDFLAGS = -lm
TARGET = voting_system

# Source files
SRCS = src/main.c \
       src/blockchain.c \
       src/block.c \
       src/transaction.c \
       src/crypto.c \
       src/voter.c \
       src/election.c \
       src/consensus.c \
       src/network.c \
       src/utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET) *.db *.log

# Clean and rebuild
rebuild: clean all

# Run the system
run: $(TARGET)
	./$(TARGET)

# Test compilation
test-compile: $(OBJS)
	@echo "Compilation successful!"

# Show source files
show-src:
	@echo "Source files:"
	@for file in $(SRCS); do echo "  $$file"; done

# Count lines of code
count-lines:
	@echo "Lines of code:"
	@find src/ headers/ -name "*.c" -o -name "*.h" | xargs wc -l | tail -1

# Create distribution package
dist: clean
	tar -czf blockchain_voting_c.tar.gz src/ headers/ data/ tests/ docs/ Makefile README.md

.PHONY: all clean rebuild run test-compile show-src count-lines dist
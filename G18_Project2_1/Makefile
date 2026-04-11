CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
BIN_DIR = bin
SRC_DIR = src
UTILS_DIR = $(SRC_DIR)/utils
SHELL_DIR = $(SRC_DIR)/shell

# Automatically find all .c files in src/utils
UTILS_SRC = $(wildcard $(UTILS_DIR)/*.c)
# Create a list of target binaries in bin/
UTILS_BIN = $(patsubst $(UTILS_DIR)/%.c, $(BIN_DIR)/%, $(UTILS_SRC))

# The main shell binary
SHELL_TARGET = $(BIN_DIR)/g18-shell

# Default target
all: $(BIN_DIR) $(UTILS_BIN) $(SHELL_TARGET)

# Create bin directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile each utility (e.g., custom_cat.c -> bin/custom_cat)
$(BIN_DIR)/%: $(UTILS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Compile the shell
$(SHELL_TARGET): $(SHELL_DIR)/main_shell.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
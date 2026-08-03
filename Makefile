# Nom du binaire
NAME = packx

# Dossiers
APP_DIR = ~/.packx/
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN = $(BUILD_DIR)/$(NAME)

# Compilateur
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Werror -Iinclude

# Sources
SRC_DIR = src
SRCS = $(shell find $(SRC_DIR) -name "*.c")

# Objets
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Règle principale
all: $(BIN)

# Link
$(BIN): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BUILD_DIR)

re: fclean all

# Run
run: all
	./$(BIN)
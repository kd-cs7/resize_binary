CC = gcc
CFLAGS = -Wall
LDFLAGS =  

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = ./

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/manage_file.c $(SRC_DIR)/misc.c $(SRC_DIR)/resize.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/resize_binary

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/


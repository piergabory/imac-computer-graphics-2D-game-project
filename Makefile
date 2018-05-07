# Bash options

CC = gcc
CFLAGS = -Wall -W -g 
LDFLAGS =

# Binary name

APP_BIN = flapimac


# Paths

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include/
BIN_PATH = bin
LIB_PATH = lib


# Files

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))


# OS detection

UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
    CFLAGS += -D MacOS
    LDFLAGS = -framework OpenGL -framework SDL2 -framework SDL2_image -framework Cocoa
else
	CFLAGS += -D Linux
    LDFLAGS = -lSDL2 -lGLU -lGL -lm -lSDL2_image
endif


# Methods

all: $(APP_BIN)

$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(CFLAGS) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

run:
	$(BIN_PATH)/$(APP_BIN)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)


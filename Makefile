CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

APP_BIN = flapimac

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = bin
LIB_PATH = lib

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))


ifeq ($(OS),Windows_NT)
	CCFLAGS += -D Windows
else
    UNAME_S := $(shell uname -s)

    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D Linux
    endif

    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D MacOs
		LDFLAGS = -framework OpenGL SDL2  SDL2_image  Cocoa
    endif
endif


all: $(APP_BIN)

$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c -v $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)


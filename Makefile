.PHONY: all clean run

PROJECT ?= game 
RAYLIB_PATH ?= C:/raylib/raylib
CC = gcc
BUILD ?= Release

SRC_DIR := ./
OBJ_DIR := obj

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OUT := $(PROJECT).exe

CFLAGS = -Wall -std=c99 -I"$(RAYLIB_PATH)/src" -I"$(RAYLIB_PATH)/src/external" 

ifeq ($(BUILD),Debug)
CFLAGS += -g -O0 -D_DEBUG
else
CFLAGS += -O2
endif

LDFLAGS := -L"$(RAYLIB_PATH)/src"
LDLIBS := -lraylib -lopengl32 -lgdi32 -lwinmm

all: $(OBJ_DIR) $(OUT)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# compile .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# link
$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT) $(OBJ_DIR)/*.o


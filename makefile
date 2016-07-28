
CC = clang++-3.6

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
CC = clang++
endif

CFLAGS			= -std=c++11 -O2 -ferror-limit=0 -Wall -Weverything -pedantic

BUILD_DIR		= build
SOURCE_DIR		= src

EXECUTABLE		= main

MAIN_OBJS		= $(MAIN_TARGET)
MAIN_TARGET		= $(BUILD_DIR)/main.o

LIBS			= -L/usr/local/lib -L/usr/lib
INCLUDES_DIR	= -I/usr/local/include/



all: $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(INCLUDES_DIR) $(LIBS) -o $(BUILD_DIR)/$(EXECUTABLE)
	./$(BUILD_DIR)/$(EXECUTABLE)

$(MAIN_TARGET): $(SOURCE_DIR)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES_DIR) -c $(SOURCE_DIR)/main.cpp -o $(MAIN_TARGET)


.PHONY: clean
clean:
	-rm $(BUILD_DIR)/*.o $(BUILD_DIR)/*~ $(BUILD_DIR)/$(EXECUTABLE)

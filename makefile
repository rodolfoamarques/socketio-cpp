
CC = clang++-3.6

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
CC = clang++
endif

CFLAGS					= -std=c++11 -O2 -ferror-limit=0 -Wall -Weverything -pedantic

BUILD_DIR				= build
SOURCE_DIR				= src
SOCKETMODEL_SOURCE_DIR	= $(SOURCE_DIR)/SocketAPI

SOCKETIOCPP_DIR			= vendor/socket.io-client-cpp/build
SOCKETIOCPP_LIB_DIR		= $(SOCKETIOCPP_DIR)/lib/Release
SOCKETIOCPP_INCLUDE_DIR	= $(SOCKETIOCPP_DIR)/include

EXECUTABLE				= main

MAIN_TARGET				= $(BUILD_DIR)/main.o
SOCKETMODEL_TARGET		= $(BUILD_DIR)/socket_model.o
MAIN_OBJS				= $(SOCKETMODEL_TARGET) $(MAIN_TARGET)

SOCKETMODEL_DEPS		= $(SOCKETMODEL_SOURCE_DIR)/SocketModel.hpp \
							$(SOCKETIOCPP_INCLUDE_DIR)/sio_client.h \
							$(SOCKETIOCPP_INCLUDE_DIR)/sio_message.h \
							$(SOCKETIOCPP_INCLUDE_DIR)/sio_socket.h

INCLUDES_DIR			= -I/usr/local/include/ -I$(SOCKETIOCPP_INCLUDE_DIR)
LIBS					= -L/usr/local/lib -L/usr/lib -L$(SOCKETIOCPP_LIB_DIR) \
							-lsioclient -lboost_date_time -lboost_random -lboost_system



all: $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(INCLUDES_DIR) $(LIBS) -o $(BUILD_DIR)/$(EXECUTABLE)
	./$(BUILD_DIR)/$(EXECUTABLE)

$(SOCKETMODEL_TARGET): $(SOCKETMODEL_SOURCE_DIR)/SocketModel.cpp $(SOCKETMODEL_DEPS)
	$(CC) $(CFLAGS) -I$(SOCKETIOCPP_INCLUDE_DIR) -c $(SOCKETMODEL_SOURCE_DIR)/SocketModel.cpp -o $(SOCKETMODEL_TARGET)

$(MAIN_TARGET): $(SOURCE_DIR)/main.cpp $(SOCKETMODEL_SOURCE_DIR)/SocketModel.hpp 
	$(CC) $(CFLAGS) $(INCLUDES_DIR) -c $(SOURCE_DIR)/main.cpp -o $(MAIN_TARGET)


.PHONY: clean
clean:
	-rm $(BUILD_DIR)/*.o $(BUILD_DIR)/*~ $(BUILD_DIR)/$(EXECUTABLE)

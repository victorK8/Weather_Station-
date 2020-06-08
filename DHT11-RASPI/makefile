# Compiler
CC = g++

# Includes
INCLUDE_DIR = include

# Source Code Path
SRC_DIR = src

# Flags to compiler
CFLAGS = -I$(INCLUDE_DIR)  -lwiringPi

# Header dependencies
DEPS = $(INCLUDE_DIR)/dht11.h

# Files to compile
SRCS =  $(SRC_DIR)/dht11.cpp $(SRC_DIR)/main.cpp

# EXE NAME
EXE = run

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)

# Compiler
CC = g++

# Includes
INCLUDE_DIR = include

# Source Code Path
SRC_DIR = src

# LogFileReader Header Path
LIB_PATH = LogFileReader

# Flags to compiler
CFLAGS = -I$(INCLUDE_DIR) -I$(LIB_PATH)/$(INCLUDE_DIR)  -lwiringPi

# Files to compile
SRCS =  $(LIB_PATH)/$(SRC_DIR)/LogFileReader.cpp $(SRC_DIR)/dht11.cpp $(SRC_DIR)/main.cpp

# EXE NAME
EXE = run

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE) $(SRCS)

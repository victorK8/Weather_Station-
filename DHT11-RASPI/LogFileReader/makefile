# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -I

# Path of header files
INCLUDE_PATH = include

# Path of Source Code files
SRC_PATH = src

# Dependencies (Header Files)
DEPS = $(INCLUDE_PATH)/LogFileReader.h

# Source Code Files 
SRC = $(SRC_PATH)/LogFileReader.cpp $(SRC_PATH)/test.cpp

# Name for executable
EXE = test

# Make it!
$(EXE): $(SRC)
	$(CC) -o $(EXE) $(CFLAGS)$(DEPS) $(SRC)

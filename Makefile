.PHONY: build run pack clean

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++11

# Source
SRC = main.cpp

# Here is the name for executable
EXE = tema2

# Build executable
build: $(SRC)
	$(CC) $(CFLAGS) $^ -o $(EXE)

# Run it
run: build
	./$(EXE)

# Pack my homework
pack:
	zip -FSr $(EXE).zip $(SRC) *.h Makefile README

# Clean current directory
clean:
	rm -f *.o $(EXE)

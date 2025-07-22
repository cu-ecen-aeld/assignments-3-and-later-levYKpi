# Makefile for writer


ifdef CROSS_COMPILE
    CC = $(CROSS_COMPILE)gcc
else
    CC = gcc
endif
CFLAGS = -Wall -Wextra -std=c11 -g # Common compilation flags: warnings, C11 standard, debug info

# The name program
TARGET = finder-app/writer
OBJ_FILE = finder-app/writer.o

# Default target (the first one listed)
all: $(TARGET)
	$(CC) -print-sysroot -v

$(TARGET): $(OBJ_FILE)
	$(CC) $(OBJ_FILE) -o $(TARGET)

$(OBJ_FILE): $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c -o $(OBJ_FILE)

# Phony targets: these don't correspond to actual files
.PHONY: CROSS_COMPILE all clean

clean:
	rm -f $(TARGET) $(OBJ_FILE)
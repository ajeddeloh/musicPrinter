#Makefile
CC=gcc
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=muprint
CFLAGS= -std=c11 -Wall -Wextra -Werror -g
LDFLAGS=-lavformat -lavutil

%.o:%.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.PHONY: all
all: $(EXECUTABLE)

.PHONY: clean
clean: 
	rm -f $(OBJECTS) $(EXECUTABLE)

#Makefile
CC=gcc
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=muprint
CFLAGS= -c -std=c99 -Wall -Wextra -Werror

%.o:%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LD_FLAGS) $(OBJECTS) -o $@

.PHONY: all
all:
	$(EXECUTABLE)

.PHONY: clean
clean: 
	rm -f $(EXECUTABLE) $(OBJECTS)

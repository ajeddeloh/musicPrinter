#Makefile
CC=gcc
SOURCES=$(wildcard src/*.c)
HEADERS=$(wildcard src/*.h)
OBJECTS=$(patsubst src/%, build/%, $(SOURCES:.c=.o))
EXECUTABLE=muprint
CFLAGS= -std=c11 -Wall -Wextra -Werror
LDFLAGS=`pkg-config --libs libavformat libavutil`

build/%.o:src/%.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.PHONY: debug
debug: CFLAGS += -g
debug: $(EXECUTABLE)

.PHONY: release
release: CFLAGS += -O2
release: $(EXECUTABLE)

.PHONY: all
all: $(EXECUTABLE)
	echo $(LDFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJECTS) $(EXECUTABLE)

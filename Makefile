CC = gcc
SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)
CFLAGS = -g

all: tse

tse: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

clean:
	rm -f tse

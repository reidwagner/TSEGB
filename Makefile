CC = gcc
SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)

all: tse

tse: $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(SOURCES)

clean:
	rm tse

SOURCES = $(wildcard src/*.c)
SOURCES_NO_MAIN := $(filter-out src/main.c, $(SOURCES))
HEADERS = $(wildcard src/*.h)
TEST_SOURCES = $(wildcard test/*.c)
UNITY_SOURCES = $(wildcard test/unity/*.c)
ASM_SOURCES = $(wildcard assembly/*.s)
ASM_BIN = $(ASM_SOURCES:.s=.bin)

#ZASM = ./zasm-4.0.15-Linux64/zasm
ZASM = ./zasm

CC = gcc
CFLAGS = -g

all: tse

%.bin: %.s
	$(ZASM) -o $@ $<

tse: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

tse_tests: $(SOURCES) $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(TEST_SOURCES) $(SOURCES_NO_MAIN) $(UNITY_SOURCES)

test: tse_tests $(ASM_BIN)
	./tse_tests

clean:
	rm -f tse

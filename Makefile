CC = gcc
CFLAGS = -g -std=c99 -Wall -Wno-missing-braces

BDIR = build
SDIR = src

SOURCES=$(shell find $(SDIR)/ -type f -name '*.c')
OBJECTS=$(patsubst $(SDIR)/%.c, $(BDIR)/%.o, $(SOURCES))


all: dir main

dir:
	mkdir -p $(BDIR)

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $^

$(BDIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -iquote $(SDIR) -c $^ -o $@

clean:
	rm -r build/*
	rmdir build

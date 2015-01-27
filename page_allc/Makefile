
PAGE_SOURCES=$(wildcard page*.c)
PAGE_OBJECTS=$(patsubst %.c,%.o,$(PAGE_SOURCES))

OBJECT_SOURCES=$(wildcard object*.c)
OBJECT_OBJECTS=$(patsubst %.c,%.o,$(OBJECT_SOURCES))

CFLAGS=-g -Wall -O3

all: page_alloc_test object_alloc_test

page_alloc_test: $(PAGE_OBJECTS)

object_alloc_test: $(OBJECT_OBJECTS)


.PHONY: clean
clean:
	-rm $(PAGE_OBJECTS) $(OBJECT_OBJECTS) page_alloc_test object_alloc_test


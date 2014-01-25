CC = gcc
SOURCES = cs322_assn2.c
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -c -g -Wall
LDFLAGS = -lm

distsum: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o distsum
.c.o:
	$(CC) $(CFLAGS) $< -o $@

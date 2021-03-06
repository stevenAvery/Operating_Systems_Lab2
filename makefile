CC = clang
CFLAGS = -O -Wall -Wextra -std=c99 -w
LFLAGS =
LIBS = -lm
SOURCES = myshell.c utility.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = myshell
.PHONY: clean help

default:
	$(CC) $(CFLAGS) $(SOURCES) $< $(LIBS) -o $(EXE)

%.exe : %.o
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and .exe files"

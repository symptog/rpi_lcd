SOURCES= $(wildcard *.c)
BINARIES= $(patsubst %.c, %, $(SOURCES))

CC=gcc
CCFLAGS=-Wall -Wextra -Werror -g 

default: $(BINARIES)

%: %.c
	$(CC) $(CCFLAGS) -o $@ $<

clean:
	rm -f $(BINARIES)

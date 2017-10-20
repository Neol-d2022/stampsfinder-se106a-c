CC=gcc

CFLAGS=-Wall -Wextra -g3
LFLAGS=

OBJS=linkedlist.o main.o mm.o stamp.o vector.o
DEPS=linkedlist.h mm.h stamp.h vector.h
LIBS=-lm

BIN=stampfinder

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(BIN)

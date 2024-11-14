CC= gcc
CFLAGS= -O2 -g -Wall -Iinclude
LFLAGS= -Llib -lSDL2

SRC= $(wildcard src/*.c)

BIN= og

all: $(SRC)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $(BIN)

clean:
	rm src/*.o


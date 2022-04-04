CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
OBJECTS = NodeGame.o Node.o Tile.o LinkedList.o AlphaBeta.o
EXECUTABLE = NodeGame

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

Node.o: Node.c Node.h Tile.h
	$(CC) $(CFLAGS) -c Node.c -o Node.o

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c -o LinkedList.o

Tile.o: Tile.c Tile.h Node.h NodeGame.h
	$(CC) $(CFLAGS) -c Tile.c -o Tile.o

AlphaBeta.o: AlphaBeta.c AlphaBeta.h
	$(CC) $(CFLAGS) -c AlphaBeta.c -o AlphaBeta.o

NodeGame.o: NodeGame.c NodeGame.h Node.h Tile.h NodeActualy.h AlphaBeta.h
	$(CC) $(CFLAGS) -c NodeGame.c -o NodeGame.o
CC=g++
CFLAGS=-Wall -std=c++11

OBJ= recursive.o Recursive.o Network.o Link.o Node.o

recursive: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o recursive

recursive.o: recursive.cc
	$(CC) $(CFLAGS) -c recursive.cc

Recursive.o: Recursive.cc
	$(CC) $(CFLAGS) -c Recursive.cc

Network.o: Network.cc
	$(CC) $(CFLAGS) -c Network.cc

Link.o: Link.cc
	$(CC) $(CFLAGS) -c Link.cc

Node.o: Node.cc
	$(CC) $(CFLAGS) -c Node.cc

clean:
	rm *.o iterative recursive

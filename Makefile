CC=g++
CFLAGS=-Wall -std=c++11

OBJ= enumerating.o Recursive.o Network.o Link.o Node.o

enumerating: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o enumerating

enumerating.o: enumerating.cc
	$(CC) $(CFLAGS) -c enumerating.cc

Recursive.o: Recursive.cc
	$(CC) $(CFLAGS) -c Recursive.cc

Network.o: Network.cc
	$(CC) $(CFLAGS) -c Network.cc

Link.o: Link.cc
	$(CC) $(CFLAGS) -c Link.cc

Node.o: Node.cc
	$(CC) $(CFLAGS) -c Node.cc

clean:
	rm *.o enumerating

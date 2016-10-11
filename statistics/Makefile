CC=g++
CFLAGS=-Wall -std=c++11

OBJ= stat.o

stat: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o stat

stat.o: stat.cc
	$(CC) $(CFLAGS) -c stat.cc

clean:
	rm *.o stat

clean-all:
	rm *.o stat *.txt

CC=g++
CFLAGS=-g -std=c++11 -Wextra -Wunused -Wall -mcmodel=large
LFLAGS= -lm

main: $(OBJ)
	$(CC) $(CFLAGS) main.cpp -o main $(LFLAGS)

clean:
	rm main

clean-all:
	rm main
	rm networks/*
	rm results/* 

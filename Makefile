#Makefile for my Simple Genetic Algorithm

#set up flags
CFLAGS = -std=c++11 -g 
CC = g++ -w 

#build target executable which accounts for all program files in the directory
sga: ga.h ga.cpp main.cpp
	$(CC) -o a.out ga.h ga.cpp main.cpp

clean:
	rm a.out

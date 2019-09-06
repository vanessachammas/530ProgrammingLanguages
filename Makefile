#############################################
# Makefile for CS530 Assignment 2
# Samantha Wagner, Vanessa Chammas
#############################################

CC = g++

cflags = -O



./xed: xed.o functions.o opcode.o
	$(CC) $(cflags) -o xed xed.o functions.o opcode.o

xed.o: xed.cpp
	$(CC) $(cflags) -c xed.cpp           

functions.o: functions.cpp functions.h
	$(CC) $(cflags) -c functions.cpp

opcode.o: opcode.cpp opcode.h
	$(CC) $(cflags) -c opcode.cpp



clean:
	rm -rf xed *o
	rm -f *.sic *.lis

############[ EOF: Makefile ]##############

OBJS = main.o game.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -lncurses $(DEBUG)

proj1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o proj1
main.o : stdafx.h game.h fun.cpp main.cpp
	$(CC) $(CFLAGS) main.cpp
game.o : game.h game.cpp
	$(CC) $(CFLAGS) game.cpp

clean:
	\rm *.o proj1
tar:
	tar cfv proj1.tar main.cpp game.cpp stdafx.h game.h fun.cpp


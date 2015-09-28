OBJS = main.o zipcode.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

hw1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o hw1
main.o : zipcode.h main.cpp
	$(CC) $(CFLAGS) main.cpp
zipcode2.o : zipcode.h zipcode.cpp
	$(CC) $(CFLAGS) zipcode.cpp

clean:
	\rm	*.o hw1
tar:
	tar cfv hw1.tar main.cpp zipcode.cpp zipcode.h

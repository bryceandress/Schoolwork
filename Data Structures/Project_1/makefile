CC=g++
DebugFlag=-g

p1: p1.o term.o
	$(CC) $(DebugFlag) -o p1 p1.o term.o

term.o: term.h term.cpp
	$(CC) $(DebugFlag) -c term.cpp

p1.o: term.h p1.cpp
	$(CC) $(DebugFlag) -c p1.cpp

clean:
	rm -rf *.o p1

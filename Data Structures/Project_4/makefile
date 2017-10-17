CC=g++
DebugFlag=-g

p4: p4.o State.o Date.o
	$(CC) $(DebugFlag) -o p4 p4.o Date.o State.o

State.o: State.h State.cpp
	$(CC) $(DebugFlag) -c State.cpp

Date.o: Date.h Date.cpp
	$(CC) $(DebugFlag) -c Date.cpp

p4.o: State.h Date.h p4.cpp
	$(CC) $(DebugFlag) -c p4.cpp

clean:
	rm -rf *.o p4

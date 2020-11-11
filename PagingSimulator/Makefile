OBJS =  main.o MemSim.o InvPgT.o LRU.o WS.o
HEADER = MemSim.h InvPgT.h LRU.h WS.h

all: psim

CC 	= g++
FLAGS	= -c  -std=c++11

psim: $(OBJS) $(HEADER)
	$(CC) -o psim $(OBJS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

MemSim.o: MemSim.cpp
	$(CC) $(FLAGS) MemSim.cpp

InvPgT.o: InvPgT.cpp
	$(CC) $(FLAGS) InvPgT.cpp

LRU.o: LRU.cpp
	$(CC) $(FLAGS) LRU.cpp

WS.o: WS.cpp
	$(CC) $(FLAGS) WS.cpp



clean:
	rm -f psim $(OBJS)

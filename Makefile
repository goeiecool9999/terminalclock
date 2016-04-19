all: clock
	
clock: clock.o termg.o timeutils.o
	g++ clock.o termg.o timeutils.o -pthread -o clock
clock.o: clock.cpp termg.h timeutils.h
	g++ -c clock.cpp
termg.o: termg.cpp termg.h
	g++ -c termg.cpp
timeutils.o: timeutils.cpp timeutils.h
	g++ -c timeutils.cpp

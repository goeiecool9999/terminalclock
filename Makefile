OBJS=clock.o termg.o timeutils.o
LDFLAGS=-pthread -g
CXXFLAGS=-g -Og -std=c++11

all: clock

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clock: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

#Manual header dependencies. Inexperienced with makefiles.
clock.o: termg.h timeutils.h
termg.o: termg.h
timeutils.o: timeutils.h

clean:
	rm -f *.o clock

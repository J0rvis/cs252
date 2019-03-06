CC = g++
DEPS = Cache.h

%.o: %.cc $(DEPS)
	$(CC) -cc -o $@ $< $(CFLAGS)

Simulation: Simulation.cc Cache.cc Set.cc Block.cc
	$(CC) -o Simulation Simulation.cc Cache.cc Set.cc Block.cc 

Set: Set.cc Cache.cc Block.cc
	$(CC) -o Set Set.cc Cache.cc Block.cc

Block: Block.cc Cache.cc Set.cc
	$(CC) -o Block Cache.cc Set.cc Block.cc	


clean:
	rm Simulation

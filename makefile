CC = g++
CFLAG = -c
OPTFLAGS = -O3

all: bin/mps

bin/mps: main.o maximum_planar_subset.o
	$(CC) $(OPTFLAGS) main.o maximum_planar_subset.o -o $@

main.o: src/main.cpp
	$(CC) $(CFLAG) $< -o $@

maximum_planar_subset.o: src/maximum_planar_subset.cpp src/maximum_planar_subset.h
	$(CC) $(CFLAG) $(OPTFLAGS) $< -o $@

clean:
	rm -rf *.o bin/*

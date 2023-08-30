output: Code_debug.o Code_optimize.o
	g++ Code_debug.o Code_optimize.o -o output

Code_debug.o: Code_debug.cpp
	g++ -Wall Code_debug.cpp

Code_optimize.o: Code_optimize.cpp
	g++ -O2 Code_optimize.cpp

clean:
	rm *.o output
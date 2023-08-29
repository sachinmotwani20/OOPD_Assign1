output: Code_debug.o Code_optimize.o
	g++ Code_debug.o Code_optimize.o -o output

Code_debug.o: Code.cpp
	g++ -Wall Code.cpp

Code_optimize.o: Code.cpp
	g++ -O2 Code.cpp

clean:
	rm *.o output

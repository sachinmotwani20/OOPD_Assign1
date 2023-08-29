output: Code.o
	g++ Code.o -o output

India.o: Code.cpp
	g++ -c Code.cpp

clean:
	rm *.o output
driver: main.o 
	g++ main.o -o driver

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm *.o driver
mapToNum : mapToNum.o Dijkstra.o
	g++ -o mapToNum mapToNum.o Dijkstra.o

mapToNum.o : mapToNum.cpp ./Dijkstra.h
	g++ -c mapToNum.cpp

Dijkstra.o : Dijkstra.h Dijkstra.cpp
	g++ -c Dijkstra.cpp

changeToDis : changeToDis.o DijkstraForDis.o
	g++ -o changeToDis changeToDis.o DijkstraForDis.o

changeToDis.o : ./changeToDis.cpp ./DijkstraForDis.h ./Path.h
	g++ -c ./changeToDis.cpp

DijkstraForDis.o : Dijkstra.h Path.h DijkstraForDis.cpp
	g++ -c DijkstraForDis.cpp

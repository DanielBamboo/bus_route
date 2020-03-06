changeToDis : changeToDis.o DijkstraForDis.o setPath.o
	g++ -o ./build/changeToDis changeToDis.o DijkstraForDis.o setPath.o

changeToDis.o : changeToDis.cpp DijkstraForDis.h setPath.h
	g++ -c changeToDis.cpp

DijkstraForDis.o : Dijkstra.h setPath.h DijkstraForDis.cpp
	g++ -c DijkstraForDis.cpp

setPath.o : setPath.h setPath.cpp
	g++ -c setPath.cpp
clean:
	rm *.o

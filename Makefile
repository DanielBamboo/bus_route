changeToDis : changeToDis.o DijkstraForDis.o newPath.o
	g++ -o changeToDis changeToDis.o DijkstraForDis.o newPath.o

changeToDis.o : ./changeToDis.cpp ./DijkstraForDis.h ./newPath.h
	g++ -c ./changeToDis.cpp

DijkstraForDis.o : Dijkstra.h newPath.h DijkstraForDis.cpp
	g++ -c DijkstraForDis.cpp

newPath.o : newPath.h newPath.cpp
	g++ -c newPath.cpp
clean:
	rm *.o

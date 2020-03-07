doSomeSearching : doSomeSearching.o DijkstraForDis.o setPath.o
	g++ -o ./build/doSomeSearching doSomeSearching.o DijkstraForDis.o setPath.o

doSomeSearching.o : doSomeSearching.cpp DijkstraForDis.h setPath.h ./note/Route_man.h
	g++ -c doSomeSearching.cpp

DijkstraForDis.o : Dijkstra.h setPath.h DijkstraForDis.cpp
	g++ -c DijkstraForDis.cpp

setPath.o : setPath.h setPath.cpp
	g++ -c setPath.cpp


clean:
	rm *.o

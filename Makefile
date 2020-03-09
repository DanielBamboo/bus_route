doSomeSearching : doSomeSearching.o DijkstraForDis.o setPath.o ./file/Read_file_refactor.o
	g++ -o ./build/doSomeSearching doSomeSearching.o DijkstraForDis.o setPath.o ./file/Read_file_refactor.o

doSomeSearching.o : doSomeSearching.cpp DijkstraForDis.h setPath.h ./note/Route_man.h ./file/Read_file_refactor.h
	g++ -c doSomeSearching.cpp

DijkstraForDis.o : Dijkstra.h setPath.h DijkstraForDis.cpp
	g++ -c DijkstraForDis.cpp

setPath.o : setPath.h setPath.cpp
	g++ -c setPath.cpp

Read_file_refactor.o : ./file/Read_file_refactor.h ./file/Read_file_refactor.cpp
	g++ -c ./file/Read_file_refactor.cpp ./file/Read_file_refactor.h

clean:
	rm *.o
	rm ./file/*.o
	rm ./note/*.o

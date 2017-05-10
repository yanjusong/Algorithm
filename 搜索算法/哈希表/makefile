objects = yjs-HashTable.o yjs-Node.o

test-HashTable : test-HashTable.cpp $(objects)
	g++ -std=c++11 test-HashTable.cpp $(objects) -o test-HashTable
yjs-HashTable.o : yjs-HashTable.h yjs-HashTable.cpp
	g++ -std=c++11 -c yjs-HashTable.cpp
yjs-Node.o : yjs-Node.h yjs-Node.cpp
	g++ -std=c++11 -c yjs-Node.cpp

clean:
	rm $(objects) test-HashTable.exe
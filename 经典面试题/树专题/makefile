objects = yjs-OperateTree.o yjs-Node.o mirrorTree.o levelTraversal.o treeHeight.o \
          preOrderTraversal.o inOrderTraversal.o postOrderTraversal.o
operateCPP = yjs-OperateTree.cpp mirrorTree.cpp levelTraversal.cpp treeHeight.cpp \
             preOrderTraversal.cpp inOrderTraversal.cpp postOrderTraversal.cpp

main : main.cpp $(objects)
	g++ -std=c++11 main.cpp $(objects) -o main

yjs-Node.o : yjs-Node.h yjs-Node.cpp
	g++ -std=c++11 -c yjs-Node.cpp
yjs-OperateTree.o : yjs-OperateTree.h $(operateCPP)
	g++ -std=c++11 -c $(operateCPP)

clean:
	rm $(objects) main.exe
all: matrix listarray graph listlinear jam mesinkata queue point tree stack fileio

matrix:
	gcc -Wall -Wextra matrix.c driver/driver-matrix.c -o driver-executable/driver-matrix

listarray:
	gcc -Wall -Wextra listarray.c driver/driver-listarray.c -o driver-executable/driver-listarray

graph:
	gcc -Wall -Wextra graph.c driver/driver-graph.c -o driver-executable/driver-graph

listlinear:
	gcc -Wall -Wextra listlinear.c driver/driver-listlinear.c -o driver-executable/driver-listlinear

jam:
	gcc -Wall -Wextra jam.c driver/driver-jam.c -o driver-executable/driver-jam

mesinkata:
	gcc -Wall -Wextra mesinkata.c mesinkar.c driver/driver-mesinkata.c -o driver-executable/driver-mesinkata

queue:
	gcc -Wall -Wextra prioqueuechar.c driver/driver-prioqueuechar.c -o driver-executable/driver-queue

stack:
	gcc -Wall -Wextra stack.c driver/driver-stack.c -o driver-executable/driver-stack

tree:
	gcc -Wall -Wextra tree.c listrek.c driver/driver-tree.c -o driver-executable/driver-tree

point:
	gcc -Wall -Wextra point.c driver/driver-point.c -o driver-executable/driver-point

fileio:
	gcc -Wall -Wextra driver/driver-fileio.c ../fileio.c -o driver-executable/driver-fileio

clean:
	rm driver-executable/*
	rm *.o

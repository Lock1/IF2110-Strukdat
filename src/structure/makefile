all: matrix listarray graph listlinear jam mesinkata

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

clean:
	rm driver-executable/*
	rm *.o

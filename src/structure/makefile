all: matrix-listarray

matrix-listarray:
	gcc -Wall -Wextra matrix.h matrix.c driver/driver-matrix.c -o driver-executable/driver-matrix
	# TODO

clean:
	rm driver-executable/*
	rm *.o

listarray:
	gcc -Wall -Wextra listarray.h listarray.c driver/driver-listarray.c -o driver-executable/driver-listarray

all:
	rm willy; gcc -Wall -Wextra src/*.c -o willy
clean:
	rm *.o

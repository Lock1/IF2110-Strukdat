all:
	rm willy; gcc -Wall -Wextra src/*.c src/structure/*.c -o willy
clean:
	rm *.o

CC = gcc

main : main.c function.o
	$(CC) -o $@ $^

function.o : function.c function.h
	$(CC) -c function.c -o function.o

clean :
	rm main *.o
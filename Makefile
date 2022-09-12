$(CC) = gcc

demo: demo.o simple_crypto.o 
		$(CC) demo.o simple_crypto.o -o demo

demo.o: demo.c simple_crypto.h
		$(CC) -c demo.c

simple_crypto.o: simple_crypto.c simple_crypto.h
		$(CC) -c simple_crypto.c

clean:
		rm *.o demo
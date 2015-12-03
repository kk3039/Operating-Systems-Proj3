

main: main.o testq.o prob2.o
	gcc -o main -pthread main.o testq.o prob2.o

main.o: main.c testq.h prob2.h
	gcc main.c -lpthread -c

testq.o: testq.c testq.h
	gcc testq.c -lpthread -c

prob2.o: prob2.c testq.h prob2.h
	gcc prob2.c -lpthread -c

clean:
	rm *.o main

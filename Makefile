all: index
	gcc -o run.out index.o

index: index.c
	gcc -c index.c

clean:
	rm *.o *.out

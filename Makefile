run.out: index.o input.o base.o
	gcc -o run.out index.o input.o base.o

index.o: index.c index.h
	gcc -c index.c

input.o: input.c input.h
	gcc -c input.c

base.o: base.c base.h
	gcc -c base.c

clean:
	rm *.o *.out

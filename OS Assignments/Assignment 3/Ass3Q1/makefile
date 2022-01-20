all: t1 t2 run

t1: test.c
	gcc test.c -lgomp -o test

t2: test2.c
	gcc test2.c -lgomp -o test2

clean:
	rm test test2

run:
	./test && ./test2
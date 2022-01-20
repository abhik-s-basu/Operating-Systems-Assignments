targ: a1a a1b

a1a: a1a.c
	# gcc -o a1a a1a.c -Wall
	gcc -E a1a.c -o a1a.i
	gcc -S a1a.c 
	gcc -c a1a.c
	gcc a1a.c -o a1a 
	./a1a

a1b: a1b.c
	# gcc -o a1b a1b.c -Wall
	gcc -E a1b.c -o a1b.i
	gcc -S  a1b.c 
	gcc -c a1b.c
	gcc a1b.c -pthread -o  a1b
	./a1b
clean: 
	-rm *.o a1a a1b *.s *.i











	
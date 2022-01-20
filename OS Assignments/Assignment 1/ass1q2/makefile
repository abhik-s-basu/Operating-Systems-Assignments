targ: q2 

q2: q2.c
	nasm -f elf64 -o b.o b.asm
	gcc -no-pie  q2.c b.o -o q2
	clear
	./q2

clean: 
	-rm *.o q2 














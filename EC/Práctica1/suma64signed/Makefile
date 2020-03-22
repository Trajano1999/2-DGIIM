suma64signed: suma64signed.o
	ld -m elf_i386 suma64signed.o -o suma64signed

suma64signed.o: suma64signed.s 
	as --32 -g suma64signed.s -o suma64signed.o

clean:
	rm *.o

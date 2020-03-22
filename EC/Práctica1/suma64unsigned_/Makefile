suma64unsigned: suma64unsigned.o
	ld -m elf_i386 suma64unsigned.o -o suma64unsigned

suma64unsigned.o: suma64unsigned.s 
	as --32 -g suma64unsigned.s -o suma64unsigned.o

clean:
	rm *.o

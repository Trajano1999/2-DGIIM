media64signed: media64signed.o
	ld -m elf_i386 media64signed.o -o media64signed

media64signed.o: media64signed.s 
	as --32 -g media64signed.s -o media64signed.o

clean:
	rm *.o

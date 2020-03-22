.section .data
lista: .int 1, 2, 10, 1, 2, 0b10, 1, 2, 0x10      #0b10 = 2; 0x10 = 16
longlista: .int (.-lista)/4
resultado: .int -1
formato: .ascii "resultado = %d = %0x hex\n\0"

.section .text
main: .global main
     pushl longlista
     pushl $lista
     call suma

     add $8, %esp
     mov %eax, resultado

     push %eax
     push %eax
     push $formato
     call printf
     add $12, %esp

     pushl $0
     call exit

suma: 
     push %ebp
     mov %esp, %ebp

     push %ebx
     mov 8(%ebp), %ebx
     mov 12(%ebp), %ecx

	mov $0, %eax
	mov $0, %edx

bucle:
	add (%ebx,%edx,4), %eax
	inc %edx
	cmp %edx,%ecx
	jne bucle

	pop %ebx
     pop %ebp
	ret
     
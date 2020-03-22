.section .data
lista: .int 1, 2, 10, 1, 2, 0b10, 1, 2, 0x10
longlista: .int (.-lista)/4
resultado: .int -1
formato: .ascii "resultado = %d = %0x hex\n\0"

int suma(int *array, int len){
    int i, res=0;
    for(i=0; i<len; i++)
        res += array[i];
    return res;
}

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

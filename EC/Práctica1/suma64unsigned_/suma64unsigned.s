.section .data
	.macro linea
		.int 134217728, 134217728, 134217728, 134217728				
														
	.endm													
lista: .irpc i, 12345678
		linea
	.endr
longlista:	.int (.-lista)/4								# Para calcular la longitud de la lista se resta . que indica donde comienza la lista menos lista
														# que apunta al ultimo elemento y posteriormente lo dividimos entre 4 que es el numero de bytes que ocupa un int.

resultado:	.quad -1 										# quad es una variable para almacenar enteros en 64 bits.

.section .text
_start:	.global _start										# Aqui comienza el código, es equivalente a la funcion main() en C.
	mov    $lista, %ebx										# Mueve la dirección donde empieza la lista en %ebx.
	mov	longlista, %ecx									# Mueve la longitud de lista a %ecx.
	call suma 											# Llamada a la función suma.
	mov %eax, resultado										# Mueve %eax a resultado. Asi, la primera mitad de resultado almacena ese valor mientras que
	mov %edx, resultado+4									# en esta instruccion, le almacenamos a la segunda parte de resultado el acarreo que tenia.
														# Así, resultado es una variable quad que almacena 64 bits, en la que los primeros 32 son de resultado 
														# y los 32 siguientes son del acarreo.

	mov $1, %eax											# Ajuste final.
	mov $0, %ebx
	int $0x80												# Fin de programa.

suma:													# Comienza la funcion suma.
	push %esi												# Aplicamos la instruccion push a %esi para usarlo en la función conservando su valor.
														# A continuacion debemos inicializar a 0 los registros que vamos a usar.
	mov $0, %eax											# %eax es el acumulador.
	mov $0, %edx											# %edx es la suma de acarreos.
	mov $0, %esi											# %esi es el índice.

bucle:													# En este bucle se realiza la suma de los n valores.
	add (%ebx,%esi,4), %eax									# Esta operacion va iterando y sumando todos los elementos que estan en la lista.
														# Esto es, %ebx+4*%esi, recordemos que %ebx tiene almacenada la dirección de inicio de lista y 
														# %esi es el índice (que se va incrementando cada paso).
	adc $0, %edx											# Suma de acarreo ya que tiene en cuenta los flags y se almacena en el registro %edx.
	inc       %esi											# Incrementa del índice.
	cmp  %esi,%ecx											# Compara %esi y %ecx, esto es, realiza la operacion %ecx - %esi y tiene en cuenta el flat de estado.
	jne bucle												# Realiza el salto al bucle cuando el valor de la resta anterior es distinto a 0. 

	pop %esi												# Se le hace un pop a %esi para recuperar el valor que se perdió al realizar el push.
	ret													# Retorno a la función.
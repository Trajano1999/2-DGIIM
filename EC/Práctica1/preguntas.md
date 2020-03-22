# Sesión de depuración de "saludo.s"


## Pregunta 1
### ¿Qué contiene EDX tras ejecutar mov longsaludo, %edx?
EAX: 0x1c = 28 (esto es el valor de longsaludo, es decir, la longitud de la cadena de caracteres "saludo")

### ¿Para qué necesitamos esa instrucción, o ese valor?
Para imprimir el valor de saludo, desde su dirección de inicio en %ecx hasta su dirección final %ecx+%edx

## ¿De dónde se obtiene el valor de longsaludo?
Se obtiene de longsaludo: .int	.-saludo, que realiza la resta de la dirección actual menos la dirección del comienzo de saludo dando como resultado la longitud de la cadena de caracteres


## Pregunta 2
### ¿Qué contiene ECX tras ejecutar `mov $saludo, %ecx`?
0x8049097: que es la dirección de memoria en la que comienza la variable saludo

## Realizar un dibujo a escala de la memoria del programa, indicando dónde empieza el programa, dónde empieza saludo y dónde está el tope de la pila

|Dirección|Contenido|
|---|---|
| ...| ... |
|0x0804874| .text |
| ... | ... |
|0x8048095|int $0x80|
| ... | ... |
|0x8049097| .data |
|...|...|
|0xfffd080| (ESP)|


## Pregunta 3
### ¿Qué sucede si se elimina el símbolo de dato inmediato ($) de la instrucción anterior, (`mov saludo, %ecx`)? Realizar la modificación, indicar el contenido de ECX en hexadecimal, explicar por qué no es el mismo en ambos casos. Concretar de dónde viene el nuevo valor (obtenido sin usar $)
Valor de ECX: 0x616c6f48, que es el contenido de la variable saludo, y no su dirección de memoria que es lo que hubiesemos encontrado si hubiesemos puesto el simbolo $


## Pregunta 4
### ¿Cuántas posiciones de memoria ocupa la variable longsaludo?
Al ser int ocupa 4 bytes

### ¿Y la variable saludo?
Un byte por char, en total longsaludo ocupa 28 bytes

### ¿Cuántos bytes ocupa por tanto la sección de datos?
28 + 4 = 32 B


# Sesión de depuración de suma.s


## Pregunta 1
### ¿Cual es el contenido de EAX justo antes de ejecutar la instruccion RET para esos componentes de la lista concretos? Incluye cuanto valen 0b10, 0x10 y (.-lista)/4
EAX: 0x25 = 37
0b10 = 2080480a0
0x10 =  16
longlista: 9


## Pregunta 2
### ¿Qué valor en hexadecimal se obtiene en resultado si se usa la lista de 3 elementos .int 0 0xffffffff, 0xfffffffff, 0xffffffff? ¿Por qué es diferente del que se obtiene haciendo la suma a mano?
-3, porque 0xffffffff = -1, ya que es una representación en complemento a 2

### Indicar qué valores va tomando EAX en cada iteración del bucle. Fijarse en si se van activando los flags CF y OF o no tras cada suma
|It|EAX (hex)|EAX (dec)|Flags|
|---|---|---|---|
|0|0x0|0||
|1|0xffffffff|-1|---|
|2|0xfffffffe|-2|CF|
|3|0xfffffffd|-3|CF|


## Pregunta 3
### ¿Qué dirección se le ha asignado a la etiqueta suma? ¿Y al bucle? ¿Cómo se ha obtenido esa información?
Suma: 0x8048095
Bucle: 0x80480a0
Se ha obtenido con la orden objdump -D suma


## Pregunta 4
### ¿Para qué usa el procesador los registros EIP y ESP?
EIP (registro de instrucción): almacena la dirección de memoria de la siguiente instrucción que se va a ejecutar.
ESP (puntero de pila): almacena la dirección de memoria del inicio de la pila.


## Pregunta 5
### ¿Cuál es el valor de ESP antes de ejecutar CALL?
El valor de ESP antes de ejecutar CALL es 0xffffd080

### ¿Y cuál antes de ejecutar RET?
El valor de ESP antes de ejecutar RET es 0xffffd07c

### ¿En cuanto se diferencian ambos valores? ¿Por qué?
Se diferencian en 4, porque cuando se llama a función suma se almacena la dirección de retorno en la pila y esta dirección ocupa 4 bytes

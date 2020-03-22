# BP4

Esperar al final para optimizar dificulta el proceso de optimización.

Optimizaciones desde el Lenguaje de Alto Nivel (OHLL)
- Optimizaciones aplicables a cualquier procesador (OGP).
- Optimizaciones específicas para un procesador (OEP).

Optimizaciones desde el Lenguaje Ensamblador (OASM)
- Optimizaciones aplicables a cualquier procesador (OGP).
- Optimizaciones específicas para un procesador (OEP).

|option|optimization level|execution time|code size|memory usage|compile time|
|--- |--- |--- |--- |--- |--- |
|-O0|optimization for compilation time (default)|+|+|-|-|
|-O1 or -O|optimization for code size and execution time|-|-|+|+|
|-O2|optimization more for code size and execution time|--||+|++|
|-O3|optimization more for code size and execution time|---||+|+++|
|-Os|optimization for code size||--||++|

### Optimización de la Ejecución 

--> Intentar cambiar las divisiones por multiplicaciones ya que suele haber más unidades funcionales para estas y tardan menos.
--> A veces es más rápido utilizar desplazamientos y sumas para realizar una multiplicación por una constante entera que utilizar la instrucción IMUL.

El desenrollado de bucles reduce el número de saltos y de comparaciones del bucle,
aumenta la oportunidad de encontrar instrucciones independientes y facilita la posibilidad de insertar instrucciones para ocultar las latencias. La contrapartida es que aumenta el tamaño de los códigos. Ejemplo:

```
for (i=0; i<ARR; i++) {
    tmp += a[i]*b[i];
}

for (i=0; i<ARR; i+=4) {
    tmp0 += a[i]*b[i];
    tmp1 += a[i+1]*b[i+1];
    tmp2 += a[i+2]*b[i+2];
    tmp3 += a[i+3]*b[i+3];
}
```
--> Si el compilador no puede resolver los punteros (código ambiguo), se inhiben ciertas optimizaciones del compilador:
* Asignar variables durante la compilación.
* Realizar cargas de memoria mientras que un almacenamiento está en marcha.

--> Si no se utilizan punteros el código es más dependiente de la máquina, y a veces las ventajas de no utilizarlos no compensa. 

Como evitar código ambiguo y sus efectos:
- Utilizar variables locales en lugar de punteros.
- Utilizar variables globales si no se pueden utilizar las locales.
- Poner las instrucciones de almacenamiento después o bastante antes de las de carga de memoria. 

Conclusión nuestra: Sustituir punteros por una variable local.

### Optimización del Acceso a Memoria

Alineamiento de datos: como para el acceso a un dato de la caché necesitamos toda la linea, es mucho mejor que el código necesario esté en una misma linea, y para ello intentamos siempre comenzar la linea.

NO ENTENDEMOS LAS COLISIONES DE CACHÉ.
Utilizar datos del mismo tamaño y direcciones alineadas y
poner los loads tan lejos como sea posible de los stores a la misma área
de memoria 

Dependiendo de lo que nos interese declaramos el struct de una u otra forma. En la primera, como queremos recorrer 500 elementos seguidos de a, es mejor declarar el for de esa forma, ya que si lo declarases de la segunda forma, encontrariamos un b entre cada 2 a. La segunda forma se utiliza en ese código porque para cada iteración encontramos un b seguido de cada a.

```
struct {
    int a[500];
    int b[500];
} s;

for (i=0; i<500; i++)
    s.a[i]=2*s.a[i];

for (i=0;i<500;i++)
    s.b[i]=3*s.b[i];

//----------------------

struct {
    int a;
    int b;
} s[500];

for (i=0;i<500;i++){
    s[i].a+=5;
    s[i].b+=3;
}
```

Una matriz se almacena en cache por filas, esto hace que para recorrerla sea más eficiente recorrerla por filas ya que cada vez que accedemos a caché tomamos valores proximos en memoria del valor que buscamos, y como está almacenado por filas, esto es beneficioso, mientrad que si lo recorremos por columnas, esos valores nos son innecesarios.

Los atascos se producen por: 
    -Carga larga que sigue de un almacenamiento pequeño.
    -Carga pequeña sigue a un almacenamiento largo.
    -Datos del mismo tamaño se almacenan y luego se cargan en direcciones solapadas pero no alineadas.
Poner LOAD lejos de STORE.
Para evitarlos: Utilizar datos del mismo tamaño y direcciones alineadas y
poner los loads tan lejos como sea posible de los stores a la misma área
de memoria.

El procesador, mediante las correspondientes instrucciones de precaptación, carga zonas de memoria en cache antes de que se soliciten (cuando hay ancho de banda disponible).

Una instrucción de prefetch carga una línea entera de cache.
El aspecto crucial al realizar precaptación es la anticipación con la que se
pre-captan los datos. En muchos casos es necesario aplicar una estrategia
de prueba y error.

```
for (i=0; i<1000; i++){
    x=function(matriz[i]);
    _mm_prefetch(matriz[i+16],_MM_HINT_T0);
}
``` 
En el ejemplo se precapta el dato necesario para la iteración situada a 16 iteraciones (en el futuro).
En un prefetch no se generan faltas de memoria (es seguro precaptar más allá de los límites del array)

### Optimización de Saltos

```
if (t1==0 && t2==0 && t3==0)

if ((t1 | t2 | t3)==0)
```

Cada una de las condiciones separadas por && se evalúa mediante una nstrucción de salto distinta. Si las variables pueden ser 1 ó 0 con la misma probabilidad, la posibilidad de predecir esas instrucciones de salto no es muy elevada.
Si se utiliza un único salto, la probabilidad de 1 es de 0.125 y la de 0
de 0.875 y la posibilidad de hacer una buena predicción aumenta.
Mediante la instrucción de movimiento condicional se pueden evitar los saltos

Se puede reducir el número de saltos de un programa reordenando el switch, en el caso de que alguna opción se ejecute mucho más que las otras.

NO SABEMOS POR QUÉ EN LA DIAPO 22 PONE EL IF EN VEZ DE PONER ESA COMPROBACIÓN LA PRIMERA.

CMOVcc hace la transferencia de información si se cumple la condición indicada en cc.
FCMOVcc es similar a CMOVcc pero utiliza operandos en coma flotante.
SETcc es otro ejemplo de instrucción con predicado que puede permitir reducir el número de instrucciones de salto.

## PREGUNTAS DEL EXAMEN

-Instrucciones que mejoran la optimización: 
-O3 es la mejor opcion para compilar mientras que la opción que genera menos instrucciones es -Os.
-Orden instrucciones de un switch: La más probable arriba.
-Mejor forma de multiplicar 3 matrices: I,K,J
for i
    for k
        for j
            a[i+j] = b[i+k] + c[j+k]
-Como ordenar un struct para hacer un sumatorio: ¿?
-A que funcion corresponde el código en ensamblador: ¿cmov en ensamblador?
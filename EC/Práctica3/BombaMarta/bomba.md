*Juan Manuel Mateos Pérez*

#PRÁCTICA 3

### Primera Depuración
Tenemos el ejecutable de la bomba (que hemos creado con `gcc -m32 bomba.cpp -o bomba`), y para empezar a descifrarlo, desde la terminal ejecutamos `bomba` con la orden `gdb`.

En esta primera depuración que realizo simplemente me hago una primera idea del programa. Para poder comenzar a depurar debemos poner un **breakpoint** al inicio del main, con el comando `break main`.

Ahora introducimos `run` y vamos haciendo `next i`, para ir desplazandonos por el programa. El programa comienza pidiendome una **contraseña**, que, al no tener conocimiento de cual es, introduzco la contraseña `hola`, por ejemplo. Seguimos introduciendo `ni` hasta encontrar un `strncmp`. Llegado ese punto nos damos cuenta de que después de eso nos va a terminar mandando a la funcion `boom`, tras la cual nos explota la bomba. Por ello, debemos introducir un breakpoint antes de esa función.


### Segunda Depuración
Iniciamos una segunda depuración, en la que nos paramos en el `strncmp` y ponemos `stepi` para meternos dentro de la función, una vez dentro introducimos `break` para poner un breakpoint. Y volvemos a recorrer la función con `stepi` buscando alguna pista donde encontrar contraseña. 

Encontramos un `mov` y con la orden `x/cb $eax` mostramos el contenido y nos damos cuenta de que hemos accedido a `0x56557008 <password>:  112 'p'` , lo que nos confirma que estamos en la primera posición de memoria de la contraseña. 
Nos damos cuenta de que si introducimos `x/cb 0x56557009` en el gdb nos muestra el contenido de esa posición de memoria, así que como sabemos que en las siguientes posiciones tenemos las siguientes letras, y cada char ocupa 1B, vamos avanzando una a una hasta llegar a un salto de linea y conseguimos la contraseña: **patatilla**.

Volvemos a ejecutar el gdb introduciendo la contraseña, y vemos que es correcta, ya que no se mete en la función `boom`. 

##### Siguiente paso: 
Seguir descifrando la contraseña. Ahora nos pide que introduzcamos 4 números del 0 al 9, y comprobamos que, efectivamente entra en un bucle donde nos va pidiendo los datos. Cuando los hemos terminado de introducir nos pide la nueva contraseña y recorre un bucle 4 veces en el que realiza un `scanf`, por lo que sabemos que nos pide 4 datos, concretamente 4 enteros, con ello tenemos que la contraseña tiene 4 posiciones en las cuales se almacenan enteros.

En la primera entrada de datos introducimos **5 2 0 9** y en la segunda **4 8 1 5**. Una vez introducidos los dos "vectores" nos damos cuenta de que se hace una llamada a la funcion `or`. 
En la siguiente depuración haremos un `stepi` en dicha función. Una vez dentro y viendo la estructura del código podemos deducir que es un bucle en el que se modifican las posiciones de los elementos, viendo además que trabaja sobre el primer vector que hemos introducido, llegamos a concluir que está ordenando el vector. 

Volvemos a depurar y vemos que se hace una llamada a la funcion `ig`, tras la cual se ejecuta `boom`. Una vez nos damos cuenta de esto, volvemos a ejecutar el gdb introduciendo los mismos datos y haremos un `stepi` en la funcion `ig`. 

Dentro de la función mostramos con `display $eax` el valor de `eax` en cada iteración, es decir, `display` muestra el valor que compara de la contraseña con el `edx` que nos muestra nuestra cadena introducida, por lo que en cada `cmp %eax,%edx` mostramos los valores de ambas variables. Desciframos la contraseña sabiendo que el valor correcto (ya que compara el segundo vector con ese) es el de `eax`. Mostramos los resultados de la orden `display` en las cuatro ejecuciones de `cmp`:

**Primera ejecución**: 
    `(gdb) display $eax`
    `1: $eax = 0`
    `(gdb) display $edx`
    `2: $edx = 4`
**Segunda ejecución**:
    `0x565558b2 in ig ()`
    `1: $eax = 2`
    `2: $edx = 8`
**Tercera ejecución**:
    `0x565558b2 in ig ()`
    `1: $eax = 5`
    `2: $edx = 1`
**Cuarta ejecución**:
    `0x565558b2 in ig ()`
    `1: $eax = 9`
    `2: $edx = 5`

Una vez adivinado el código vamos a comprobar que la segunda contraseña es el vector introducido en primer lugar, pero ordenando sus posiciones de menor a mayor. 

Concluimos la Práctica diciendo la solucion del programa:

|contraseña|codigo|
|---|---|
|patatilla|0 2 5 9|
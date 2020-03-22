#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define WSIZE 8*sizeof(unsigned)
#define SIZE 1<<20

unsigned lista[SIZE];
int resultado=0;

///Esta es la primera version, la cual utiliza un bucle for para calcular la paridad de cada elemento.
int parity1(unsigned* vector, int longitud){
    int j, res = 0, val = 0;
    for(int i=0; i<longitud; i++){
		for(j=0, val=0; j<WSIZE; j++){
			unsigned mask=0x1 << j;						
			val^= (vector[i] & mask) != 0;			
		}
		res+=val;
    }
    return res;
}

///Esta es la segunda version, la cual utiliza un bucle while para calcular la paridad de cada elemento.
int parity2(unsigned* vector, int longitud){
    int j, res = 0, val = 0;
    for(int i=0; i<longitud; i++){
		j=0;
		while(j < WSIZE){
			unsigned mask=0x1 << j;						
			val^= (vector[i] & mask) != 0;			
			j++;
		}
		res+=val;
    }
    return res;
}

///Esta es la tercera version, la cual compara bit a bit.
int parity3(unsigned* vector, int longitud){
	unsigned res = 0, val = 0, mask=0x1, x;

	for(int i=0; i<longitud; i++){
		x = vector[i];
		while(x){									
			val^=x;									
			x>>=1;									
		}
		res+=(val & mask);
		val=0;
	}
	return res;
}

///Esta es la cuarta version, la cual utiliza asm para calcular la paridad de cada elemento.
int parity4(unsigned* vector, int longitud){
	unsigned res = 0, val = 0, mask=0x1, x;

	for(int i=0; i<longitud; i++){
		x = vector[i];
		val=0;
		asm("\n"
		".ini3:			\n\t"
			"xor %[x], %[v]	\n\t"				
			"shr %[x]	\n\t"					
			"jnz .ini3	\n\t"
			"and $0x1, %[v]	\n\t"
			: [v] "+r" (val)
			: [x] "r" (x)
			);		
		
		res+=val;
	}
	return res;
}

/*
Esta es la quinta version, la cual compara x consigo misma desplazada unos lugares dependientes de cada iteracion.
Cabe destacar que en esta version no se necesita ninguna variable auxiliar.
*/
int parity5(unsigned* vector, int longitud){
	unsigned res = 0, mask=0x1, x;

	for(int i=0; i<longitud; i++){
		x = vector[i];
		for(int j=16; j>=1; j/=2)					
			x^=x>>j;							
		res+=(x & mask);						
	}
	return res;
}

///Esta es la sexta version, el procedimiento es similar al anterior pero con asm.
int parity6(unsigned* vector, int longitud){
	unsigned res = 0, mask=0x1, x;

	for(int i=0; i<longitud; i++){
		x=vector[i];
		asm("\n"
		"mov	%[x], %%edx	\n\t"				
		"shr	$0x10, %[x]	\n\t"				
		"xor	%[x], %%edx	\n\t"				
		"shr	$0x08, %[x]	\n\t"
		"xor    %[x], %%edx	\n\t"
		"setpo  %%dl		\n\t" 				
		"movzx %%dl, %[x]	\n\t"
		: [x] "+r" (x)
		:
		: "edx"
		);
		res+=x;
	}
	return res;
}

void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;	
    long tv_usecs;

    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);
    printf("resultado = %d\t", resultado);
    printf("%s%9ld\n", msg, tv_usecs);
}

int main(){
    for (int i=0; i<SIZE; i++)
		lista[i]=i;

    crono(parity1, "parity1 (bucle for           )");
    crono(parity2, "parity2 (bucle while         )");
    crono(parity3, "parity3 (comparacion al final)");
    crono(parity4, "parity4 (instrucciones asm   )");
    crono(parity5, "parity5 (arbol               )");
    crono(parity6, "parity6 (arbol en asm        )");
    printf("SIZE/2=%d\n", (SIZE)/2);
}  

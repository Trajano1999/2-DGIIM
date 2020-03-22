#include <stdio.h>  // para printf()
#include <stdlib.h> // para exit()
#include <string.h> // para strncmp()/strlen()

char password[] = "estaeslabomba\n";
int codigo = 1111;

void bomba(){
	printf("\n");
	for(int i=0; i<6; i++)
		printf("**********************************************************************\n");
	printf("******************** ¡¡ LA BOMBA HA EXPLOTADO !! *********************\n");
	for(int i=0; i<6; i++)
		printf("**********************************************************************\n");
	printf("\n");
	exit(-1);
}

void desactivada(){
	printf("\n");
	for(int i=0; i<6; i++)
		printf("**********************************************************************\n");
	printf("*************** ¡¡ LA BOMBA HA SIDO DESACTIVADA !! *******************\n");
	for(int i=0; i<6; i++)
		printf("**********************************************************************\n");
	printf("\n");
	exit(0);
}

void perdertiempo(int cod){
	int aux = 0;
	for(int i=1; i<cod; i++){
		if(cod%i == 0)
			aux++;	
	}
}

int comprobarcontrasena(char pass[]){
	if(strcmp(pass, password) == 0)
		return 0;
	return 1;
}

int main(){
#define SIZE 100
	char pass[SIZE];
	int cod;
#define TLIM 5

	printf("\nIntroduce la contraseña: ");
	fgets(pass, SIZE, stdin);
	
	printf("Introduce el codigo: ");
	scanf("%i", &cod);

	perdertiempo(cod);

	if (comprobarcontrasena(pass) == 0 && cod == codigo)
		desactivada();
	else
		bomba();
}
#include <stdio.h> // para printf()
#include <stdlib.h> // para exit()
#include <string.h> // para strncmp()/strlen()
char password[]="patatilla\n";
void boom(){
	printf("###############\n"); 
	printf("        ,--.!, \n");
	printf("     __/   -*- \n");
	printf("   ,d08b.  '|` \n");
	printf("   0088MM      \n");
	printf("   `9MMP'      \n");
	printf("###############\n");
	exit(-1);
}
void defused(){
	 printf("·························\n");
	 printf("··· bomba desactivada ···\n");
	 printf("·························\n");
	 exit(0);
}
int * or(int vector[10]){
	int i, a, min;
  	for (i=1; i < 4; i++) {
    		min = vector[i];
    		a = i-1;
    		while (a >= 0 && vector[a] > min) {
      			vector[a + 1] = vector[a];
      			a--;
    		}
    		vector[a+1] = min;
  	}
	return vector;
}
int ig(int vec[4], int vec2[4]){
	int correcto=0;
	for (int i=0; i<4 ; i++){
		if (vec[i] != vec2[i])
			correcto = 1;
	}
	return correcto;
}
int main(){
	#define SIZE 100
	char pass[SIZE];
	int patata[4];
	int patato[4];
	
 	printf("Introduce la contraseña: ");
 	fgets(pass,SIZE,stdin);
	if (strncmp(pass,password,strlen(password)))
 		boom();

	printf("Introduce 4 numeros del 0 al 9: ");
 	for (int i=0; i<4 ; i++){
		scanf("%i", &patata[i]);
	}
	printf("Introduce contraseña: ");
 	for (int i=0; i<4 ; i++){
		scanf("%i", &patato[i]);
	}
	if (ig(patato, or(patata)) == 1)
 		boom();
 	
 	defused();
}

 /**
   @author Grupo ALGO
   @file Comparación de preferencias
*/

#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <fstream>
using namespace std;

#define TAM 25
int casosEntrada[TAM]={1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000};

//Devuelve el número de inversiones por el algoritmo de Fuerza Bruta
int compararPreferenciasFB(int *v, int n);

//Devuelve el número de inversiones por algoritmo Divide y Vencerás
int compararPreferenciasDyV(int *v, int i, int f);

//Devuelve el número de inversiones entre las dos mitades a mezclar
int inversiones_merge(int *v, int i, int m, int f);

//Mezcla dos vectores ordenador en uno nuevo ordenado
void merge(int *v, int i, int m, int f);

//Genera un número uniformemente distribuido en el intervalo [0,1) a partir de un generador
double uniforme();


int main(int argc, char * argv[]){
	ofstream salidaFB, salidaDyV;
  chrono::high_resolution_clock::time_point tAntesFB, tDespuesFB, tAntesDyV, tDespuesDyV;
  unsigned long tAcumuladoFB, tAcumuladoDyV, tMedioFB, tMedioDyV;

	if (argc != 3){
  	cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
  	cerr<<argv[0]<<" FicheroSalidaFB FicheroSalidoDyV\n\n";

    return -1;
  }

	srandom(time(NULL));

	salidaFB.open(argv[1]);
	if (!salidaFB.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

  salidaDyV.open(argv[2]);
	if (!salidaDyV.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[2]<<"\n\n";
		return 0;
	}

	for(int caso=0; caso<TAM; caso++){
		int n = casosEntrada[caso];
		int * T = new int[n];
		assert(T);
    for (int j=0; j<n; j++) T[j]=j;

    tAcumuladoFB = 0;
    tAcumuladoDyV = 0;

    cout << "Caso " << caso+1 << " de " << TAM << endl;
    for(int iteracion=0; iteracion<15; iteracion++){

      //algoritmo de random shuffling the Knuth (permutación aleatoria)
      for (int j=n-1; j>0; j--) {
         double u=uniforme();
         int k=(int)(j*u);
         int tmp=T[j];
         T[j]=T[k];
         T[k]=tmp;
      }

      tAntesFB = chrono::high_resolution_clock::now();
      compararPreferenciasFB(T, n);
      tDespuesFB = chrono::high_resolution_clock::now();
      tAcumuladoFB += chrono::duration_cast<std::chrono::microseconds>(tDespuesFB - tAntesFB).count();

    	tAntesDyV = chrono::high_resolution_clock::now();
    	compararPreferenciasDyV(T, 0, n-1);
    	tDespuesDyV = chrono::high_resolution_clock::now();
    	tAcumuladoDyV += chrono::duration_cast<std::chrono::microseconds>(tDespuesDyV - tAntesDyV).count();

    }

    tMedioFB = tAcumuladoFB/15;
    tMedioDyV = tAcumuladoDyV/15;

  	salidaFB << n << " " << tMedioFB << endl;
    salidaDyV << n << " " << tMedioDyV << endl;
  	delete [] T;
	}

	salidaFB.close();
  salidaDyV.close();

	return 0;
}

int compararPreferenciasFB(int *v, int n){
  int inversiones = 0;
  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      if(v[i]>v[j])
      inversiones++;
    }
  }
  return inversiones;
}


int compararPreferenciasDyV(int *v, int i, int f) {
  int inversiones = 0;

  if(i!=f) {
    int m = (i+f)/2;
    inversiones += compararPreferenciasDyV(v, i, m);
    inversiones += compararPreferenciasDyV(v, m+1, f);
    inversiones += inversiones_merge(v, i, m, f);
    merge(v, i, m, f);
  }
  return inversiones;
}

int inversiones_merge(int *v, int i, int m, int f){
  int j = i;
  int k = m+1;
  int inversiones = 0;

  while(j<=m && k<=f){
    if(v[j]>v[k]){
      inversiones += m-j+1;
      k++;
    }
    else
    j++;
  }
  return inversiones;
}

void merge(int *v, int i, int m, int f) {
   int *aux = new int[m-i+1];
   for(int j=i; j<=m; j++)
       aux[j-i] = v[j];

   int c1=0, c2=m+1;
   for(int j=i; j<=f; j++) {
       if(aux[c1] < v[c2]) {
           v[j] = aux[c1++];
           if(c1==m-i+1)
               for(int k=c2; k<=f; k++)
                   v[++j] = v[k];
       }
       else {
           v[j] = v[c2++];
           if(c2==f+1)
               for(int k=c1; k<=m-i; k++)
                   v[++j] = aux[k];
       }
   }
   delete [] aux;
}

double uniforme() {
  int t = rand();
  double f = ((double)RAND_MAX+1.0);
  return (double)t/f;
}

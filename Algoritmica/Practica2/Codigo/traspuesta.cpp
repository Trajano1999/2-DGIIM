#include <iostream>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <fstream>

using namespace std;

#define TAM 25
int casosEntrada[TAM]={500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 10500, 11000, 11500, 12000, 12500};

//Traspone una matriz por el método sencillo
void trasponerFB(int **m, int n);
//Traspone una matriz por el método divide y vencerás
void trasponerDyV(int **m, int n);
//Traspone por divide y vencerás. Encargada de las llamadas recursivas
void trasponerDyV(int **m, int fila_inicio, int fila_fin, int columna_inicio, int columna_fin);
//Intercambia la submatriz superior derecha con la inferior izquierda
void intercambiar (int **m, int fila_iniA, int columna_iniA, int fila_iniB, int columna_iniB, int dimension);
//Rellena la matriz con números de 1 a n*n.
void rellenarMatriz(int **m, int n);
//Libera la memoria reservada para la matriz
inline void vaciarMatriz(int **matriz, int nFilas);


int main(int argc, char * argv[]){
  ofstream salidaFB, salidaDyV;
  chrono::high_resolution_clock::time_point tAntesFB, tDespuesFB, tAntesDyV, tDespuesDyV;
  unsigned long tAcumuladoFB, tAcumuladoDyV, tMedioFB, tMedioDyV;
  int **matriz;

  if(argc != 3){
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
    matriz = new int*[n];
    for(int i=0; i<n; i++){
      matriz[i] = new int[n];
    }
    rellenarMatriz(matriz, n);

    tAcumuladoFB = 0;
    tAcumuladoDyV = 0;

    cout << "Caso " << caso+1 << " de " << TAM << endl;
    for(int iteracion=0; iteracion<15; iteracion++){
      tAntesFB = chrono::high_resolution_clock::now();
      trasponerFB(matriz, n);
      tDespuesFB = chrono::high_resolution_clock::now();
      tAcumuladoFB += chrono::duration_cast<std::chrono::microseconds>(tDespuesFB - tAntesFB).count();

      tAntesDyV = chrono::high_resolution_clock::now();
      trasponerDyV(matriz, n);
      tDespuesDyV = chrono::high_resolution_clock::now();
      tAcumuladoDyV += chrono::duration_cast<std::chrono::microseconds>(tDespuesDyV - tAntesDyV).count();

    }

    tMedioFB = tAcumuladoFB/15;
    tMedioDyV = tAcumuladoDyV/15;

    salidaFB << n << " " << tMedioFB << endl;
    salidaDyV << n << " " << tMedioDyV << endl;

    vaciarMatriz(matriz, n);

  }

  salidaFB.close();
  salidaDyV.close();

  return 0;
}

void trasponerFB(int **m, int n){
  for(int i=1; i<n; i++){
    for(int j=0; j<i; j++){
      int aux = m[i][j];
      m[i][j] = m[j][i];
      m[j][i] = aux;
    }
  }
}

void trasponerDyV(int **m, int n){
	trasponerDyV(m, 0, n-1, 0, n-1);
}

void trasponerDyV(int **m, int fila_inicio, int fila_fin, int columna_inicio, int columna_fin){
	if (fila_inicio < fila_fin){
		int fila_medio = (fila_inicio+fila_fin)/2;
		int columna_medio = (columna_inicio+columna_fin)/2;
		trasponerDyV(m, fila_inicio, fila_medio, columna_inicio, columna_medio);
		trasponerDyV(m, fila_inicio, fila_medio, columna_medio+1, columna_fin);
		trasponerDyV(m, fila_medio+1, fila_fin,  columna_inicio, columna_medio);
		trasponerDyV(m, fila_medio+1, fila_fin,  columna_medio+1, columna_fin);
		intercambiar(m, fila_medio+1, columna_inicio, fila_inicio, columna_medio+1, fila_fin-fila_medio);
	}
}

void intercambiar(int **m, int fila_iniA, int columna_iniA, int fila_iniB, int columna_iniB, int dimension){
	for (int i=0; i<=dimension-1; i++){
		for (int j=0; j<=dimension-1; j++){
			int aux = m[fila_iniA+i][columna_iniA+j];
			m[fila_iniA+i][columna_iniA+j] = m[fila_iniB+i][columna_iniB+j];
			m[fila_iniB+i][columna_iniB+j]=aux;
		}

	}
}

void rellenarMatriz(int **m, int n){
  int contador = 1;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      m[i][j] = contador;
      ++contador;
    }
  }
}

inline void vaciarMatriz(int **matriz, int nFilas){
	for(int i=0; i<nFilas; i++){
		delete [] matriz[i];
	}
	delete [] matriz;
}

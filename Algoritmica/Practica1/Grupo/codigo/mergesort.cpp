/**
   @file Ordenación por mezcla
*/

   
#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <fstream> // Para usar ficheros
using namespace std;


//EJECUCIÓN: ./mergesort ficheroSalida


/* ************************************************************ */ 
/*  Método de ordenación por mezcla  */

/**
   @brief Ordena un vector por el método de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static 
void mergesort(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el método de mezcla.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(int T[], int inicial, int final);


/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static 
void insercion(int T[], int num_elem);


/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la inserción.
*/
static void insercion_lims(int T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a escribir.
   @param final: Posición detrás de la última de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El número de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static void fusion(int T[], int inicial, int final, int U[], int V[]);



/**
   Implementación de las funciones
**/


inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_MS = 100;

void mergesort(int T[], int num_elem)
{
  mergesort_lims(T, 0, num_elem);
}

static void mergesort_lims(int T[], int inicial, int final)
{
  if (final - inicial < UMBRAL_MS)
    {
      insercion_lims(T, inicial, final);
    } else {
      int k = (final - inicial)/2;

      int * U = new int [k - inicial + 1];
      assert(U);
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++)
        U[l] = T[l2];
      U[l] = INT_MAX;

      int * V = new int [final - k + 1];
      assert(V);
      for (l = 0, l2 = k; l < final - k; l++, l2++)
        V[l] = T[l2];
      V[l] = INT_MAX;

      mergesort_lims(U, 0, k);
      mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}
  

static void fusion(int T[], int inicial, int final, int U[], int V[])
{
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k]) {
	T[i] = U[j];
	j++;
      } else{
	T[i] = V[k];
	k++;
      };
    };
}

#define NUM_CASOS 25
int casos_entrada[NUM_CASOS]={500, 50500, 100500, 150500, 200500, 250500, 300500, 350500, 400500, 450500, 500500, 550500, 600500, 650500, 700500, 750500, 800500, 850500, 900500, 950500, 1000500, 1050500, 1100500, 1150500, 1200500};



int main(int argc, char * argv[])
{
	ofstream fsalida;
    double t_medio;
    unsigned long t_ejecucion;
    
  	if (argc != 2){
    	cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
    	cerr<<argv[0]<<" NombreFicheroSalida\n\n";
      
        return -1;
    }

  	srandom(time(NULL));

  	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

	for(int i = 0; i < NUM_CASOS; i++){
		int n = casos_entrada[i];
        t_medio = 0;
        cerr << "Ejecutando Mergesort para tam. caso: " << n <<" (" << i+1 << "/" << "25)" << endl;

        int * T = new int[n];
        for(int j=0; j<15; j++){
            
            for (int k = 0; k < n; k++){
                T[k] = random();
            }
            
            chrono::high_resolution_clock::time_point t_antes = chrono::high_resolution_clock::now();
            mergesort(T, n);
            chrono::high_resolution_clock::time_point t_despues = chrono::high_resolution_clock::now();
            t_ejecucion = chrono::duration_cast<std::chrono::microseconds>(t_despues - t_antes).count();
            cerr << "\tTiempo de ejec. (us): " << t_ejecucion << " para tam. caso "<< n<<endl;
            t_medio += t_ejecucion;
        }
        delete [] T;
        
        t_medio = t_medio/NUM_CASOS;
        cerr << "\tTiempo medio de ejec. (us): " << t_medio << " para tam. caso "<< n<<endl;
        fsalida << n << " " << t_medio << endl;
	}

	fsalida.close();
  	

	return 0;
};

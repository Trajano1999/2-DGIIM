#include <iostream>

#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <fstream> // Para usar ficheros

using namespace std;

/* ************************************************************ */
/*  M�todo de ordenaci�n por montones  */

/**
   @brief Ordena un vector por el m�todo de montones.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de ordenaci�n por montones.
*/
inline static void heapsort(int T[], int num_elem);

/**
   @brief Reajusta parte de un vector para que sea un mont�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.
   @param k: �ndice del elemento que se toma com ra�z
   
   Reajusta los elementos entre las posiciones k y num_elem - 1 
   de T para que cumpla la propiedad de un mont�n (APO), 
   considerando al elemento en la posici�n k como la ra�z.
*/
static void reajustar(int T[], int num_elem, int k);

/**
   Implementaci�n de las funciones
**/
static void heapsort(int T[], int num_elem)
{
  int i;

  for (i = num_elem / 2; i >= 0; i--)
    reajustar(T, num_elem, i);
  for (i = num_elem - 1; i >= 1; i--)
  {
    int aux = T[0];
    T[0] = T[i];
    T[i] = aux;
    reajustar(T, i, 0);
  }
}

static void reajustar(int T[], int num_elem, int k)
{
  int j;
  int v;
  v = T[k];
  bool esAPO = false;
  while ((k < num_elem / 2) && !esAPO)
  {
    j = k + k + 1;
    if ((j < (num_elem - 1)) && (T[j] < T[j + 1]))
      j++;
    if (v >= T[j])
      esAPO = true;
    T[k] = T[j];
    k = j;
  }
  T[k] = v;
}

#define NUM_CASOS 25
int casos_entrada[NUM_CASOS]={500, 50500, 100500, 150500, 200500, 250500, 300500, 350500, 400500, 450500, 500500, 550500, 600500, 650500, 700500, 750500, 800500, 850500, 900500, 950500, 1000500, 1050500, 1100500, 1150500, 1200500};

int main(int argc, char *argv[]){
  if (argc != 2){
    cerr << "Formato: Fichero_salida " << endl;
    return -1;
  }

  ofstream fsalida;
  fsalida.open(argv[1]);
  if (!fsalida.is_open()) {
		cerr << "Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
		return 0;
	}

  for(int k=0; k<NUM_CASOS; ++k){
    int n = casos_entrada[k];

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;

    int *T = new int[n];
    assert(T);

    int tiempos[10];

    for (int l=0; l<10; ++l){
      srandom(time(0));
      for (int i = 0; i < n; i++)
      {
        T[i] = random();
      };

      t0= std::chrono::high_resolution_clock::now();
      heapsort(T, n);
      tf= std::chrono::high_resolution_clock::now();

      unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
      cout << "\nPara la ejecución " << l << ", el tiempo que tarda heapsort es: " << tejecucion;
      tiempos[l] = tejecucion;
    }

    double media = 0;
    for(int i=0; i<10; ++i)
      media += tiempos[i];
    media = media / 10;

    cerr.precision(17);
		cerr << "\nTiempo MEDIO de ejec. (us): " << media << " para tam. caso " << n << endl;
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida.precision(17);
		fsalida << n << " " << media << "\n";

    delete[] T;
  }

  cout << endl;
  return 0;
};

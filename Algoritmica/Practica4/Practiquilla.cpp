#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;


#define NUM_CASOS 25
int casos_entrada[NUM_CASOS]{500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 10500, 11000, 11500, 12000, 12500};


void nuevaSecuencia(string &s1, int tam){
  int aux;
  s1.clear();

  while (s1.size() < tam){
    aux = (int)rand() % 25 + 97;
    char tmp = (char)aux;
    s1.push_back(tmp);
  }
}

string subsecuencialarga(string X, string Y){
  int m = X.size();
    int n = Y.size();
    int **L = new int *[m + 1];
    for(int i = 0; i < m+1; ++i)
        L[i] = new int[n+1];
    int i, j;
    string resultado;

  //Rellenamos tabla
  for (i = 0; i <= m; i++){
    for (j = 0; j <= n; j++){
      if (i == 0 || j == 0)
        L[i][j] = 0;

      else if (X[i - 1] == Y[j - 1])
        L[i][j] = L[i - 1][j - 1] + 1;

      else
        L[i][j] = max(L[i - 1][j], L[i][j - 1]);
    }
  }

  i = m;
  j = n;
  while (L[i][j] != 0){
    if (L[i - 1][j] > L[i][j - 1]){
      i--;
    }
    else if (L[i - 1][j] < L[i][j - 1]){
      j--;
    }
    else{
      if (L[i - 1][j] == L[i][j]){
        i--;
      }
      else{
        resultado.push_back(X[i - 1]);
        i--;
        j--;
      }
    }
  }

  //Invertimos el orden de la cadena
  n = resultado.size();
  for (i = 0; i < n / 2; i++){
    char aux = resultado[i];
    resultado[i] = resultado[n - i - 1];
    resultado[n - i - 1] = aux;
  }

    for (int i = 0; i < m+1; i++){
        delete [] L[i];
    }
    delete [] L;
    return resultado;
}

int main(int narg, char *argv[]){

  chrono::time_point<chrono::high_resolution_clock> t0, tf;

  if (narg != 3){
    cerr << "\nError: El programa se debe ejecutar de la siguiente forma:\n\n";
    cerr << argv[0] << " NombreFicheroSalidaEjemplo " << "NombreFicheroSalidaTiempos" << "\n\n";
    return -1;
  }

  ofstream fsalida;
  fsalida.open(argv[1]);
  if (!fsalida.is_open()){
    cerr << "Error: No se pudo abrir el fichero de salida1 " << argv[1] << "\n\n";
    return 0;
  }

  ofstream fsalida2;
  fsalida2.open(argv[2]);
  if (!fsalida2.is_open()){
    cerr << "Error: No se pudo abrir el fichero de salida1 " << argv[2] << "\n\n";
    return 0;
  }

  string secuencia1 = "juanma";
  string secuencia2 = "antonia";

  fsalida << "Las secuencias a estudiar son: \n"
          << "\t" << secuencia1 << "\n"
          << "\t" << secuencia2 << "\n";

  //Calcula la subsecuencia de caracteres más larga
  string resultado = subsecuencialarga(secuencia1, secuencia2);

  //Muestra la subsecuencia de caracteres más larga
  fsalida << "\nLa secuencia resultante es: "
          << "\n\t" << resultado << endl;

  //-------------------------------------------------------------------------------------------------------------------
  
  unsigned long tejecucion = 0, tmedia = 0, tsuma = 0;

  for (int k = 0; k < NUM_CASOS; ++k){ // for que recorre casos_entrada
    for(int l=0; l<10; ++l){    // for necesario para calcular la media de los tiempos
      int n = casos_entrada[k], cont = 0;

      string sec1 = " ", sec2 = " ";
      nuevaSecuencia(sec1, n);
      nuevaSecuencia(sec2, n);

      tejecucion = 0, tmedia = 0, tsuma = 0;
      t0 = chrono::high_resolution_clock::now();

      // Calcula la subsecuencia de caracteres más larga
      string resul = subsecuencialarga(sec1, sec2);

      tf = chrono::high_resolution_clock::now();
      tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
      tsuma += tejecucion;
    }
    tmedia = tsuma/10;
    cout << "\nEl tiempo que tarda para secuencias de " << casos_entrada[k] << " palabras es de " << tmedia << " microsegundos\n";
    fsalida2 << casos_entrada[k] << " " << tmedia << "\n";
  }
  
  fsalida.close();
  fsalida2.close();
  cout << "\n";
  return 0;
}

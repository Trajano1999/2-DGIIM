 #include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
#include <fstream> // Para usar ficheros
#include <algorithm>
using namespace std;

//EJECUCIÓN: ./buscarBinario ficheroSalida
#define NUM_CASOS 35
int casos_entrada[NUM_CASOS]{1000000, 2500000, 5000000, 10000000, 15000000, 20000000, 25000000, 30000000, 40000000, 50000000, 60000000, 70000000, 80000000, 90000000, 100000000, 110000000, 120000000, 130000000, 140000000, 150000000, 160000000, 170000000, 180000000, 190000000, 200000000, 210000000, 220000000, 230000000, 240000000 , 250000000, 260000000, 270000000, 280000000, 290000000, 300000000};

int BuscarBinario(double *T, const int ini, const int fin, const double x);


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
        cerr << "Ejecutando BuscarBinario para tam. caso: " << n << " (" << i+1 << "/" << "35)" << endl;

        double * T = new double[n];
        for (int k = 0; k < n; k++){
                T[k] = ((double)random())/RAND_MAX*random();
        }
        sort(T, T+n);
        
        for(int j=0; j<1000; j++){
            
            double x = ((double)random())/RAND_MAX*random();
            
            chrono::high_resolution_clock::time_point t_antes = chrono::high_resolution_clock::now();
            BuscarBinario(T, 0, n, x);
            chrono::high_resolution_clock::time_point t_despues = chrono::high_resolution_clock::now();
            t_ejecucion = chrono::duration_cast<std::chrono::microseconds>(t_despues - t_antes).count();
            //cerr << "\tTiempo de ejec. (us): " << t_ejecucion << " para tam. caso "<< n<<endl;
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

int BuscarBinario(double *T, const int ini, const int fin, const double x){
    int centro;
    if (ini>fin) return -1;
    
    centro= (ini+fin)/2;
    if(T[centro] == x) return centro;
    if(T[centro]>x) return BuscarBinario(T, ini, centro-1, x);
    return BuscarBinario(T, centro+1, fin, x);
}







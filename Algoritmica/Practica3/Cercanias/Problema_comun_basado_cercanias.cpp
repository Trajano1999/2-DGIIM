#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <chrono>

using namespace std;

#define NUM_CASOS 25
int casos_entrada[NUM_CASOS]{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500};

int distanciaCiudad(vector<pair<bool, pair<double,double> > > v, int a, int b){
    int distancia = rint(sqrt(
    (v[b].second.first - v[a].second.first)*(v[b].second.first - v[a].second.first) +
    (v[b].second.second - v[a].second.second)*(v[b].second.second - v[a].second.second)
    ));
    return distancia;
}

int calculoSumaTotal(vector<int> v, vector<pair<bool, pair<double,double> > > v2){
    int ciudad_actual=0, suma=0;

    for(int i=1; i<v.size(); ++i){
        suma += distanciaCiudad(v2, v[ciudad_actual], v[i]);
        ciudad_actual = i;
    }
    suma += distanciaCiudad(v2, 0, v[v.size()-1]);
    return suma;
}

void nuevaLectura(vector<pair<bool, pair<double,double> > >& v, int l){
    int cont=0;
    v.clear();
    
    while(cont != l){
        pair<bool, pair<int,int> > tmp;
        tmp.first = true;
        tmp.second.first = (int)random();
        tmp.second.second = (int)random();
        v.push_back(tmp);
        cont++;
    }
}

vector<int> cercanias(vector<pair<bool, pair<double,double> > > v, int n){
    int cont=0;
    int d_min, pos, ciudad_actual = 0;
    vector<int> resultados;

    while(cont != n){
        bool encontrado=false;
        for(int j=1; j<n && !encontrado; ++j)
            if(v[j].first && j != ciudad_actual){
                d_min = distanciaCiudad(v, ciudad_actual, j);
                pos = j;
                encontrado = true;
            }
        
        for(int i=1; i<n; ++i){
            if(v[i].first && i != ciudad_actual && distanciaCiudad(v, ciudad_actual,i) < d_min){
                d_min = distanciaCiudad(v, ciudad_actual,i);
                pos = i;
            }
        }
        resultados.push_back(ciudad_actual);
        v[ciudad_actual].first = false;
        ciudad_actual = pos;
        cont++;
    }
    return resultados;
}

int main(int narg, char* argv[]){
    chrono::time_point<chrono::high_resolution_clock> t0, tf;
    
    if (narg != 4){
    	cerr << "\nError: El programa se debe ejecutar de la siguiente forma:\n\n";
    	cerr << argv[0] << " NombreFicheroEntrada " << "NombreFicheroSalidaDatos" << "NombreFicheroSalidaTiempos" << "\n\n";
        return -1;
    }

    ifstream fentrada;
    fentrada.open(argv[1]);
    if (!fentrada.is_open()){
		cerr << "Error: No se pudo abrir el fichero de lectura " << argv[1] << "\n\n";
		return 0;
	}

    ofstream fsalida;
    fsalida.open(argv[2]);
    if (!fsalida.is_open()){
		cerr << "Error: No se pudo abrir el fichero de escritura de datos " << argv[2] << "\n\n";
		return 0;
	}

    ofstream fsalida2;
    fsalida2.open(argv[3]);
    if (!fsalida2.is_open()){
		cerr << "Error: No se pudo abrir el fichero de escritura de tiempos " << argv[3] << "\n\n";
		return 0;
	}

    string lect; int dim;
    do{
        fentrada >> lect;
    }while(lect != "DIMENSION");
    
    fentrada >> lect >> dim;
    fsalida << "La dimensión es: " << dim << "\n\n";
    
    while(lect != "NODE_COORD_SECTION"){
        fentrada >> lect;
    }

    double valor1, valor2, valor3, cont=0;
    vector<pair<bool, pair<double,double> > > ciudades;

    //Lectura de los valores del vector ciudades
    while(cont != dim){
        pair<bool, pair<double,double> > tmp;
        fentrada >> valor1 >> valor2 >> valor3;
        tmp.first = true;
        tmp.second.first = valor2;
        tmp.second.second = valor3;
        ciudades.push_back(tmp);
        cont++;
    }
    
    //Calcula el orden más eficiente mediante el método de cercanias
    vector<int> cercanias1 = cercanias(ciudades, dim);

    //Muestra el orden de las ciudades
    for(int i=0; i<cercanias1.size(); ++i)
        fsalida << cercanias1[i]+1 << "\n";

    //Calculo de la suma total de cercanias1
    fsalida << "\nLa suma total es: " << calculoSumaTotal(cercanias1, ciudades);

    //-------------------------------------------------------------------------------------------------------------------

    unsigned long tejecucion=0, tmedia=0, tsuma=0;

    for(int k=0; k<NUM_CASOS; ++k){     //for que recorre casos_entrada
        for(int l=0; l<10; ++l){    // for necesario para calcular la media de los tiempos
            ciudades.clear();
            int n = casos_entrada[k], cont = 0;

            //Creación del nuevo vector de ciudades
            nuevaLectura(ciudades, casos_entrada[k]);
        
            tejecucion=0, tmedia=0, tsuma=0;
            t0 = chrono::high_resolution_clock::now();

            //Cálculo del recorrido más eficiente basado en cercanías
            vector<int> cercanias2 = cercanias(ciudades, casos_entrada[k]);
            
            tf = chrono::high_resolution_clock::now();
            tejecucion = chrono::duration_cast<chrono::microseconds>(tf - t0).count();
            tsuma += tejecucion;
        }
        tmedia = tsuma/10;
        cout << "\nEl tiempo que tarda para " << casos_entrada[k] << " ciudades es de " << tmedia << " microsegundos\n";
        fsalida2 << casos_entrada[k] << " " << tmedia << "\n";
    }
    
    fentrada.close();
    fsalida.close();
    fsalida2.close();

    return 0;
}

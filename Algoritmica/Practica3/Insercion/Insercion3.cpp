#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <chrono>

using namespace std;

#define NUM_CASOS 8
int casos_entrada[NUM_CASOS]{100, 200, 300, 400, 500, 600, 700, 800};

/*#define NUM_CASOS 25
int casos_entrada[NUM_CASOS]{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500};*/

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

int distancia(pair<double, double> a, pair<double, double> b){
  return rint(sqrt(
  (b.first - a.first)*(b.first - a.first) + (b.second - a.second)*(b.second - a.second)));
}

void introducir3vertices(vector<int>& res, vector<pair<bool, pair<double,double> > > & v){
    int max_este = v[0].second.first; int max_oeste = v[0].second.first; int max_norte=v[0].second.second;
    int pos_este=0; int pos_oeste=0; int pos_norte=0;

    for(int i=0; i<v.size(); ++i){
        if(v[i].second.first > max_este){
            max_este = v[i].second.first;
            pos_este = i;
        }
        if(v[i].second.first < max_oeste){
            max_oeste = v[i].second.first;
            pos_oeste = i;
        }
        if(v[i].second.second > max_norte){
            max_norte = v[i].second.second;
            pos_norte = i;
        }
    }
    res.push_back(pos_oeste);
    res.push_back(pos_norte);
    res.push_back(pos_este);

    for(int i=0; i<res.size(); ++i)
        v[res[i]].first = false;
}

vector<int> insercion(vector<pair<bool, pair<double,double> > > v){
    vector<int> res;

    introducir3vertices(res, v);

    int suma_final = __INT_MAX__, insertado_final=0, pos_final=0;
    int suma_min = 0, insertado=0, pos=0;

    while(res.size()<v.size()){
        suma_final = __INT_MAX__;
        for(int i=0; i<v.size(); ++i){

            if(v[i].first){
                suma_min = __INT_MAX__;
                int suma2, insertado2, pos2;

                for(int k=0; k<res.size(); ++k){

                    suma2 = distancia(v[i].second, v[res[k]].second) + distancia(v[i].second, v[res[(k-1)%res.size()]].second)
                            -distancia(v[res[(k-1)%res.size()]].second, v[res[k]].second);
                    insertado2 = i;
                    pos2 = k;

                    if(suma2 < suma_min){
                        suma_min = suma2;
                        insertado = insertado2;
                        pos = pos2;
                    }
                }

                if(suma_min < suma_final){
                    suma_final = suma_min;
                    insertado_final = insertado;
                    pos_final = pos;
                }

            }
        }
        res.insert(res.begin() + pos_final, insertado_final);
        v[insertado_final].first = false;
    }
    return res;
}

/*int insertion(list<City>& travel) {
    // Inicialización de variables:
    initialize_adjacency();
    travel.clear();

    // Cálculo de recorrido parcial, id est, este, norte y oeste:
    int max_east = numeric_limits<int>::min();
    int max_west = numeric_limits<int>::max();
    int max_north = numeric_limits<int>::min();

    int index_east_city, index_west_city, index_north_city;
    vector<City>::iterator east_city_it, west_city_it, north_city_it;

    for (vector<City>::iterator it = cities.begin(); it != cities.end(); ++it) {
        if ((*it).x > max_east) {
            max_east = (*it).x;
            east_city_it = it;
        }
        if ((*it).x < max_west) {
            max_west = (*it).x;
            west_city_it = it;
        }
        if ((*it).y > max_north) {
            max_north = (*it).y;
            north_city_it = it;
        }
    }

    travel.push_back(*west_city_it);
    cities.erase(west_city_it);
    if (*north_city_it != *east_city_it && *north_city_it != *west_city_it) {
        travel.push_back(*north_city_it);
        cities.erase(north_city_it);
    }
    travel.push_back(*east_city_it);
    cities.erase(east_city_it);



    // Inserción del resto de ciudades en la lista:
    list<City>::iterator it_min=next(travel.begin());
    int dist_min, dist_aux, final_dist;
    for (auto c : cities) {
        // Busco la posición óptima para insertar c:
        int dist_min = numeric_limits<int>::max();
        for (list<City>::iterator it=travel.begin(); it != travel.end(); ++it) {
            travel.insert(it, c); // inserto
            dist_aux = list_distance(travel); // calculo distancia
            if (dist_aux < dist_min) {
                dist_min = final_dist = dist_aux;
                it_min = it;
            }
            travel.erase(prev(it)); // elimino
        }

        // Inserto c:
        travel.insert(it_min, c);
    }

    return final_dist; // quedó almacenada la última distancia mínima
}*/

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


    //Calcula el orden más eficiente mediante el método de insercion
    vector<int> insercion1 = insercion(ciudades);
    //Muestra el orden de las ciudades
    for(int i=0; i<insercion1.size(); ++i)
        fsalida << insercion1[i]+1 << " " << ciudades[insercion1[i]].second.first << " " << ciudades[insercion1[i]].second.second << "\n";

    //Calculo de la suma total de cercanias1
    fsalida << "\nLa suma total es: " << calculoSumaTotal(insercion1, ciudades) << endl;
    //-------------------------------------------------------------------------------------------------------------------

    /*unsigned long tejecucion=0, tmedia=0, tsuma=0;

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
    */

    fentrada.close();
    fsalida.close();
    fsalida2.close();

    return 0;
}

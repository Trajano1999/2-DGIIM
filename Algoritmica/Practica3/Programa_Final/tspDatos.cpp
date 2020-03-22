/*
 * @file: Recubrimiento Minimal
 * @author: Grupo ALGO
**/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <chrono>

using namespace std;

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

//Aplica el algoritmo por Cercanía
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

//Aplica el algoritmo de completar extremos
vector<int> extremos(vector<pair<bool, pair<double, double> > > v, int n){
  int cont;
  bool aniadirFinal;
  int d_minInicio, d_minFinal, proxInicio, proxFinal, elegidaInicio, elegidaFinal, elegida;
  vector<int> resultados;

  cont = 0;
  elegidaInicio = 0;
  elegidaFinal = 0;
  elegida = 0;
  aniadirFinal = true;
  while(cont != n){
      bool encontrado=false;
      for(int j=1; j<n && !encontrado; ++j){
          if(v[j].first && j != elegida){
              d_minInicio = distanciaCiudad(v, elegidaInicio, j);
              d_minFinal = distanciaCiudad(v, elegidaFinal, j);
              proxInicio = j;
              proxFinal = j;
              encontrado = true;
          }
      }

      //Extremo Inicio
      for(int i=1; i<n; ++i){
          if(v[i].first && i != elegida && distanciaCiudad(v, elegidaInicio,i) < d_minInicio){
              d_minInicio = distanciaCiudad(v, elegidaInicio, i);
              proxInicio = i;
          }
      }

      //Extremo Final
      for(int i=1; i<n; ++i){
          if(v[i].first && i != elegida && distanciaCiudad(v, elegidaFinal,i) < d_minFinal){
              d_minFinal = distanciaCiudad(v, elegidaFinal,i);
              proxFinal = i;
          }
      }
      if(aniadirFinal)
        resultados.push_back(elegida);
      else
        resultados.insert(resultados.begin(), elegida);
      v[elegida].first = false;

      if(d_minInicio<d_minFinal){
        elegida = proxInicio;
        elegidaInicio = proxInicio;
        aniadirFinal = false;
      }
      else{
        elegida = proxFinal;
        aniadirFinal = true;
        elegidaFinal = proxFinal;
      }
      cont++;
  }
  return resultados;
}

//Valida todas las ciudades del vector
void validar(vector<pair<bool, pair<double,double> > > v, int n){
  for(int i=0; i<n; i++){
    v[i].first = true;
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

//Aplica el algoritmo de insercion
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

int main(int argc, char* argv[]){
    if(argc != 2){
      cerr << "\nError: El programa se debe ejecutar de la siguiente forma:\n\n";
    	cerr << argv[0] << " FicheroDeDatos" << endl;
        return -1;
    }
    string archivo = argv[1];

    ifstream fentrada;
    fentrada.open(argv[1]);
    if (!fentrada.is_open()){
  		cerr << "Error: No se pudo abrir el fichero de lectura " << argv[1] << "\n\n";
  		return 0;
	  }

    ofstream salidaCercania;
    salidaCercania.open(archivo + "datosCercania.txt");

    ofstream salidaInsercion;
    salidaInsercion.open(archivo + "datosInsercion.txt");

    ofstream salidaExtremos;
    salidaExtremos.open(archivo + "datosExtremos.txt");

    ofstream salidaResumen;
    salidaResumen.open(archivo + "datosResumen.txt");

    string lect; int dim;
    do{
        fentrada >> lect;
    }while(lect != "DIMENSION");

    fentrada >> lect >> dim;

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

    vector<int> cercanias_ = cercanias(ciudades, dim);
    validar(ciudades, dim);
    vector<int> insercion_ = insercion(ciudades);
    validar(ciudades, dim);
    vector<int> extremos_ = extremos(ciudades, dim);

    salidaResumen << "Fichero: " << argv[1] << endl;
    salidaResumen << "\tCercania-> " << calculoSumaTotal(cercanias_, ciudades) << endl;
    salidaResumen << "\tInsercion-> " << calculoSumaTotal(insercion_, ciudades) << endl;
    salidaResumen << "\tExtremos-> " << calculoSumaTotal(extremos_, ciudades) << endl;

    for(int i=0; i<cercanias_.size(); i++){
      salidaCercania << cercanias_[i] << " " << ciudades[cercanias_[i]].second.first << " " << ciudades[cercanias_[i]].second.second << endl;
    }
    salidaCercania << cercanias_[0] << " " << ciudades[cercanias_[0]].second.first << " " << ciudades[cercanias_[0]].second.second << endl;

    for(int i=0; i<insercion_.size(); i++){
      salidaInsercion << insercion_[i] << " " << ciudades[insercion_[i]].second.first << " " << ciudades[insercion_[i]].second.second << endl;
    }
    salidaInsercion << insercion_[0] << " " << ciudades[insercion_[0]].second.first << " " << ciudades[insercion_[0]].second.second << endl;

    for(int i=0; i<extremos_.size(); i++){
      salidaExtremos << extremos_[i] << " " << ciudades[extremos_[i]].second.first << " " << ciudades[extremos_[i]].second.second << endl;
    }
    salidaExtremos << extremos_[0] << " " << ciudades[extremos_[0]].second.first << " " << ciudades[extremos_[0]].second.second << endl;

    salidaCercania.close();
    salidaInsercion.close();
    salidaExtremos.close();
    salidaResumen.close();

}

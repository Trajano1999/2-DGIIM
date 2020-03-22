#include <iostream>
#include <set>

using namespace std;

set <int> operator+(const set <int>& a, const set <int>& b){
     set <int> c(a);
     c.insert(b.begin(),b.end());
     return c;
}

set <int> operator*(const set <int>& a, const set <int>& b){
     set <int> d;
     bool encontrado = false;

     for(set <int>::iterator i = a.begin(); i != a.end(); i++){
          for(set <int>::iterator j = b.begin(); j != b.end() && !encontrado; j++)
               if(*i == *j){
                    d.insert(*i);
                    encontrado = true;
               }
          encontrado = false;
     }
     return d;
}

set <int> operator-(const set <int>& a, const set <int>& b){
     set <int> e(a);
     for(set <int>::iterator i = b.begin(); i != b.end(); i++)
          e.erase(*i);
     return e;
}

ostream& operator<<(ostream& flujo, const set <int>& a){
     for(set <int>::iterator i = a.begin(); i != a.end(); i++)
          flujo << *i << " ";
     return flujo;
}

int main(int narg, char* argv[]){
     int num_elem1, num_elem2, elemento;
     set <int> a, b;

     cout << "\nIntroduce el numero de elementos del primer conjunto: " << endl;
     cin >> num_elem1;
     for(int i=0; i<num_elem1; i++){
          cin >> elemento;
          a.insert(elemento);
     }
     cout << "El conjuto A es: " << endl << a << endl;

     cout << "\nIntroduce el numero de elementos del segundo conjunto: " << endl;
     cin >> num_elem2;
     for(int i=0; i<num_elem2; i++){
          cin >> elemento;
          b.insert(elemento);
     }
     cout << "El conjunto B es: " << endl << b << endl;

     cout << "\nLa union de estos conjuntos es: " << endl;
     set <int> c = a + b;
     cout << c << endl;

     cout << "La interseccion de estos conjuntos es: " << endl;
     set <int> d = a * b;
     cout << d << endl;

     cout << "Los elementos de a que no estan en b son: " << endl;
     set <int> e = a - b;
     cout << e << endl << endl;

     return 0;
}
#include <iostream>
#include <set>

using namespace std;

set <int> operator+(const set <int>& a, const set <int>& b){
     set <int> c(a);
     c.insert(b.begin(), b.end());
     return c;
}

set <int> operator*(const set <int>& a, const set <int>& b){
     set <int> d;

     for(set <int>::iterator i = a.begin(); i != a.end(); i++)
          for(set <int>::iterator j = b.begin(); j != b.end(); j++)
               if(*i == *j){
                    d.insert(*i);
                    break;
               }
     return d;
}

set <int> operator-(const set <int>& a, const set <int>& b){
     set <int> c(a);
     
     for(set<int>::iterator i = b.begin(); i != b.end(); i++)
          c.erase(*i);
     return c;
}

ostream& operator<<(ostream& flujo, const set <int>& a){
     for(set <int>::iterator i = a.begin(); i != a.end(); i++)
          flujo << *i << " "; 
     flujo << endl;
     return flujo;
}

int main(int narg, char* argv[]){
     int num_elem1, num_elem2, elemento;
     set <int> a, b;

     cout << "\nIntroduce el numero de elementos a insertar: ";
     cin >> num_elem1;

     for(int i=0; i<num_elem1; i++){
          cin >> elemento;
          a.insert(elemento);
     }

     cout << "\nEl primer conjunto es: " << endl;
     cout << a;

     cout << "\nIntroduce el numero de elementos del segundo conjunto: ";
     cin >> num_elem2;

     for(int i=0; i<num_elem2; i++){
          cin >> elemento;
          b.insert(elemento);
     }

     cout << "\nEl segundo conjunto es: " << endl;
     cout << b;

     cout << "\nLa union de los conjuntos es: " << endl;
     set <int> c = a + b;
     cout << c;

     cout << "\nLa interseccion de los conjuntos es: " << endl;
     set <int> d = a * b;
     cout << d;

     cout << "\nLos elementos que estan en a y no estan en b: " << endl;
     set <int> e = a - b;
     cout << e;

     return 0;
}
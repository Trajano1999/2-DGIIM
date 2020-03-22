#include <iostream>
#include <set>

using namespace std;

set <int> operator+(const set <int>& a, const set <int>& b){
     set <int> c(a);
     c.insert(b.begin(), b.end());
     return c;
}

set <int> operator*(const set <int>& a, const set <int>& b){
     set <int> c;
     bool continuar = false;

     for(set <int>::iterator i = a.begin(); i != a.end(); i++){
          for(set <int>::iterator j = b.begin(); j != b.end() && !continuar; j++)
               if(*i == *j){
                    c.insert(*i);
                    continuar = true;
               }
          continuar = false;
     }
     return c;
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
}

int main(int narg, char* argv[]){
     int num_elem1, num_elem2, num_elem3, elemento;
     set <int> a, b, c;

     cout << "\nIntroduce el numero de elementos del primer conjunto: ";
     cin >> num_elem1;
     for(int i=0; i<num_elem1; i++){
          cin >> elemento;
          a.insert(elemento);
     }
     cout << "\nEl conjunto A es el siguiente: " << endl;
     cout << a;

     cout << "\nIntroduce el numero de elementos del segundo conjunto: ";
     cin >> num_elem2;
     for(int i=0; i<num_elem2; i++){
          cin >> elemento;
          b.insert(elemento);
     }
     cout << "\nEl conjunto B es el siguiente: " << endl;
     cout <<  b;

     cout << "\nIntroduce el numero de elementos del tercer conjunto: ";
     cin >> num_elem3;
     for(int i=0; i<num_elem3; i++){
          cin >> elemento;
          c.insert(elemento);
     }
     cout << "\nEl conjunto C es el siguiente: " << endl;
     cout << c;
     
     cout << "\n\nLa union de estos conjuntos es: " << endl;
     set <int> d = a + b + c;
     cout << d;

     cout << "\nLa interseccion disjunta de estos conjuntos es: " << endl;
     set <int> e = ((a * b) + (a * c) + (b * c)) - (a * b * c);
     cout << e;

     cout << endl << endl;
     return 0;
}
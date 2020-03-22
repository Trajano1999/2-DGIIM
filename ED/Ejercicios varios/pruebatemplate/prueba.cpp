#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Matriz{
private:
	vector< vector <T> > m;
	
public:
	Matriz();
	Matriz(int tamano);
	
	bool operator>(const Matriz<T>& matrix);
	friend istream& operator>>(istream& flujo, Matriz<T>& matrix);
	friend ostream& operator<<(ostream& flujo, const Matriz<T>& matrix);
};

template<class T>
Matriz<T>::Matriz(){}

template<class T>
Matriz<T>::Matriz(int tamano){
	vector< vector<T> > m1(tamano, vector<T> (tamano));
	m = m1;
}

template<class T>
bool Matriz<T>::operator>(const Matriz<T>& matrix){
	return *this.size() > matrix.size(); 
}

template<class T>
istream& operator>>(istream& flujo, Matriz<T>& matrix){
	for(int i=0; i<matrix.size(); ++i)
		for(int j=0; j<matrix[i].size(); ++j)
			flujo >> matrix[i][j];
	return flujo;
}

template<class T>
ostream& operator<<(ostream& flujo, const Matriz<T>& matrix){
	for(int i=0; i<matrix.size(); ++i){
		for(int j=0; j<matrix[i].size(); ++j){
			flujo << matrix[i][j] << " ";
		}
		flujo << endl;
	}
	return flujo;
}

int main(){
	int tamano;
	Matriz<int> mi_matriz;

	cout << "\nIntroduce el numero de filas de la matriz: ";
	cin >> tamano;
	cout << "\nIntroduce los valores de la matriz: ";
	cin >> mi_matriz;
	cout << "\nLa matriz introducida es: ";
	cout << mi_matriz;

	return 0;	
}
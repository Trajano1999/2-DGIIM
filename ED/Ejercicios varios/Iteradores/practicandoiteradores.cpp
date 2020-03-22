#include <iostream>
#include <list>

using namespace std;

struct enfrentamiento{
    unsigned char eq1, eq2;
    unsigned int puntos_eq1, puntos_eq2;
};

class liga{
private:
    list<enfrentamiento> res;

public:
    liga(){}
    int PartidosGanados(unsigned char c) const;

    class iterator{
    private:
        list<int>::iterator it, fin;

    public:
        enfrentamiento& operator*() const;
        bool operator==(const iterator& i) const;
        bool operator!=(const iterator& i) const;
        iterator& operator++();
    };

    iterator begin();
    iterator end();
};

int liga::PartidosGanados(unsigned char c) const{
    list<enfrentamiento>::const_iterator it;
    int cont=0;

    for(it = res.begin(); it != res.end(); ++it)
        if((*it.eq1 == c && *it.puntos_eq1 > *it.puntos_eq2) || (*it.eq2 == c && *it.puntos_eq2 > *it.puntos_eq1))
            cont++;
    return cont;
}

enfrentamiento& liga::iterator::operator*() const{
    return *it;
}

bool liga::iterator::operator==(const iterator& i) const{
    return (i.it == it);
}

bool liga::iterator::operator!=(const iterator& i) const{
    return (i.it != it);
}

iterator& liga::iterator::operator++(){
    bool salir = false;
    
    it++;
    while(it != fin() && !salir){
        if(*it.puntos_eq1 == *it.puntos_eq2)
            salir = true;
        else
            ++it;
    }
    return *this;
}

iterator liga::begin(){
    iterator i;
    i.it = res.begin();
    i.fin = res.end();

    if( !(*i.it.puntos_eq1 == *i.it.puntos_eq2) )
        ++i;
    return i;
}

iterator liga::end(){
    iterator i;
    i.it = res.end();
    i.it = res.end();
    return i;
}
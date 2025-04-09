#include <iostream>
#include "naglowki.hpp"

using namespace std;

int main(){
    liczba a(2.0);
    a.ustaw(3.0);
    a.ustaw(4.0);
    a.ustaw(5.0);
    cout<< a.pobierz()<<endl;
    cout<<a.pobierz_poprzednia()<<endl;
    a.zwiekrzanie_indeksu();
    a.przywrocenie_wartosci(0);
    cout<<a.pobierz()<<endl;
    cout<<a.pobierz_poprzednia()<<endl;
    cout<<a.pobierz_poprzednia()<<endl;
    //cout<<a.pobierz_poprzednia()<<endl; //tu blad bo konczy sie historia
    return 0;
}
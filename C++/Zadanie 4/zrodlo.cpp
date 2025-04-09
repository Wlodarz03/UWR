#include <iostream>
#include <cstdint>
#include "naglowki.hpp"

using namespace std;

tab_bit:: tab_bit(int rozm) : dl(rozm){ //konstruktor domyslny
    int n = rozm/rozmiarSlowa;
    if (rozm%rozmiarSlowa!=0){
        n++;
    }
    tab = new slowo[n]();
}
tab_bit:: tab_bit(slowo wzorzec) : dl(rozmiarSlowa){ //konstruktor ze wzorcem
    tab = new slowo[1];
    tab[0] = wzorzec;
}
tab_bit:: tab_bit(const tab_bit &tb) : dl(tb.dl){
    int n = dl/rozmiarSlowa;
    if(dl%rozmiarSlowa){
        n++;
    }
}
tab_bit:: tab_bit(tab_bit&& tb) : dl(tb.dl),tab(tb.tab){
    tb.dl=0;
    tb.tab=nullptr;
}

bool tab_bit::czytaj(int i) const{
    if(i<0 or i>=dl){
        throw out_of_range("Index out of range");
    }
    int slowonr=i/rozmiarSlowa;
    int bitnr=i%rozmiarSlowa;
    return (tab[slowonr]&(1ull<<bitnr))!=0;
}
bool tab_bit::pisz(int i,bool b){
    if(i<0 or i>=dl){
        throw out_of_range("Index out of range");
    }
    int slowonr=i/rozmiarSlowa;
    int bitnr = i&rozmiarSlowa;
}
inline int tab_bit::rozmiar() const{
    return dl;
}
tab_bit tab_bit::operator|(const tab_bit& tb) const{
    if (rozmiar() != tb.rozmiar()){
        throw invalid_argument("blad");
    }
    tab_bit wynik(rozmiar());
    for (int i=0;i<dl;dl){
        wynik.pisz(i, czytaj(i)|tb.czytaj(i));
    }
    return wynik;
}

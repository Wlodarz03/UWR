#include <iostream>

using namespace std;

class tab_bit{
    typedef uint64_t slowo; //komorka w tablicy
    static const int rozmiarSlowa; //rozmiar slowa w bitach
    friend istream& operator >> (istream &we,tab_bit &tb);
    friend ostream& operator << (ostream &wy,const tab_bit &tb);
    class ref; //klasa pomocnicza do adresowania bitow
    protected:
        int dl; //liczba bitow
        slowo *tab; //tablica bitow
    public:
        explicit tab_bit(int rozm); // wyzerowana tablica bitow [0...rozm]
        explicit tab_bit(slowo tb); //tablica bitow [0....rozmiarSlowa]
        tab_bit(const tab_bit &tb); //konstruktor kopiujacy
        tab_bit(tab_bit &&tb); //konstruktor przenoszacy
        tab_bit & operator = (const tab_bit &tb); //przypisanie kopiujace
        tab_bit & operator = (tab_bit &&tb); //przypisanie przenoszace
        ~tab_bit(); //destruktor
    private:
        bool czytaj (int i) const; //metoda pomocnicza do oczytu bitu
        bool pisz (int i,bool b);//metoda pomocnicza do zapisu bitu
    public:
        bool operator[] (int i) const; //metoda indeksowanie dla stalych tablic bitowych
        ref operator[] (int i); //indeksowanie dla zwyklych tablic bitowych
        inline int rozmiar () const; //rozmiar tablicy w bitach
        //operatory bitowe: | i |=, & i &=, ^ i ^= oraz !
        //zaprzyjaznione operatory strumieniowe: << i >> 
};
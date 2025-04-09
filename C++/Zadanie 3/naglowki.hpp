#include <iostream>

using namespace std;

class liczba
{
    private:
        double x;
        int dlugosc_historia;
        double *historia;
        int index;
        static const int max_dlugosc_historii = 3;

    public:
        liczba() : liczba(0){} //konstruktor delegatowy
        
        liczba(double _x) : x(_x), dlugosc_historia(1), index(0) {
            historia = new double[max_dlugosc_historii];
            historia[index] = x;
        } //konstruktor zwykły

        liczba(const liczba& licz) : x(licz.x), dlugosc_historia(licz.dlugosc_historia), index(0){
            historia = new double[max_dlugosc_historii];
            historia[index] = x;
        } //konstruktor kopiujacy 

        liczba(liczba&& licz) : x(licz.x), dlugosc_historia(licz.dlugosc_historia), historia(licz.historia), index(move(licz.index)){
            licz.historia = nullptr;
        } //konstruktor przenoszacy

        liczba& operator = (liczba& licz){ //przypisanie  kopiujace
            if (this != &licz){
                x = licz.x;
                index=licz.index;
                int kopia_dlugosc_historia = min(dlugosc_historia, licz.dlugosc_historia);
                for (int i = 0; i<kopia_dlugosc_historia; i++){
                    historia[i] = licz.historia[i];
                }
            }
            return *this;
        }
        liczba& operator =(liczba&& licz){ //przypisanie przenoszace
            if(this != &licz){
                delete[] historia;
                x = licz.x;
                index = licz.index;
                historia = licz.historia;
                dlugosc_historia = licz.dlugosc_historia;
                licz.x = 0;
                licz.dlugosc_historia = 0;
                licz.index = 0;
                licz.historia = nullptr;
            }
            return *this;
        }
        ~liczba(){ //destruktor
            delete[] historia;
            x = 0;
            dlugosc_historia = 0;
            index = 0;
        }
        void ustaw(double x2);
        double pobierz();
        double pobierz_poprzednia();
        void przywrocenie_wartosci(int i);
        void zwiekrzanie_indeksu();
};
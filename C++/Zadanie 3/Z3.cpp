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
        liczba(double _x) : x(_x), dlugosc_historia(1), index(0) {
            historia = new double[max_dlugosc_historii];
            historia[index] = x;
        } //konstruktor delegatowy

        liczba(const liczba& licz) : x(licz.x), dlugosc_historia(licz.dlugosc_historia), index(0){
            historia = new double[max_dlugosc_historii];
            historia[index] = x;
        } //konstruktor kopiujacy 

        liczba(liczba&& licz) : x(move(licz.x)), dlugosc_historia(move(licz.dlugosc_historia)), historia(move(licz.historia)), index(move(licz.index)){
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
                for (int i = kopia_dlugosc_historia; i<dlugosc_historia; i++){
                    historia[i]=0;
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
        }
        void ustaw(double x2){
            this->x = x2;
            if (index+1 >= max_dlugosc_historii){
                for (int i=0; i<dlugosc_historia-1;i++){
                    historia[i] = historia[i+1];
                }
                historia[dlugosc_historia-1] = x2;
            }
            else{
                index +=1;
                dlugosc_historia += 1;
                historia[index] = x2;
            }
            x=x2;
        }
        double pobierz(){
            return x;
        }
        double pobierz_poprzednia(){
            if (index-1>=0){
                index-=1;
                return historia[index];
                
            }
            else{
                throw out_of_range("nie ma juz nic wiecej w historii");
            }
        }
        void przywrocenie_wartosci(int i){
            if(i>=0 and i<max_dlugosc_historii-1){
                x = historia[i];
                double temp = historia[i];
                for (int j=i; j<max_dlugosc_historii-1;j++){
                    historia[j]=historia[j+1];
                }
                historia[max_dlugosc_historii-1] = temp;
            }
            else{
                throw out_of_range("zly indeks");
            }
        }

};

int main(){
    liczba a(2.0);
    a.ustaw(3.0);
    a.ustaw(4.0);
    a.ustaw(5.0);
    cout<< a.pobierz()<<endl;
    a.przywrocenie_wartosci(1);
    return 0;
}
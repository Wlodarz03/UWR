#include <iostream>
#include "naglowki.hpp"

using namespace std;

void liczba::ustaw(double x2){
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
double liczba::pobierz(){
    return x;
}
 double liczba::pobierz_poprzednia(){
    if (index-1>=0){
        index-=1;
        return historia[index];     
    }
    else{
        throw out_of_range("nie ma juz nic wiecej w historii");
    }
}
void liczba::przywrocenie_wartosci(int i){
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
void liczba::zwiekrzanie_indeksu(){
    index++;
}
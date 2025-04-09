#include <iostream>
#include <cmath>
#include <vector>
#include "nag.hpp"

using namespace std;

int main(){
    zmienna :: dodaj("x",0);
    zmienna :: dodaj("y",0);
    wyrazenie *x = new zmienna("x");
    wyrazenie *y = new zmienna("y");
    wyrazenie *w1 = new dziel(new mnoz(new odejmij(x,new liczba(1)),x),new liczba(2));
    wyrazenie *w2 = new dziel(new dodaj(new liczba(3),new liczba(5)),new dodaj(new liczba(2),new mnoz(x,new liczba(7))));
    wyrazenie *w3 = new odejmij(new dodaj(new liczba(2),new mnoz(x,new liczba(7))),new dodaj(new mnoz(y,new liczba(3)),new liczba(5)));
    wyrazenie *w4 = new dziel(new cosinus(new mnoz(new dodaj(x,new liczba(1)),new pi())),new potega(new e(),new potega(x,new liczba(2))));
    cout<<"Wyrazenie pierwsze"<<endl;
    cout<< w1->zapis()<<endl;
    cout<<"Wyrazenie drugie"<<endl;
    cout<<w2->zapis()<<endl;
    cout<<"Wyrazenie trzecie"<<endl;
    cout<<w3->zapis()<<endl;
    cout<<"Wyrazenie czwarte"<<endl;
    cout<<w4->zapis()<<endl;
    cout<<"Wyniki dla pierwszego"<<endl;
    for (double i = 0;i<=1.01;i+=0.01){
        cout<<w1->oblicz()<<endl;
        zmienna ::modyfikuj("x",i+0.01);
    }
    zmienna::modyfikuj("x",0);
    cout<<"Wyniki dla drugiego"<<endl;
    for (double i = 0;i<=1.01;i+=0.01){
        cout<<w2->oblicz()<<endl;
        zmienna :: modyfikuj("x",i+0.01);
    }
    zmienna:: modyfikuj("x",0);
    cout<<"Wyniki dla trzeciego"<<endl;
    for (double i = 0;i<=1.01;i+=0.01){
        cout<<w3->oblicz()<<endl;
        zmienna :: modyfikuj("x",i+0.01);
        zmienna :: modyfikuj("y",i+0.01);
    }
    zmienna :: modyfikuj("x",0);
    zmienna :: modyfikuj("y",0);
    cout<<"Wyniki dla czwartego"<<endl;
    for (double i = 0;i<=1.01;i+=0.01){
        cout<<w4->oblicz()<<endl;
        zmienna :: modyfikuj("x",i+0.01);
    }
    zmienna :: modyfikuj("x",0);
    return 0;
}
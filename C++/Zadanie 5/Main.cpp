#include <iostream>
#include <string>
#include <ctype.h>
#include <cctype>
#include <cmath>
#include "nag-piksel.hpp"

int main(){
    Kolor k1 = Kolor(); //czarny
    kolortransparentny k2(255,0,0,255); //czerwony
    kolornazwany k3(0,255,0,"zielony"); //zielony
    kolornt k4(0,0,0,0,"czarny");// czarny (kolornt)
    Piksel p1(400,300);
    PikselKolorowy p2(400,0,255,0,0,255); //czerwony piksel
    cout<<"Czarny na czerwony"<<endl;
    cout<<"Kolory: r="<<k1.getRed()<<" g="<<k1.getGreen()<<" b="<<k1.getBlue()<<endl;
    k1.setRed(255);
    cout<<"Po zmianie: "<<"Kolory: r="<<k1.getRed()<<" g="<<k1.getGreen()<<" b="<<k1.getBlue()<<endl;
    cout<<""<<endl;
    cout<<"Z czerwonego mocnego na czarny przezroczysty: "<<endl;
    cout<<"Kolory: r="<<k2.getRed()<<" g="<<k2.getGreen()<<" b="<<k2.getBlue()<<" Alfa: "<<k2.getAlfa()<<endl;
    k2.setAlfa(0);
    k2.setRed(0);
    cout<<"Po zmianie: "<<"Kolory: r="<<k2.getRed()<<" g="<<k2.getGreen()<<" b="<<k2.getBlue()<<" Alfa: "<<k2.getAlfa()<<endl;
    cout<<""<<endl;
    cout<<"Z zielonego na niebieski + zmiana nazwy:"<<endl;
    cout<<"Kolory: r="<<k3.getRed()<<" g="<<k3.getGreen()<<" b="<<k3.getBlue()<<" Nazwa: "<<k3.getNazwa()<<endl;
    k3.setNazwa("niebieski");
    k3.setBlue(255);
    k3.setGreen(0);
    cout<< "Po zmianie: "<<"Kolory: r="<<k3.getRed()<<" g="<<k3.getGreen()<<" b="<<k3.getBlue()<<" Nazwa: "<<k3.getNazwa()<<endl;
    cout<<""<<endl;
    cout<<"Kolory: r="<<k4.getRed()<<" g="<<k4.getGreen()<<" b="<<k4.getBlue()<<" Nazwa: "<<k4.getNazwa()<<" Alfa: "<<k4.getAlfa()<<endl;
    k4.setAlfa(56);
    k4.setRed(255);
    k4.setNazwa("czerwony");
    cout<<"Po zmianie: "<<"Kolory: r="<<k4.getRed()<<" g="<<k4.getGreen()<<" b="<<k4.getBlue()<<" Nazwa: "<<k4.getNazwa()<<" Alfa: "<<k4.getAlfa()<<endl;
    cout<<""<<endl;
    cout<<"Odleglosc od gory: "<<p1.dlugosc_od_gory()<<endl;
    cout<<"Odleglosc od dolu: "<<p1.dlugosc_od_dolu()<<endl;
    cout<<"Odleglosc od lewej: "<<p1.dlugosc_od_lewej()<<endl;
    cout<<"Odleglosc od prawej: "<<p1.dlugosc_od_prawej()<<endl;
    cout<<""<<endl;
    cout<<"Odleglosc miedzy p1 i p2: "<<odleglosc(p1,p2)<<endl;
    p2.przesuniecie(0,200);
    cout<<"Odleglosc miedzy p1 i p2 po przesunieciu "<<odleglosc(p1,p2)<<endl;
    cout<<""<<endl;
    cout<<"Kolory piksela p2 oraz alfa: "<<"r="<<p2.getRed()<<" g="<<p2.getGreen()<<" b="<<p2.getBlue()<<" alfa="<<p2.getAlfa()<<endl;
    cout<<""<<endl;
    cout<<"Proby niefajnych rzeczy: "<<endl;
    p2.przesuniecie(500,500);
    k1.setBlue(256);
    k3.setNazwa("Biały");
    k2.setAlfa(256);
    return 0;
}
#include <iostream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <cctype>
#include <cmath>
#include "nag-piksel.hpp"

Piksel::Piksel(int x, int y) : x(x), y(y){
    if (x<0 or x>=szerokosc or y<0 or y>=dlugosc){
        throw out_of_range("Poza ekranem");
    }
}
int Piksel::dlugosc_od_lewej() const {
    return x;
}
int Piksel::dlugosc_od_gory() const{
    return y;
}
int Piksel::dlugosc_od_dolu() const{
    return dlugosc-y;
}
int Piksel::dlugosc_od_prawej() const{
    return szerokosc-x;
}
PikselKolorowy::PikselKolorowy(int x, int y, int red, int green,int blue,int a) : Piksel(x,y), k(red,green,blue,a){}

int PikselKolorowy::getRed(){
    return k.getRed();
}
int PikselKolorowy::getGreen(){
    return k.getGreen();
}
int PikselKolorowy::getBlue(){
    return k.getBlue();
}
int PikselKolorowy::getAlfa(){
    return k.getAlfa();
}
void PikselKolorowy::setRed(int red){
    k.setRed(red);
}
void PikselKolorowy::setGreen(int green){
    k.setGreen(green);
}
void PikselKolorowy::setBlue(int blue){
    k.setBlue(blue);
}
void PikselKolorowy::setAlfa(int a){
    k.setAlfa(a);
}
void PikselKolorowy::przesuniecie(int _x, int _y){
    if(x+_x<0 or x+_x>szerokosc or y+_y<0 or y+_y>dlugosc){
        throw out_of_range("Wyjdzie poza ekran");
    }
    x = x + _x;
    y = y + _y;
}
int odleglosc(const Piksel& p1,const Piksel& p2){
    int dx = p2.dlugosc_od_lewej() - p1.dlugosc_od_lewej();
    int dy = p2.dlugosc_od_gory() - p1.dlugosc_od_gory();
    int d = sqrt(dx*dx+dy*dy);
    return d;
}
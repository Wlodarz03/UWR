#include <iostream>
#include <string>
#include <ctype.h>
#include <cctype>
#include <cmath>
#include "nag-kolor.hpp"

using namespace std;

Kolor::Kolor() : r(0), g(0), b(0){} //czarny

Kolor::Kolor(int red, int green, int blue) : r(red), g(green), b(blue){
    if (red<0 or red>255 or green<0 or green>255 or blue<0 or blue>255){
        throw out_of_range("Przekracza zakres");
    }
}
int Kolor::getRed(){
    return r;
}
int Kolor::getGreen(){
    return g;
}
int Kolor::getBlue(){
    return b;
}
void Kolor::setRed(int red){
    if(red<0 or red>255){
        throw out_of_range("Przekracza zakres");
    }
    r = red;
}
void Kolor::setGreen(int green){
    if (green<0 or green>255){
        throw out_of_range("Przekracza zakres");
    }
    g = green;
}
void Kolor::setBlue(int blue){
    if (blue<0 or blue>255){
        throw out_of_range("Przekracza zakres");
    }
    b = blue;
}
void Kolor::rozjasnianie(int x){
    r = min(r + x,255);
    g = min(g + x,255);
    b = min(b + x,255);
}
void Kolor::przyciemnij(int x){
    r = max(r - x,0);
    g = max(g - x,0);
    b = max(b - x,0);
}
Kolor Kolor::laczenie(const Kolor &k1, const Kolor &k2){
    int red = (k1.r + k2.r)/2;
    int green = (k1.g + k2.g)/2;
    int blue = (k1.b + k2.b)/2;
    return Kolor(red,green,blue);
}
kolortransparentny::kolortransparentny() : Kolor(), alfa(0){}

kolortransparentny::kolortransparentny(int red,int green, int blue, int a) : Kolor(red,green,blue), alfa(a){
    if(a<0 or a>255){
        throw out_of_range("Przekracza zakres");
    }
}
int kolortransparentny::getAlfa(){
    return alfa;
}
void kolortransparentny::setAlfa(int a){
    if(a<0 or a>255){
        throw out_of_range("Przekracza zakres");
    }
    alfa = a;
}
kolornazwany::kolornazwany() : Kolor(), nazwa(""){}
kolornazwany::kolornazwany(int red,int green,int blue,string s): Kolor(red,green,blue), nazwa(s){
    for(int i=0;i<s.size();i++){
        if(!islower(s[i]) or !isalpha(s[i])){
            throw invalid_argument("Nazwa nie sklada sie z samych małych liter- z alfabetu angielskiego");
        }
    }
}

string kolornazwany::getNazwa(){
    return nazwa;
}
void kolornazwany::setNazwa(string s){
    for(int i=0;i<s.size();i++){
        if(!islower(s[i]) or !isalpha(s[i])){
            throw invalid_argument("Nazwa nie sklada sie z samych małych liter- z alfabetu angielskiego");
        }
    }
nazwa = s;
}
kolornt::kolornt() : Kolor(), kolornazwany(),kolortransparentny(){}
kolornt::kolornt(int red,int green,int blue,int a,string n) : kolornazwany(red,green,blue,n),kolortransparentny(red,green,blue,a){}


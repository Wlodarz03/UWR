#include <iostream>
#include "nag.hpp"

using namespace std;

int obliczenia::wymierna::nwd(int a, int b){
    while (a!=b){
        if (a>b){
            a-=b;
        }
        else{
            b-=a;
        }
    }
    return a;
}
void obliczenia::wymierna::skroc(){
    while (nwd(abs(licz),abs(mian))!=1){
        int x = nwd(abs(licz),abs(mian));
        licz = licz/x;
        mian = mian/x;
    }
}
obliczenia::wymierna::wymierna() : licz(0), mian(1){}
obliczenia::wymierna::wymierna(int l) : licz(l), mian(1){}
obliczenia::wymierna::wymierna(int l, int m) : licz(l),mian(m){
    if (l>INT_MAX or m>INT_MAX){
        throw przekroczenie_zakresu("poza zakresem inta");
    }
    if (m==0){
        throw dzielenie_przez_0("Mianownik rowny 0");
    }
    else if (m<0){
        m=-m;
        l=-l;
    }
    licz=l;
    mian=m;
    skroc();
}
obliczenia::wymierna::wymierna(const wymierna& w) : licz(w.licz),mian(w.mian){}
obliczenia::wymierna& obliczenia::wymierna::operator=(const wymierna& w){
    this->licz = w.licz;
    this->mian = w.mian;
    return *this;
}
int obliczenia::wymierna::get_licz() const{
    return licz;
}
int obliczenia::wymierna::get_mian() const {
    return mian;
}
obliczenia::wymierna obliczenia::wymierna::operator+(const wymierna& w) const{
    int nowy_licz = licz*w.mian + w.licz*mian;
    int nowy_mian = mian * w.mian;
    return wymierna(nowy_licz,nowy_mian);
}
obliczenia::wymierna obliczenia::wymierna::operator-(const wymierna& w) const{
    int nowy_licz = licz*w.mian - w.licz*mian;
    int nowy_mian = mian * w.mian;
    return wymierna(nowy_licz,nowy_mian);
}
obliczenia::wymierna obliczenia::wymierna::operator*(const wymierna& w) const{
    int nowy_licz = licz * w.licz;
    int nowy_mian = mian * w.mian;
    return wymierna(nowy_licz,nowy_mian);
}
obliczenia::wymierna obliczenia::wymierna::operator/(const wymierna& w) const{
    int nowy_licz = licz * w.mian;
    int nowy_mian = mian * w.licz;
    return wymierna(nowy_licz,nowy_mian);
}
obliczenia::wymierna obliczenia::wymierna::operator-() const{
    return wymierna(-licz,mian);
}
obliczenia::wymierna obliczenia::wymierna::operator!() const{
    return wymierna(mian,licz);
}
obliczenia::wymierna::operator double() const{
    return static_cast<double>(licz)/ static_cast<double>(mian);
}
obliczenia::wymierna::operator int() const{
    if (static_cast<double>(licz)/static_cast<double>(mian) <0){
        return static_cast<int>(static_cast<double>(licz)/static_cast<double>(mian) - 0.5);
    }
    return static_cast<int>(static_cast<double>(licz)/static_cast<double>(mian) + 0.5);
}

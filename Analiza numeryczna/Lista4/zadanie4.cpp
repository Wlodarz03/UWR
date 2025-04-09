#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double funkcja(double x){
    return pow(x, 4) - log(x + 4);
}

int main(){
    double a1 = -1.2;
    double b1 = -0.8;
    double a2 = 1.0;
    double b2 = 1.2;
    int ilosc_krokow1 = log2((b1 - a1) / (2.0 * pow(10.0,-8))) + 1;
    int ilosc_krokow2 = log2((b2 - a2) / (2.0 * pow(10.0,-8))) + 1;
    double m1;
    double m2;
    for (int i = 1; i<=ilosc_krokow1; i++){
        m1 = (a1 + b1) / 2;
        if (funkcja(m1) < 0){
            b1 = m1;
        }
        else{
            a1 = m1;
        }
    }
    
    for (int i = 1; i<=ilosc_krokow2; i++){
        m2 = (a2 + b2) / 2;
        if (funkcja(m2) < 0){
            a2 = m2;
        }
        else{
            b2 = m2;
        }
    }
    cout << "Miejsce zerowe numer 1: " << setprecision(9) << m1 << endl;
    cout << "Miejsce zerowe numer 2: " << setprecision(9) << m2 << endl;
}
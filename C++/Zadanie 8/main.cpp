#include <iostream>
#include "nag.hpp"

using namespace std;

int main() {
    obliczenia::wymierna w(1,2);
    obliczenia::wymierna w1(1, -3);
    obliczenia::wymierna w2(1, 2);
    obliczenia::wymierna w3 = w1 + w2;
    obliczenia::wymierna w4 = w1 - w2;
    obliczenia::wymierna w5 = w1 * w2;
    obliczenia::wymierna w6 = w1 / w2;
    obliczenia::wymierna w7 = -w1;
    obliczenia::wymierna w8 = !w1;
    int wi = int(w1);
    double wd = double(w1);
    
    cout << "w1: " << w1.get_licz() << "/" << w1.get_mian() << endl;
    cout << "w2: " << w2.get_licz() << "/" << w2.get_mian() << endl;
    cout << "w1 + w2: " << w3.get_licz() << "/" << w3.get_mian() << endl;
    cout << "w1 - w2: " << w4.get_licz() << "/" << w4.get_mian() << endl;
    cout << "w1 * w2: " << w5.get_licz() << "/" << w5.get_mian() << endl;
    cout << "w1 / w2: " << w6.get_licz() << "/" << w6.get_mian() << endl;
    cout << "-w1: " << w7.get_licz() << "/" << w7.get_mian() << endl;
    cout << "!w1: " << w8.get_licz() << "/" << w8.get_mian() << endl;
    cout<<"w1 as int: "<<wi<<endl;
    cout<<"w1 as double: "<<wd<<endl;

    return 0;
}
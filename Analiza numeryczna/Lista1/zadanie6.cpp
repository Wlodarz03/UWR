#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;

double pi(int a){
    double sum = 0.0;
    for (int i=0; i<a; i++){
        sum=sum+4.0 * pow(-1,i) / (2.0 * i + 1.0);
    }
    return sum;
}

int main(){
    int i = 1;
    double blad = pow(10,-6);
    double wyn = pi(1);
    // while (abs(wyn - M_PI)>blad){
    //     i+=1;
    //     wyn=pi(i);
    //     cout<<(abs(wyn-M_PI))<<endl;
    // }
    cout<<setprecision(10)<<pi(1000000)<<endl;
    cout<<setprecision(10)<<pi(1000000-1)<<endl;
    cout<<i<<endl;
    return 0;
}
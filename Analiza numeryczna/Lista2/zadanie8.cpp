#include <iostream>
#include <cmath>

using namespace std;

double f(double x){
    return 14.0*289.0*(0.5-289.0*(pow(x,2)/24));
}

double f_0(double x){
    return 14.0 * (1.0 - cos(17.0 * x) / x * x);
}

int main(){
    for (int i = 11; i<=20;i++){
        cout<<"Dla i="<<i<<" wychodzi "<<f(pow(10,-i))<<endl;
    }
    return 0;
}
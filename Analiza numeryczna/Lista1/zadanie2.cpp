#include <iostream>
#include <cmath>

using namespace std;

int funkcja1(double x){
    return 4046*((sqrt(pow(x,14)+1)-1)/pow(x,14));
}

int main(){
    double x = 0.001;
    double result = funkcja1(x);
    cout<< "Wynik funkcji dla x=0.001: "<< result <<endl;
    
    return 0;
}
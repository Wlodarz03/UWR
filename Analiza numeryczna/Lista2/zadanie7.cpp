#include <iostream>
#include <cmath>

using namespace std;

double funkcja0(double x){
    return 4046*((sqrt(pow(x,14)+1)-1)/pow(x,14));
}

double funkcja1(double x){
    return 4046* (1.0 / (sqrt(pow(x,14)+1)+1));
}

int main(){
    double x = .001;
    cout<<funkcja0(x)<<endl;
    cout<<funkcja1(x);
}
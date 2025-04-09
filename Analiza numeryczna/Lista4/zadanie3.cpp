#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double funkcja(double x){
    return x - 0.49;
}

int main(){
    double a = 0.0;
    double b = 1.0;
    //roznica b0 - a0 = 1.0
    double alfa = 0.49;
    for (int i = 0; i <= 5; i++){
        double m = (a + b) / 2.0;
        double en = abs((alfa - m));
        double oszacowanie = pow(2.0, -i-1) / 1.0;
        cout << "n=" << i << " " << "|e" << i << "|= "<<en<< " | oszacowanie= " << oszacowanie<<endl;
        cout << "---------------------------------------------" << endl;
        if (funkcja(m) < 0) {
            a = m;
        }
        else {
            b = m;
        }
    }
    return 0;
}
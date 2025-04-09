#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double x1 = 2.0;
    double x1_poprawny = 2.0;
    cout << "Dla i=1 Ten pierwszy: " << x1 << " Ten poprawny: " << x1_poprawny<<endl;
    for (int i = 1;i<=50;i++){
        double x = pow(2, (i)) * sqrt(2.0 * (1.0 - sqrt(1.0 - pow((x1 / pow(2,i)), 2))));
        double x_poprawne = sqrt(2.0 * pow(x1_poprawny, 2) / (1.0 + sqrt(1.0 - pow(x1_poprawny / pow(2, i), 2))));
        x1=x;
        x1_poprawny = x_poprawne;
        cout << "Dla i=" << i+1 << " Ten pierwszy: " << x1 << " Ten poprawny: " << x1_poprawny << endl;
    }
}
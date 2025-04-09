#include <iostream>
#include <cmath>

using namespace std;

int main(){
    for (int i =11; i<=20; i++){
        float x_single = pow(10.0f,-i);
        double x_double = pow(10.0,-i);

        float single_result = 14.0f * (1.0f - cosf(17.0f * x_single))/(x_single*x_single);
        double double_result = 14.0 * (1.0 - cos(17.0*x_double))/(x_double*x_double);

        cout<<"i = "<< i << ", x_single = "<< x_single<<", x_double = "<<x_double<<endl;
        cout<<"Wynik w arytmetyce pojedynczej: "<<single_result<<endl;
        cout<<"Wynik w arytmetyce podwojnej: "<<double_result<<endl;
        cout<<endl;
    }
    
    return 0;
}
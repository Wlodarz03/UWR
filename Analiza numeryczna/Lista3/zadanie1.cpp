#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

double zad1av1(double x){
    return 1.0 / (pow(x, 3) + sqrt(pow(x, 6) + 2023.0 * 2023.0));
}

double zad1av2(double x){
    return (pow(x, 3) - sqrt(pow(x, 6) + 2023.0 * 2023.0)) / (-1.0 * 2023.0 * 2023.0);
}

double zad1bv1(double x){
    return log2(x) - 2.0;
}

double zad1bv2(double x){
    return log2(x / 4.0);
}

//acot(x) = atan(1/x) 
double zad1cv1(double x){
    return (M_PI / 2.0 - x - atan(1.0 / x)) / pow(x, 3);
}

double zad1cv2(double x){
    return -1.0 / 3.0 + x * x / 5.0;
}


int main(){
    cout << zad1av1(-100000000) << ' ' << zad1av2(-100000000) << '\n';
    cout << zad1bv1(4 - pow(10.0, -15)) << ' ' << zad1bv2(4 - pow(10.0, -15)) << '\n'; 
    cout << zad1cv1(pow(10.0, -10)) << ' ' << zad1cv2(pow(10.0, -10));
}

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double a = 0.25;
    double b = 10000.0;
    double c = 0.25;
    
    if (b>0){
        double x2liceum = (-b + sqrt( pow(b, 2) - 4.0 * a * c)) / 2.0 * a;
        double x2studia  = (2.0 * c) / (-b - sqrt( pow(b, 2) - 4.0 * a * c));
        double result2lic = a * pow(x2liceum, 2.0) + b * x2liceum + c;
        double result2stu = a * pow(x2studia, 2.0) + b * x2studia + c;
        cout<<"Wyniki dla liceum: "<<result2lic<<" x2: "<<x2liceum<<endl;
        cout<<"Wyniki teraz: "<<result2stu<<" x2: "<<x2studia<<endl;
    }
    else{
        double x1liceum = (-b - sqrt( pow(b, 2) - 4.0 * a * c)) / 2.0 * a;
        double x1studia = (2.0 * c) / (-b + sqrt( pow(b, 2) - 4.0 * a * c));
        double result1lic = a * pow(x1liceum, 2.0) + b * x1liceum + c;
        double result1stu = a * pow(x1studia, 2.0) + b * x1studia + c;
        cout<<"Wyniki dla liceum: "<<result1lic<<" x1: "<<x1liceum<<endl;
        cout<<"Wyniki teraz: "<<result1stu<<" x1: "<<x1studia<<endl;
    }

    return 0;
}
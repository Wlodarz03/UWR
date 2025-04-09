#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double a){
    return 1.0 / pow(x, 2) - a;
}

double pochodna(double x){
    return -2.0 * 1.0 / pow(x, 3);
}

double F(int n, double x0, double a){
    if (n == 0){
        return x0;
    }
    else{
        double xn = F(n-1, x0, a);
        return (3.0 / 2.0) * xn - (a / 2.0) * pow(xn, 3);
    }
}

//najlepiej wybrac x0 z przedzialu ( sqrt(1/3a), sqrt(5/3a) )

int main(){
    cout << "Test dla a = 3, x0 = 1/2" << endl;  
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, (1.0 / 2.0), 3.0) <<endl;
    }
    //  1/sqrt(3) => 0.577350 dla 4 iteracji juz jest git

    cout << "Test dla a = 12, x0 = 1/3" << endl;  
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, (1.0 / 3.0), 12.0) <<endl;
    }
    //  1/sqrt(12) => 0.2886751 tez dla 4 iteracji juz jest ok

    cout << "Test dla a = 27, x0 = 1/5" << endl;  
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, (1.0 / 5.0), 27.0) <<endl;
    }
    //  1/sqrt(27) => 0.19245009 tu juz dla 3 jest dobrze 
    return 0;
}
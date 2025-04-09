#include <iostream>
#include <cmath>

using namespace std;

double f(double x, int R){
    return 1.0/x - R;
}

double pochodna(double x){
    return -1.0 / pow(x,2);
}

double F(int n, double x0, int R){
    if (n == 0){
        return x0;
    }
    else{
        double xn = F(n-1, x0, R);
        return xn -  f(xn, R) / pochodna(xn);
    }
}

int main(){
    cout << "Testy dla R=5 i x0 = 1/10"<<endl;
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, (1.0 / 10.0), 5) << endl;
    }

    cout << "Testy dla R=5 i x0 = 1/4"<<endl;
    for (int i = 0; i<=15; i++){
        cout << "x" << i << " = " << F(i, (1.0 / 4.0), 5) << endl;
    }

    cout<< "Testy dla R=10 i x0 = 3/50"<<endl;
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, (3.0 / 50.0), 10) << endl;
    }

    cout << "Testy dla R=4 i x0 = 1/3"<<endl;
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, (1.0 / 3.0), 4) << endl;
    }

    cout<< "Testy dla R=2 i x0 = 1"<<endl; //nie dziala
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, 1.0, 2) << endl;
    }

    cout << "Testy dla R=5 i x0 = -1/20"<<endl; //nie dziala
    for (int i = 0; i<=10; i++){
        cout << "x" << i << " = " << F(i, -(1.0 / 20.0), 5) << endl;
    }
    return 0;
}
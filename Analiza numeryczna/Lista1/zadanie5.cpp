#include <iostream>
#include <math.h>

using namespace std;

double calka(int n){
    if (n==0){
        return log(2024.0/2023.0);
    }
    else{
        return 1.0/n - 2023.0*calka(n-1);
    }
}

int main(){
    for (int i=1; i<=20; i++){
        cout<<"Dla n="<<i<<" calka wynosi: "<<calka(i)<<endl;
    }

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

int main(){
    double y0 = 1.0;
    double y1 = -1.0/9.0;

    vector<double> results;
    results.push_back(y0);
    results.push_back(y1);

    for (int n=2; n<=50; n++){
        double yn = (80.0/9.0)*results[n-1] + results[n-2];
        results.push_back(yn);
    }
    for (int i=0; i<results.size(); i++){
        cout<<"y"<<i<<": "<<results[i]<<endl;
    }
    return 0;
}
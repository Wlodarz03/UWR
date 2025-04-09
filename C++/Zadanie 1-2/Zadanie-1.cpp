#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

string bin2rzym(int x){
    static const vector<pair<int,string> > rzym = {{1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},{100,"C"},{90,"XC"},{50,"L"},{40,"XL"},{10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}};
    string r = "";
    for (int i=0; i<rzym.size();i++){
        while ((x-rzym[i].first)>=0){
            r+=rzym[i].second;
            x-=rzym[i].first;
        }
    }
    return r;
}

bool isgood(string s){
    // if (s[0] == '0'){
    //     return 0;
    // }
    for (int j=0;j<s.size();j++){
        if (s[j]>'9' or s[j]<'0'){
            return 0;
        }
    }
    int n;
    try{n = stoi(s);}
    catch(...){
        return 0;
    }
    n=stoi(s);
    if (n>3999 or n<0){
        return 0;
    }
    return 1;   
}


int main(int argc,const char *argv[]) {
    if (argc<2){
        clog << "Za malo argumentow";
    }
    for (int i=1; i<argc;i++){
            string s = argv[i];
            if (isgood(s)){
                int a = stoi(s);
                cout << bin2rzym(a) << endl;

            }
            else{
                clog << "Blad" << endl;
                continue;
            }
    }
    return 0;
}
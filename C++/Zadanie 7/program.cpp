#include <iostream>
#include "gra.hpp"

using namespace std;

int main(){
    cout<<"Wybierz swoj znak (x lub o): ";
    char znak;
    cin>>znak;
    char aiz;
    if(znak=='x'){
        aiz ='o';
        gra::gra gra(znak,aiz);
        gra.gransko();
    }
    else if(znak=='o'){
        aiz='x';
        gra::gra gra(znak,aiz);
        gra.gransko();
    }
    else{
        while(znak!='x' or znak!='o'){
            clog<<"Wybierz x lub o"<<endl;
            cin>>znak;
        }
        gra::gra gra(znak,aiz);
        gra.gransko();
    }
    return 0;
}
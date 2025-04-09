#include <iostream>
#include "gra.hpp"
using namespace std;

void gra::gra::wybor_gracza(){
    while (true){
        cout<<"Twoj ruch: ";
        string ruch;
        cin>>ruch;
        if(ruch.length()!=2){
            clog<<"Nie ladnie, sprobuj jeszcze raz"<<endl;
        }
        else{
            int x = ruch[1]-'0';
            char y = ruch[0];
            if (x>=1 and x<=3){
                if(y=='A' or y=='B' or y=='C'){
                    if(stan.isFree(y,x)){
                        stan.wstaw_znak(znak_gracza,y,x);
                        break;
                    }
                }
            }
        }
    }
}
void gra::gra::wybor_ai(){
    pair<char,int> para = AI.ruch_komputera(stan);
    stan.wstaw_znak(znak_ai,para.first,para.second);
    
}
void gra::gra::gransko(){
    stan.display();
    while(true){
        if (tura){
            wybor_gracza();
            if(stan.win().first){
                break;
            }
            if(stan.isFull()){
                break;
            }
            tura=false;
        }
        else{
            cout<<"Ruch komputera: ";
            wybor_ai();
            stan.display();
            if(stan.win().first){
                break;
            }
            tura=true;
        }
    }
    char znakw = stan.win().second;
    if(znakw == znak_gracza){
        stan.display();
        cout<<"Koniec gry , wygral gracz"<<endl;
    }
    else if (znakw == znak_ai){
        stan.display();
        cout<<"Koniec gry, wygral komputer"<<endl;
    }
    else{
        stan.display();
        cout<<"Koniec gry, remis"<<endl;
    }
}
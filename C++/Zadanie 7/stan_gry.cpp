#include "stan_gry.hpp"
#include<iostream>
#include <iostream>
#include <stdexcept>

stan_gry::stan_gry::stan_gry(){
    for (int i = 0; i<3;i++){
        for (int j=0; j<3;j++){
            tabela[i][j] = '-';
        }
    }
}
void stan_gry::stan_gry::display(){
    std::cout<<"  A B C"<<std::endl;
    for (int i=0;i<3;i++){
        std::cout<<i+1<<" ";
        for (int j=0; j<3;j++){
            if(j==0){
                std::cout<<get_znak('A',i+1)<<" ";
            }
            if(j==1){
                std::cout<<get_znak('B',i+1)<<" ";
            }
            if(j==2){
                std::cout<<get_znak('C',i+1)<<" ";
            }
        }
        std::cout<<std::endl;
    }
}
bool stan_gry::stan_gry::isFree(char c,int indeks){
    if(tabela[indeks-1][dict[c]]=='o' or tabela[indeks-1][dict[c]]=='x'){
        return false;
    }
    else{
        return true;
    }
}
      
void stan_gry::stan_gry::wstaw_znak(char znak,char kolumna,int i){
    tabela[i-1][dict[kolumna]] = znak;
}
char stan_gry::stan_gry::get_znak(char c, int i){
    return tabela[i-1][dict[c]];
}
std::pair<bool,char> stan_gry::stan_gry::win(){
    for (int i=0;i<3;i++){
        if (tabela[i][0]==tabela[i][1] and tabela[i][1]==tabela[i][2] and tabela[i][0]!='-'){
            return std::make_pair(true,tabela[i][0]);
        }
    }
    for (int j=0;j<3;j++){
        if (tabela[0][j]==tabela[1][j] and tabela[1][j]==tabela[2][j] and tabela[0][j]!='-'){
            return std::make_pair(true,tabela[0][j]);
        }
    }
    if(tabela[0][0]==tabela[1][1] and tabela[1][1]==tabela[2][2] and tabela[0][0]!='-'){
        return std::make_pair(true,tabela[0][0]);
    }
    if(tabela[2][0]==tabela[1][1] and tabela[1][1]==tabela[0][2] and tabela[1][1]!='-'){
        return std::make_pair(true,tabela[2][0]);
    }
    return std::make_pair(false,'-');
}
bool stan_gry::stan_gry::isFull(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if (tabela[i][j]=='-'){
                return false;
            }
        }
    }
    return true;
}
#include <iostream>
#include <cstdlib>
#include <vector>
#include "stan_gry.hpp"
#include "AI.hpp"

AI::AI::AI(){
    srand(time(NULL));
}
std::pair<char,int> AI::AI::ruch_komputera(stan_gry::stan_gry& stan){
    while(true){
        int i = rand()%3 + 1;
        int j = rand()%3;
        if (stan.isFree(tab[j],i)){
            std::cout<<tab[j]<<i<<std::endl;
            return std::make_pair(tab[j],i);
            break;
        }
    }
}
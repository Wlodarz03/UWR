#ifndef STAN_GRY
#define STAN_GRY

#include <map>

namespace stan_gry
{
    class stan_gry{
        private:
            char tabela[3][3];
            std::map<char,int> dict= {{'A',0},{'B',1},{'C',2}};
        public:
            stan_gry();
            void display();
            void wstaw_znak(char znak,char kolumna,int i);
            bool isFree(char kolumna, int i);
            char get_znak(char c,int i);
            std::pair<bool,char> win();
            bool isFull();
    };
}

#endif
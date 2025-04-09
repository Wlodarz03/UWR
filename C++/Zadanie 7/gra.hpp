#include "AI.hpp"

namespace gra
{
    class gra{
        private:
            stan_gry::stan_gry stan;
            AI::AI AI;
            char znak_gracza;
            char znak_ai;
            bool tura;
        public:
            gra(char zg,char za) : stan(),tura(true),AI(),znak_gracza(zg),znak_ai(za){}
            void wybor_gracza();
            void wybor_ai();
            void gransko();
    };
}
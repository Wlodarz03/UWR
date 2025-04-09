#include "stan_gry.hpp"

namespace AI
{
    class AI{
        private:
            char tab[3] = {'A','B','C'};
        public:
            std::pair<char,int> ruch_komputera(stan_gry::stan_gry& stan);
            AI();
    };
}

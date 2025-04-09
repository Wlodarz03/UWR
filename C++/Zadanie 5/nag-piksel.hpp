#include "nag-kolor.hpp"

using namespace std;

class Piksel{
    protected:
        int x;
        int y;
        const static int szerokosc = 800;
        const static int dlugosc = 600;
    public:
        Piksel(int x, int y);
        int dlugosc_od_lewej() const;
        int dlugosc_od_gory() const;
        int dlugosc_od_dolu() const;
        int dlugosc_od_prawej() const;
};
class PikselKolorowy : public Piksel{
    protected:
        kolortransparentny k;
    public:
        PikselKolorowy(int x, int y, int red, int green,int blue,int a);

        int getRed();
        int getGreen();
        int getBlue();
        int getAlfa();
        void setRed(int red);
        void setGreen(int green);
        void setBlue(int blue);
        void setAlfa(int a);

        void przesuniecie(int _x, int _y);
};

int odleglosc(const Piksel& p1,const Piksel& p2);


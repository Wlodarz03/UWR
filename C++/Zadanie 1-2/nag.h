#ifndef NAG_H
#define NAG_H

#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

class wektor
{
public:
    double dx;
    double dy;
        wektor(double _x = 0, double _y = 0) : dx(_x), dy(_y) {}

        wektor(const wektor &v) : dx(v.dx), dy(v.dy) {}

        wektor &operator=(const wektor &v)
        {
            dx = v.dx;
            dy = v.dy;
            return *this;
        }
};
class prosta
{
public:
    double a;
    double b;
    double c;

    prosta(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    prosta(const prosta &pr) : a(pr.a), b(pr.b), c(pr.c) {}

    prosta &operator=(const prosta &pr)
    {
        a = pr.a;
        b = pr.b;
        c = pr.c;
        return *this;
    }
};
class punkt
{
public:
    double x;
    double y;

public:
    punkt(double _x, double _y) : x(_x), y(_y) {}

    punkt(const punkt &p) : x(p.x), y(p.y) {}

    punkt &operator=(const punkt &p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    void przesun(const wektor &v);
    void obroc(punkt p, double kat);
    void symetria_punkt(punkt p);
    void symetria_os(const prosta &pr);
};
class odcinek
{
public:
    punkt p1;
    punkt p2;

public:
    odcinek(punkt _p1, punkt _p2) : p1(_p1), p2(_p2)
    {
        if (p1.x == p2.x and p1.y == p2.y)
        {
            throw invalid_argument("Te same punkty, nie da sie zrobic odc");
        }
    }

    odcinek(const odcinek &o) : p1(o.p1), p2(o.p2) {}

    odcinek &operator=(const odcinek &o)
    {
        p1 = o.p1;
        p2 = o.p2;
        return *this;
    }
    void przesun_odc(const wektor &v);
    void obroc_odc(punkt p, double kat);
    void symetria_odc_punkt(punkt p);
    void symetria_odc_os(prosta pr);
    double dlugosc_odc();
    bool czy_w_odc(punkt p);
};
class trojkat
{
public:
    punkt p1;
    punkt p2;
    punkt p3;

public:
    trojkat(punkt _p1, punkt _p2, punkt _p3) : p1(_p1), p2(_p2), p3(_p3)
    {
        odcinek o1(p1, p2);
        odcinek o2(p1, p3);
        odcinek o3(p2, p3);
        if (max(max(o1.dlugosc_odc(), o2.dlugosc_odc()), o3.dlugosc_odc()) > o1.dlugosc_odc() + o2.dlugosc_odc() + o3.dlugosc_odc() - max(max(o1.dlugosc_odc(), o2.dlugosc_odc()), o3.dlugosc_odc()))
        {
            throw invalid_argument("nie da sie utworzyc trojkata z tych wierzcholkow");
        }
        else if ((p2.x-p1.x)*(p3.y-p1.y)==(p2.y-p1.y)*(p3.x-p1.x)){
            if(!(((p2.x-p1.x)*(p3.y-p1.y)==0 or (p2.x-p1.x)*(p3.y-p1.y)==-0) and (p2.y-p1.y)*(p3.x-p1.x)==0 or (p2.y-p1.y)*(p3.x-p1.x)==-0)){
                throw invalid_argument("wspoliniowe wierzcholki ");
            }
        }
    }

    trojkat(const trojkat &t) : p1(t.p1), p2(t.p2), p3(t.p3) {}

    trojkat &operator=(const trojkat &t)
    {
        p1 = t.p1;
        p2 = t.p2;
        p3 = t.p3;

        return *this;
    }
    void przesun_troj(const wektor &v);
    void obrot(punkt p, double kat);
    void symetria_troj_punkt(punkt p);
    void symetria_troj_os(prosta pr);
    double obwod();
    double pole();
    bool czy_w_troj(punkt p);
};

bool czy_rownolegle(odcinek o1, odcinek o2);
bool czy_prostopadle(odcinek o1, odcinek o2);
double distance_bet_2points(punkt p1, punkt p2);
bool czy_troj_rozlaczny(trojkat t1, trojkat t2);
bool czy_zawiera_sie_1w2(trojkat t1, trojkat t2);


#endif
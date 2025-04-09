#include <iostream>
#include <cmath>
#include "nag.h"

using namespace std;

class wektor {
    public:
        double dx;
        double dy;

        wektor(double _x = 0, double _y = 0) : dx(_x), dy(_y) {}

        wektor(const wektor& v) : dx(v.dx) , dy(v.dy) {}

        wektor& operator = (const wektor& v){
            dx = v.dx;
            dy = v.dy;
            return *this;
        } 
};

class prosta{
    public:
        double a;
        double b;
        double c;

        prosta(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

        prosta(const prosta& pr) : a(pr.a), b(pr.b), c(pr.c) {}

        prosta& operator = (const prosta& pr){
            a = pr.a;
            b = pr.b;
            c = pr.c;
            return *this;
        }
};

class punkt {
    public:
        double x;
        double y;

    public:
        punkt(double _x, double _y) : x(_x), y(_y) {}

        punkt(const punkt& p) : x(p.x), y(p.y) {}

        punkt& operator = (const punkt& p){
            x = p.x;
            y = p.y;
            return *this;
        }

        void przesun(const wektor& v){
            x += v.dx;
            y += v.dy;
        }

        void obroc(punkt pkt, double kat){
            double rad = kat*M_PI/180.0;
            double x2 = (x - pkt.x)*cos(rad) - (y - pkt.y)*sin(rad) + pkt.x;
            double y2 = (x - pkt.x)*sin(rad) + (y - pkt.y)*cos(rad) + pkt.y;
            x=x2;
            y=y2;
        }
        void symetria_punkt(punkt p){
            double x2 = 2*p.x - x;
            double y2 = 2*p.y - y;
            x=x2;
            y=y2;
        }

        void symetria_os(const prosta& pr){
            double d = abs(pr.a*x + pr.b*y + pr.c)/sqrt(pr.a*pr.a + pr.b*pr.b);
            prosta prostop(-pr.b, pr.a, pr.b*x - pr.a*y);
            punkt srodek(-((pr.c*prostop.b - prostop.c*pr.b)/(pr.a*prostop.b - prostop.a*pr.b)), (-(pr.a *prostop.c - prostop.a*pr.c)/(pr.a*prostop.b - prostop.a*pr.b)));
            if(pr.a*x+pr.b*y+pr.c==0){
                x = x;
                y = y;
            }
            if (srodek.x == -x){
                x = x;
                y = -y;
            }
            else if(srodek.y == y){
                x = -x;
                y = y;
            }
            else{
                x = 2*srodek.x - x;
                y = 2*srodek.y - y;
            }
        }
};

class odcinek{
    public:
        punkt p1;
        punkt p2;
    public:
        odcinek(punkt _p1, punkt _p2) : p1(_p1),p2(_p2) {
            if(p1.x == p2.x and p1.y==p2.y){
                throw invalid_argument("Te same punkty, nie da sie zrobic odc");
            }
        }

        odcinek(const odcinek& o) : p1(o.p1), p2(o.p2) {}

        odcinek& operator = (const odcinek& o){
            p1 = o.p1;
            p2 = o.p2;
            return *this;
        }

        void przesun_odc(const wektor& v){
            p1.przesun(v);
            p2.przesun(v);
        }

        void obroc_odc(punkt p, double kat){
            p1.obroc(p,kat);
            p2.obroc(p,kat);
        }

        void symetria_odc_punkt(punkt p){
            p1.symetria_punkt(p);
            p2.symetria_punkt(p);
        }

        void symetria_odc_os(prosta pr){
            p1.symetria_os(pr);
            p2.symetria_os(pr);
        }

        int dlugosc_odc(){
            int wyn = sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2));
            return wyn;
        }
        bool czy_w_odc(punkt p){
            if (p2.x != p1.x){
                    double a = (p2.y - p1.y) / (p2.x - p1.x);
                    double b = p1.y - a*p1.x;
                    if(p.y == a*p.x +b){
                        if ((p.x <= max(p1.x, p2.x) and p.x >= min(p1.x, p2.x)) and (p.y <= max(p1.y,p2.y) and p.y >= min(p1.y, p2.y))){
                            return true;
                        }
                        else{
                            return false;
                        }
                    }
                    else{
                        return false;
                    }
            }
            else{
                double a = 0.0;
                double b = p1.x;
                if(p.y == a*p.x +b){
                    if(p.y <= max(p1.y, p2.y) and p.y >= min(p1.y, p2.y)){
                        return true;
                    }
                    else{
                        return false;
                    }
                }   
                else{
                    return false;
                }
            } 
        }
};

class trojkat{
    public:
        punkt p1;
        punkt p2;
        punkt p3;
    public:
        trojkat(punkt _p1, punkt _p2, punkt _p3) : p1(_p1), p2(_p2), p3(_p3) {
            odcinek o1(p1,p2);
            odcinek o2(p1,p3);
            odcinek o3(p2,p3);
            if(max(max(o1.dlugosc_odc(),o2.dlugosc_odc()),o3.dlugosc_odc()) > o1.dlugosc_odc()+o2.dlugosc_odc()+o3.dlugosc_odc() - max(max(o1.dlugosc_odc(),o2.dlugosc_odc()),o3.dlugosc_odc())){
                throw invalid_argument("nie da sie utworzyc trojkata z tych wierzcholkow");
            }
            if(p1.x == p2.x and p1.x == p3.x){
                throw invalid_argument("nie da sie, leza na jednej prostej");
            }
            if(p1.y == p2.y and p1.y == p3.y){
                throw invalid_argument("nie da sie, leza na jednej prostej");
            }
        }

        trojkat(const trojkat& t) : p1(t.p1), p2(t.p2), p3(t.p3) {}

        trojkat& operator = (const trojkat& t) {
            p1 = t.p1;
            p2 = t.p2;
            p3 = t.p3;
            
            return *this;
        }
        void przesun_troj(const wektor& v){
            p1.przesun(v);
            p2.przesun(v);
            p3.przesun(v);
        }
        void obrot(punkt p, double kat){
            p1.obroc(p,kat);
            p2.obroc(p,kat);
            p3.obroc(p,kat);
        }
        void symetria_troj_punkt(punkt p){
            p1.symetria_punkt(p);
            p2.symetria_punkt(p);
            p3.symetria_punkt(p);
        }
        void symetria_troj_os(prosta pr){
            p1.symetria_os(pr);
            p2.symetria_os(pr);
            p3.symetria_os(pr);
        }
        int obwod(){
            odcinek o1(p1,p2);
            odcinek o2(p1,p3);
            odcinek o3(p2,p3);
            int obw = o1.dlugosc_odc() + o2.dlugosc_odc() + o3.dlugosc_odc();
            return obw;
        }
        int pole(){
            odcinek o1(p1,p2);
            punkt srodek((p1.x+p2.x)/2, (p1.y+p2.y)/2);
            odcinek o2(srodek,p3);
            int a = o1.dlugosc_odc();
            int h = o2.dlugosc_odc();
            int p = a*h/2;
            return p; 
        }
        bool czy_w_troj(punkt p){
            trojkat t1(p,p1,p2);
            trojkat t2(p,p1,p3);
            trojkat t3(p,p2,p3);
            int pole1 = t1.pole();
            int pole2 = t2.pole();
            int pole3 = t3.pole();
            int pole_calk = pole1 + pole2 + pole3;
            if(pole_calk == pole()){
                return true;
            }
            else{
                return false;
            } 
        }
};

bool czy_rownolegle(odcinek o1, odcinek o2){
    int a1 = (o1.p2.y - o1.p1.y)/(o1.p2.x - o1.p1.x);
    int a2 = (o2.p2.y - o2.p1.y)/(o2.p2.x - o2.p1.x);
    if (a1==a2){
        return true;
    }
    else{
        return false;
    }
}

bool czy_prostopadle(odcinek o1, odcinek o2){
    int a1 = (o1.p2.y - o1.p1.y)/(o1.p2.x - o1.p1.x);
    int a2 = (o2.p2.y - o2.p1.y)/(o2.p2.x - o2.p1.x);
    if(a1*a2 == -1){
        return true;
    }
    else{
        return false;
    }
}

double distance_bet_2points(punkt p1, punkt p2){
    int wyn = sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2));
    return wyn;
}
bool czy_troj_rozlaczny(trojkat t1,trojkat t2){
    punkt w1(t1.p1);
    punkt w2(t1.p2);
    punkt w3(t1.p3);
    punkt q1(t2.p1);
    punkt q2(t2.p2);
    punkt q3(t2.p3);
    if(t2.czy_w_troj(w1)==false and t2.czy_w_troj(w2)==false and t2.czy_w_troj(w3)==false){
        if(t1.czy_w_troj(q1)==false and t1.czy_w_troj(q2)==false and t1.czy_w_troj(q3)==false){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool czy_zawiera_sie_1w2(trojkat t1, trojkat t2){
    punkt w1(t1.p1);
    punkt w2(t1.p2);
    punkt w3(t1.p3);
    if(t2.czy_w_troj(w1)==true and t2.czy_w_troj(w2)==true and t2.czy_w_troj(w3)==true){
        return true;
    }
    else{
        return false;
    }
}


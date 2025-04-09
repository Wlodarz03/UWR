#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class wyrazenie{
    public:
        wyrazenie() = default;
        virtual ~wyrazenie() = default;
        wyrazenie(const wyrazenie&) = delete;
        wyrazenie& operator=(const wyrazenie&) = delete;
        virtual double oblicz() = 0;
        virtual string zapis() = 0;
};

class liczba : public wyrazenie{
    private:
        double wart;
    public:
        liczba(double w) : wart(w){}

        double oblicz(){
            return wart;
        }

        string zapis(){
            return to_string(wart);
        }
};
class stala : public wyrazenie{
    protected:
        string nazwa;
        double wart;
    public:
        stala(string n, double w) : nazwa(n),wart(w){}
        double oblicz(){
            return wart;
        }
        string zapis(){
            return nazwa;
        }
};
class pi : public stala{
    public:
        pi() : stala("pi", M_PI){}
        double oblicz(){
            return M_PI;
        }
        string zapis(){
            return "pi";
        }
};
class e : public stala{
    public:
        e() : stala("e", M_E){}
        double oblicz(){
            return M_E;
        }
        string zapis(){
            return "e";
        }
};
class fi : public stala{
    public:
        fi() : stala("fi", 1.618){}
        double oblicz(){
            return 1.618;
        }
        string zapis(){
            return "fi";
        }
};
class zmienna : public wyrazenie{
    protected:
        string nazwa;
        static int find_index(string _nazwa){
            for (int i = 0;i<zmienne.size();i++){
                if (zmienne[i].first == _nazwa){
                    return i;
                }
            }
            return -1;
        }
    public:
        static vector<pair<string, double>> zmienne;
        zmienna(string n) : nazwa(n){}
        double oblicz(){
            if (find_index(nazwa)==-1){
                throw new invalid_argument("Nie ma takiej zmiennej");
            }
            else{
                return zmienne[find_index(nazwa)].second;
            }
        }
        string zapis(){
            return nazwa;
        }

        static void dodaj(string _nazwa, double _wart){
            zmienne.push_back(make_pair(_nazwa, _wart));
        }
        static void usun(string _nazwa){
            if (find_index(_nazwa)==-1){
                throw new invalid_argument("Nie ma takiej zmiennej");
            }
            else{
                zmienne.erase(zmienne.begin() + find_index(_nazwa));
            }
        }
        static void modyfikuj(string _nazwa, double _wart){
            if(find_index(_nazwa)==-1){
                throw new invalid_argument("Nie ma takiej zmiennej");
            }
            else{
                zmienne[find_index(_nazwa)].second = _wart;
            }
        }
};
class operator1arg : public wyrazenie{
    protected:
        wyrazenie *argument;
    public:
        operator1arg(wyrazenie *arg) : argument(arg){}
        double oblicz() = 0;
        string zapis() = 0;
};

class sinus : public operator1arg{
    public:
        sinus(wyrazenie *arg) : operator1arg(arg){}
        double oblicz(){
            return sin(argument->oblicz());
        }
        string zapis(){
            return "sin("+argument->zapis()+")";
        }
};
class cosinus : public operator1arg{
    public:
        cosinus(wyrazenie *arg) : operator1arg(arg){}
        double oblicz(){
            return cos(argument->oblicz());
        }
        string zapis(){
            return "cos("+argument->zapis()+")";
        }
};
class exponent : public operator1arg{
    public:
        exponent(wyrazenie *arg) : operator1arg(arg){}
        double oblicz(){
            return exp(argument->oblicz());
        }
        string zapis(){
            return "exp("+argument->zapis()+")";
        }
};
class logarytmn : public operator1arg{
    public:
        logarytmn(wyrazenie *arg) : operator1arg(arg){}
        double oblicz(){
            if (argument->oblicz()>0){
                return log(argument->oblicz());
            }
            else{
                throw new invalid_argument("Zly argument");
            }
        }
        string zapis(){
            if(argument->oblicz()<0){
                throw new invalid_argument("Zly argument");
            }
            return "ln("+argument->zapis()+")";
        }
};
class bezwzgl : public operator1arg{
    public:
        bezwzgl(wyrazenie *arg) : operator1arg(arg){}
        double oblicz(){
            if(argument->oblicz() > 0){
                return argument->oblicz();
            }
            else{
                return -1* argument->oblicz();
            }
        }
        string zapis(){
            return "|"+argument->zapis()+"|";
        }
};
class przeciw : public operator1arg{
    public:
        przeciw(wyrazenie *arg) : operator1arg(arg){}
        double oblicz(){
            return -1 * argument->oblicz();
        }
        string zapis(){
            return "-"+argument->zapis();
        }
};
class odwrot : public operator1arg{
    public:
        odwrot(wyrazenie *arg) : operator1arg(arg){}
        double oblicz(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna tak");
            }
            return  1 / argument->oblicz();
        }
        string zapis(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna tak");
            }
            return "1/"+argument->zapis();
        }
};
class operator2arg : public operator1arg{
    protected:
        wyrazenie *argument2;
    public:
        operator2arg(wyrazenie *arg1, wyrazenie *arg2) : operator1arg(arg1), argument2(arg2){}
        double oblicz() = 0;
        string zapis() = 0;
};
class dodaj : public operator2arg{
    public:
        dodaj(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
        double oblicz(){
            return argument->oblicz() + argument2->oblicz();
        }
        string zapis(){
            return "("+argument->zapis()+"+"+argument2->zapis()+")";
        }
};
class odejmij : public operator2arg{
    public:
        odejmij(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
        double oblicz(){
            return argument->oblicz() - argument2->oblicz();
        }
        string zapis(){
            return "("+argument->zapis()+"-"+argument2->zapis()+")";
        }
};
class mnoz : public operator2arg{
    public:
        mnoz(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
        double oblicz(){
            return argument->oblicz() * argument2->oblicz();
        }
        string zapis(){
            return "("+argument->zapis()+"*"+argument2->zapis()+")";
        }
};
class dziel : public operator2arg{
    public:
        dziel(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
        double oblicz(){
            if (argument2->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return argument->oblicz() / argument2->oblicz();
        }
        string zapis(){
            if (argument2->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return "("+argument->zapis()+"/"+argument2->zapis()+")";
        }
};
class logarytm : public operator2arg{
    public:
        logarytm(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
        double oblicz(){
            double a = argument->oblicz();
            double b = argument2->oblicz();
            if (a>0 && a!=1 && b>0){
                return log(b)/log(a); //wzor logarytmow
            }
            throw new invalid_argument("Zle wyrazenia");
        }
        string zapis(){
            double a = argument->oblicz();
            double b = argument2->oblicz();
            if (a>0 and a!=1 and b>0){
                return "log_"+argument->zapis()+"("+argument2->zapis()+")";
            }
        }
};
class modulo : public operator2arg{
    public:
        modulo(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
        double oblicz(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return fmod(argument->oblicz(),argument2->oblicz());
        }
        string zapis(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return "("+argument->zapis()+"%"+argument2->zapis()+")";
        }
};
class potega : public operator2arg{
    public:
        potega(wyrazenie *arg1,wyrazenie *arg2) : operator2arg(arg1,arg2){}
        double oblicz(){
            return pow(argument->oblicz(), argument2->oblicz());
        }
        string zapis(){
            return "("+argument->zapis()+"^"+argument2->zapis()+")";
        }
};

vector<pair<string,double>> zmienna::zmienne;

// int main(){
//     zmienna :: dodaj("x",0);
//     zmienna :: dodaj("y",0);
//     wyrazenie *x = new zmienna("x");
//     wyrazenie *y = new zmienna("y");
//     wyrazenie *w1 = new dziel(new mnoz(new odejmij(x,new liczba(1)),x),new liczba(2));
//     wyrazenie *w2 = new dziel(new dodaj(new liczba(3),new liczba(5)),new dodaj(new liczba(2),new mnoz(x,new liczba(7))));
//     wyrazenie *w3 = new odejmij(new dodaj(new liczba(2),new mnoz(x,new liczba(7))),new dodaj(new mnoz(y,new liczba(3)),new liczba(5)));
//     wyrazenie *w4 = new dziel(new cosinus(new mnoz(new dodaj(x,new liczba(1)),new pi())),new potega(new e(),new potega(x,new liczba(2))));
//     cout<<"Wyrazenie pierwsze"<<endl;
//     cout<< w1->zapis()<<endl;
//     cout<<"Wyrazenie drugie"<<endl;
//     cout<<w2->zapis()<<endl;
//     cout<<"Wyrazenie trzecie"<<endl;
//     cout<<w3->zapis()<<endl;
//     cout<<"Wyrazenie czwarte"<<endl;
//     cout<<w4->zapis()<<endl;
//     cout<<"Wyniki dla pierwszego"<<endl;
//     for (double i = 0;i<=1.01;i+=0.01){
//         cout<<w1->oblicz()<<endl;
//         zmienna ::modyfikuj("x",i+0.01);
//     }
//     zmienna::modyfikuj("x",0);
//     cout<<"Wyniki dla drugiego"<<endl;
//     for (double i = 0;i<=1.01;i+=0.01){
//         cout<<w2->oblicz()<<endl;
//         zmienna :: modyfikuj("x",i+0.01);
//     }
//     zmienna:: modyfikuj("x",0);
//     cout<<"Wyniki dla trzeciego"<<endl;
//     for (double i = 0;i<=1.01;i+=0.01){
//         cout<<w3->oblicz()<<endl;
//         zmienna :: modyfikuj("x",i+0.01);
//         zmienna :: modyfikuj("y",i+0.01);
//     }
//     zmienna :: modyfikuj("x",0);
//     zmienna :: modyfikuj("y",0);
//     cout<<"Wyniki dla czwartego"<<endl;
//     for (double i = 0;i<=1.01;i+=0.01){
//         cout<<w4->oblicz()<<endl;
//         zmienna :: modyfikuj("x",i+0.01);
//     }
//     zmienna :: modyfikuj("x",0);
//     return 0;
// }
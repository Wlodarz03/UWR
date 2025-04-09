#include <iostream>
#include <vector>
#include <cmath>
#include "nag.hpp"

wyrazenie::wyrazenie() = default;
wyrazenie:: ~wyrazenie() = default;

liczba::liczba(double w) : wart(w){}
double liczba:: oblicz(){
            return wart;
        }
string liczba::zapis(){
            return to_string(wart);
        }

stala::stala(string n, double w) : nazwa(n),wart(w){}
double stala::oblicz(){
            return wart;
        }
string stala::zapis(){
            return nazwa;
        }

pi::pi() : stala("pi", M_PI){}
double pi::oblicz(){
            return M_PI;
        }
string pi::zapis(){
            return "pi";
        }

e::e() : stala("e", M_E){}
double e::oblicz(){
            return M_E;
        }
string e::zapis(){
            return "e";
        }

fi::fi() : stala("fi", 1.618){}
double fi::oblicz(){
            return 1.618;
        }
string fi::zapis(){
            return "fi";
        }

int zmienna::find_index(string _nazwa){
            for (int i = 0;i<zmienne.size();i++){
                if (zmienne[i].first == _nazwa){
                    return i;
                }
            }
            return -1;
        }
zmienna::zmienna(string n) : nazwa(n){}
double zmienna::oblicz(){
            if (find_index(nazwa)==-1){
                throw new invalid_argument("Nie ma takiej zmiennej");
            }
            else{
                return zmienne[find_index(nazwa)].second;
            }
        }
string zmienna::zapis(){
            return nazwa;
        }
void zmienna::dodaj(string _nazwa, double _wart){
            zmienne.push_back(make_pair(_nazwa, _wart));
        }
void zmienna::usun(string _nazwa){
            if (find_index(_nazwa)==-1){
                throw new invalid_argument("Nie ma takiej zmiennej");
            }
            else{
                zmienne.erase(zmienne.begin() + find_index(_nazwa));
            }
        }
void zmienna::modyfikuj(string _nazwa, double _wart){
            if(find_index(_nazwa)==-1){
                throw new invalid_argument("Nie ma takiej zmiennej");
            }
            else{
                zmienne[find_index(_nazwa)].second = _wart;
            }
        }

operator1arg::operator1arg(wyrazenie *arg) : argument(arg){}

sinus::sinus(wyrazenie *arg) : operator1arg(arg){}
double sinus::oblicz(){
            return sin(argument->oblicz());
        }
string sinus::zapis(){
            return "sin("+argument->zapis()+")";
        }

cosinus::cosinus(wyrazenie *arg) : operator1arg(arg){}
double cosinus::oblicz(){
            return cos(argument->oblicz());
        }
string cosinus::zapis(){
            return "cos("+argument->zapis()+")";
        }

exponent::exponent(wyrazenie *arg) : operator1arg(arg){}
double exponent::oblicz(){
            return exp(argument->oblicz());
        }
string exponent::zapis(){
            return "exp("+argument->zapis()+")";
        }

logarytmn::logarytmn(wyrazenie *arg) : operator1arg(arg){}
double logarytmn::oblicz(){
            if (argument->oblicz()>0){
                return log(argument->oblicz());
            }
            else{
                throw new invalid_argument("Zly argument");
            }
        }
string logarytmn::zapis(){
            if(argument->oblicz()<0){
                throw new invalid_argument("Zly argument");
            }
            return "ln("+argument->zapis()+")";
        }

bezwzgl::bezwzgl(wyrazenie *arg) : operator1arg(arg){}
double bezwzgl::oblicz(){
            if(argument->oblicz() >= 0){
                return argument->oblicz();
            }
            else{
                return -1* argument->oblicz();
            }
        }
string bezwzgl::zapis(){
            return "|"+argument->zapis()+"|";
        }

przeciw::przeciw(wyrazenie *arg) : operator1arg(arg){}
double przeciw::oblicz(){
            return -1 * argument->oblicz();
        }
string przeciw::zapis(){
            return "-"+argument->zapis();
        }

odwrot::odwrot(wyrazenie *arg) : operator1arg(arg){}
double odwrot::oblicz(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna tak");
            }
            return  1 / argument->oblicz();
        }
string odwrot::zapis(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna tak");
            }
            return "1/"+argument->zapis();
        }

operator2arg::operator2arg(wyrazenie *arg1, wyrazenie *arg2) : operator1arg(arg1), argument2(arg2){}

dodaj::dodaj(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
double dodaj::oblicz(){
            return argument->oblicz() + argument2->oblicz();
        }
string dodaj::zapis(){
            return "("+argument->zapis()+"+"+argument2->zapis()+")";
        }

odejmij::odejmij(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
double odejmij::oblicz(){
            return argument->oblicz() - argument2->oblicz();
        }
string odejmij::zapis(){
            return "("+argument->zapis()+"-"+argument2->zapis()+")";
        }

mnoz::mnoz(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
double mnoz::oblicz(){
            return argument->oblicz() * argument2->oblicz();
        }
string mnoz::zapis(){
            return argument->zapis()+"*"+argument2->zapis();
        }

dziel::dziel(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
double dziel::oblicz(){
            if (argument2->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return argument->oblicz() / argument2->oblicz();
        }
string dziel::zapis(){
            if (argument2->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return argument->zapis()+"/"+argument2->zapis();
        }

logarytm::logarytm(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
double logarytm::oblicz(){
            double a = argument->oblicz();
            double b = argument2->oblicz();
            if (a>0 and a!=1 and b>0){
                return log(b)/log(a); //wzor logarytmow
            }
            throw new invalid_argument("Zle wyrazenia");
        }
string logarytm :: zapis(){
            double a = argument->oblicz();
            double b = argument2->oblicz();
            if (a>0 and a!=1 and b>0){
                return "log_"+argument->zapis()+"("+argument2->zapis()+")";
            }
            else{
                throw new invalid_argument("Zle wyrazenia");
            }
        }

modulo::modulo(wyrazenie *arg1, wyrazenie *arg2) : operator2arg(arg1,arg2){}
double modulo:: oblicz(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return fmod(argument->oblicz(),argument2->oblicz());
        }
string modulo::zapis(){
            if(argument->oblicz()==0){
                throw new invalid_argument("Nie mozna dzielic przez 0");
            }
            return "("+argument->zapis()+"%"+argument2->zapis()+")";
        }

potega::potega(wyrazenie *arg1,wyrazenie *arg2) : operator2arg(arg1,arg2){}
double potega::oblicz(){
            return pow(argument->oblicz(), argument2->oblicz());
        }
string potega::zapis(){
            return "("+argument->zapis()+"^"+argument2->zapis()+")";
        }

vector<pair<string,double>> zmienna::zmienne;

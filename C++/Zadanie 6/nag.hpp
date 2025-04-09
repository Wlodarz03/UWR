#include <iostream>
#include <vector>

using namespace std;

class wyrazenie{
    private:
        wyrazenie(const wyrazenie&) = delete;
        wyrazenie& operator=(const wyrazenie&) = delete;
    public:
        wyrazenie();
        virtual ~wyrazenie();
        virtual double oblicz() = 0;
        virtual string zapis() = 0;
};
class liczba final : public wyrazenie{
    private:
        double wart;
    public:
        liczba(double w);
        double oblicz();
        string zapis();
};
class stala : public wyrazenie{
    protected:
        string nazwa;
        double wart;
    public:
        stala(string n, double w);
        double oblicz();
        string zapis();
};
class pi final : public stala{
    public:
        pi();
        double oblicz();
        string zapis();
};
class e final : public stala{
    public:
        e();
        double oblicz();
        string zapis();
};
class fi final : public stala{
    public:
        fi();
        double oblicz();
        string zapis();
};
class zmienna final : public wyrazenie{
    protected:
        string nazwa;
        static int find_index(string _nazwa);
    public:
        static vector<pair<string, double>> zmienne;
        zmienna(string n);
        double oblicz();
        string zapis();

        static void dodaj(string _nazwa, double _wart);
        static void usun(string _nazwa);
        static void modyfikuj(string _nazwa, double _wart);
};
class operator1arg : public wyrazenie{
    protected:
        wyrazenie *argument;
    public:
        operator1arg(wyrazenie *arg);
        double oblicz() = 0;
        string zapis() = 0;
};
class sinus : public operator1arg{
    public:
        sinus(wyrazenie *arg);
        double oblicz();
        string zapis();
};
class cosinus : public operator1arg{
    public:
        cosinus(wyrazenie *arg);
        double oblicz();
        string zapis();
};
class exponent : public operator1arg{
    public:
        exponent(wyrazenie *arg);
        double oblicz();
        string zapis();
};
class logarytmn : public operator1arg{
    public:
        logarytmn(wyrazenie *arg);
        double oblicz();
        string zapis();
};
class bezwzgl : public operator1arg{
    public:
        bezwzgl(wyrazenie *arg);
        double oblicz();
        string zapis();
};
class przeciw : public operator1arg{
    public:
        przeciw(wyrazenie *arg);
        double oblicz();
        string zapis();
};
class odwrot : public operator1arg{
    public:
        odwrot(wyrazenie *arg);
        double oblicz();
        string zapis();
};
class operator2arg : public operator1arg{
    protected:
        wyrazenie *argument2;
    public:
        operator2arg(wyrazenie *arg1, wyrazenie *arg2);
        double oblicz() = 0;
        string zapis() = 0;
};
class dodaj : public operator2arg{
    public:
        dodaj(wyrazenie *arg1, wyrazenie *arg2);
        double oblicz();
        string zapis();
};
class odejmij : public operator2arg{
    public:
        odejmij(wyrazenie *arg1, wyrazenie *arg2);
        double oblicz();
        string zapis();
};
class mnoz : public operator2arg{
    public:
        mnoz(wyrazenie *arg1, wyrazenie *arg2);
        double oblicz();
        string zapis();
};
class dziel : public operator2arg{
    public:
        dziel(wyrazenie *arg1, wyrazenie *arg2);
        double oblicz();
        string zapis();
};
class logarytm : public operator2arg{
    public:
        logarytm(wyrazenie *arg1, wyrazenie *arg2);
        double oblicz();
        string zapis();
};
class modulo : public operator2arg{
    public:
        modulo(wyrazenie *arg1, wyrazenie *arg2);
        double oblicz();
        string zapis();
};
class potega : public operator2arg{
    public:
        potega(wyrazenie *arg1,wyrazenie *arg2);
        double oblicz();
        string zapis();
};
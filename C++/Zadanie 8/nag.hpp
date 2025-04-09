#include <iostream>

using namespace std;

namespace obliczenia{
    class wyjatek_wymierny: public logic_error{
        public:
            wyjatek_wymierny(const string &err) : logic_error(err){}
    };
    class przekroczenie_zakresu: public wyjatek_wymierny{
        public:
            przekroczenie_zakresu(const string &err): wyjatek_wymierny(err){}
    };
    class dzielenie_przez_0 : public wyjatek_wymierny{
        public:
            dzielenie_przez_0(const string &err): wyjatek_wymierny(err){}
    };
    class wymierna{
        private:
            int licz,mian;
            int nwd(int a,int b);
            void skroc();
        public:
            wymierna();
            wymierna(int l,int m);
            wymierna(int l);
            wymierna(const wymierna& w);
            wymierna& operator=(const wymierna& w);
            int get_licz() const;
            int get_mian() const;
            wymierna operator+(const wymierna& w) const;
            friend wymierna operator+(int i, const wymierna& w);
            wymierna operator-(const wymierna& w) const;
            friend wymierna operator-(int i,const wymierna& w);
            wymierna operator*(const wymierna& w) const;
            friend wymierna operator*(int i, const wymierna& w);
            wymierna operator/(const wymierna& w) const;
            friend wymierna operator/(int i, const wymierna& w);
            wymierna operator-() const;
            wymierna operator!() const;
            explicit operator double() const;
            explicit operator int() const;
    };
    wymierna operator+(int i,const wymierna &w);
}
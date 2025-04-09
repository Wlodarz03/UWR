using namespace std;

class Kolor{
    protected:
        int r;
        int g;
        int b;
    public:
        Kolor();
        Kolor(int red, int green, int blue);
        int getRed();
        int getGreen();
        int getBlue();
        void setRed(int red);
        void setGreen(int green);
        void setBlue(int blue);
        void rozjasnianie(int x);
        void przyciemnij(int x);
        static Kolor laczenie(const Kolor &k1, const Kolor &k2);
};
class kolortransparentny : public virtual Kolor{
    protected:
        int alfa;
    public:
        kolortransparentny();
        kolortransparentny(int red,int green, int blue, int a);
        int getAlfa();
        void setAlfa(int a);
};
class kolornazwany : public virtual Kolor{
    protected:
        string nazwa;
    public:
        kolornazwany();
        kolornazwany(int red,int green,int blue,string s);

        string getNazwa();
        void setNazwa(string s);
};
class kolornt : public kolornazwany, public kolortransparentny{
    public:
        kolornt();
        kolornt(int red,int green,int blue,int a,string n);
};
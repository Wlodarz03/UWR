// #include <iostream>
// #include <string>
// #include <ctype.h>
// #include <cctype>
// #include <cmath>

// using namespace std;

// class Kolor{
//     protected:
//         int r;
//         int g;
//         int b;
//     public:
//         Kolor() : r(0), g(0), b(0){} //czarny
//         Kolor(int red, int green, int blue) : r(red), g(green), b(blue){
//             if (red<0 or red>255 or green<0 or green>255 or blue<0 or blue>255){
//                 throw out_of_range("Przekracza zakres");
//             }
//         }

//         int getRed(){
//             return r;
//         }
//         int getGreen(){
//             return g;
//         }
//         int getBlue(){
//             return b;
//         }
//         void setRed(int red){
//             if(red<0 or red>255){
//                 throw out_of_range("Przekracza zakres");
//             }
//             r = red;
//         }
//         void setGreen(int green){
//             if (green<0 or green>255){
//                 throw out_of_range("Przekracza zakres");
//             }
//             g = green;
//         }
//         void setBlue(int blue){
//             if (blue<0 or blue>255){
//                 throw out_of_range("Przekracza zakres");
//             }
//             b = blue;
//         }
//         void rozjasnianie(int x){
//             r = min(r + x,255);
//             g = min(g + x,255);
//             b = min(b + x,255);
//         }
//         void przyciemnij(int x){
//             r = max(r - x,0);
//             g = max(g - x,0);
//             b = max(b - x,0);
//         }
//         static Kolor laczenie(const Kolor &k1, const Kolor &k2){
//             int red = (k1.r + k2.r)/2;
//             int green = (k1.g + k2.g)/2;
//             int blue = (k1.b + k2.b)/2;
//             return Kolor(red,green,blue);
//         }
// };
// class kolortransparentny : public virtual Kolor{
//     protected:
//         int alfa;
//     public:
//         kolortransparentny() : Kolor(), alfa(0){}
//         kolortransparentny(int red,int green, int blue, int a) : Kolor(red,green,blue), alfa(a){
//             if(a<0 or a>255){
//                 throw out_of_range("Przekracza zakres");
//             }
//         }
//         int getAlfa(){
//             return alfa;
//         }
//         void setAlfa(int a){
//             if(a<0 or a>255){
//                 throw out_of_range("Przekracza zakres");
//             }
//             alfa = a;
//         }
// };
// class kolornazwany : public virtual Kolor{
//     protected:
//         string nazwa;
//     public:
//         kolornazwany() : Kolor(), nazwa(""){}
//         kolornazwany(int red,int green,int blue,string s): Kolor(red,green,blue), nazwa(s){
//             for(int i=0;i<s.size();i++){
//                 if(!islower(s[i]) or !isalpha(s[i])){
//                     throw invalid_argument("Nazwa nie sklada sie z samych małych liter- z alfabetu angielskiego");
//                 }
//             }
//         }

//         string getNazwa(){
//             return nazwa;
//         }
//         void setNazwa(string s){
//             for(int i=0;i<s.size();i++){
//                 if(!islower(s[i]) or !isalpha(s[i])){
//                     throw invalid_argument("Nazwa nie sklada sie z samych małych liter- z alfabetu angielskiego");
//                 }
//             }
//             nazwa = s;
//         }
// };
// class kolornt : public kolornazwany, public kolortransparentny{
//     public:
//         kolornt() : Kolor(), kolornazwany(),kolortransparentny(){}
//         kolornt(int red,int green,int blue,int a,string n) : kolornazwany(red,green,blue,n),kolortransparentny(red,green,blue,a){}

// };

// class Piksel{
//     protected:
//         int x;
//         int y;
//         const static int szerokosc = 800;
//         const static int dlugosc = 600;
//     public:
//         Piksel(int x, int y) : x(x), y(y){
//             if (x<0 or x>=szerokosc or y<0 or y>=dlugosc){
//                 throw out_of_range("Poza ekranem");
//             }
//         }
//         int dlugosc_od_lewej() const {
//             return x;
//         }
//         int dlugosc_od_gory() const{
//             return y;
//         }
//         int dlugosc_od_dolu() const{
//             return dlugosc-y;
//         }
//         int dlugosc_od_prawej() const{
//             return szerokosc-x;
//         }
// };
// class PikselKolorowy : public Piksel{
//     protected:
//         kolortransparentny k;
//     public:
//         PikselKolorowy(int x, int y, int red, int green,int blue,int a) : Piksel(x,y), k(red,green,blue,a){}

//         int getRed(){
//             return k.getRed();
//         }
//         int getGreen(){
//             return k.getGreen();
//         }
//         int getBlue(){
//             return k.getBlue();
//         }
//         int getAlfa(){
//             return k.getAlfa();
//         }
//         void setRed(int red){
//             k.setRed(red);
//         }
//         void setGreen(int green){
//             k.setGreen(green);
//         }
//         void setBlue(int blue){
//             k.setBlue(blue);
//         }
//         void setAlfa(int a){
//             k.setAlfa(a);
//         }

//         void przesuniecie(int _x, int _y){
//             if(x+_x<0 or x+_x>szerokosc or y+_y<0 or y+_y>dlugosc){
//                 throw out_of_range("Wyjdzie poza ekran");
//             }
//             x = x + _x;
//             y = y + _y;
//         }
// };
// int odleglosc(const Piksel& p1,const Piksel& p2){
//     int dx = p2.dlugosc_od_lewej() - p1.dlugosc_od_lewej();
//     int dy = p2.dlugosc_od_gory() - p1.dlugosc_od_gory();
//     int d = sqrt(dx*dx+dy*dy);
//     return d;
// }

// int main(){
//     Kolor k1 = Kolor(); //czarny
//     kolortransparentny k2(255,0,0,255); //czerwony
//     kolornazwany k3(0,255,0,"zielony"); //zielony
//     kolornt k4(0,0,0,0,"czarny");// czarny (kolornt)
//     Piksel p1(400,300);
//     PikselKolorowy p2(400,0,255,0,0,255); //czerwony piksel
//     cout<<"Czarny na czerwony"<<endl;
//     cout<<"Kolory: r="<<k1.getRed()<<" g="<<k1.getGreen()<<" b="<<k1.getBlue()<<endl;
//     k1.setRed(255);
//     cout<<"Po zmianie: "<<"Kolory: r="<<k1.getRed()<<" g="<<k1.getGreen()<<" b="<<k1.getBlue()<<endl;
//     cout<<""<<endl;
//     cout<<"Z czerwonego mocnego na czarny przezroczysty: "<<endl;
//     cout<<"Kolory: r="<<k2.getRed()<<" g="<<k2.getGreen()<<" b="<<k2.getBlue()<<" Alfa: "<<k2.getAlfa()<<endl;
//     k2.setAlfa(0);
//     k2.setRed(0);
//     cout<<"Po zmianie: "<<"Kolory: r="<<k2.getRed()<<" g="<<k2.getGreen()<<" b="<<k2.getBlue()<<" Alfa: "<<k2.getAlfa()<<endl;
//     cout<<""<<endl;
//     cout<<"Z zielonego na niebieski + zmiana nazwy:"<<endl;
//     cout<<"Kolory: r="<<k3.getRed()<<" g="<<k3.getGreen()<<" b="<<k3.getBlue()<<" Nazwa: "<<k3.getNazwa()<<endl;
//     k3.setNazwa("niebieski");
//     k3.setBlue(255);
//     k3.setGreen(0);
//     cout<< "Po zmianie: "<<"Kolory: r="<<k3.getRed()<<" g="<<k3.getGreen()<<" b="<<k3.getBlue()<<" Nazwa: "<<k3.getNazwa()<<endl;
//     cout<<""<<endl;
//     cout<<"Kolory: r="<<k4.getRed()<<" g="<<k4.getGreen()<<" b="<<k4.getBlue()<<" Nazwa: "<<k4.getNazwa()<<" Alfa: "<<k4.getAlfa()<<endl;
//     k4.setAlfa(56);
//     k4.setRed(255);
//     k4.setNazwa("czerwony");
//     cout<<"Po zmianie: "<<"Kolory: r="<<k4.getRed()<<" g="<<k4.getGreen()<<" b="<<k4.getBlue()<<" Nazwa: "<<k4.getNazwa()<<" Alfa: "<<k4.getAlfa()<<endl;
//     cout<<""<<endl;
//     cout<<"Odleglosc od gory: "<<p1.dlugosc_od_gory()<<endl;
//     cout<<"Odleglosc od dolu: "<<p1.dlugosc_od_dolu()<<endl;
//     cout<<"Odleglosc od lewej: "<<p1.dlugosc_od_lewej()<<endl;
//     cout<<"Odleglosc od prawej: "<<p1.dlugosc_od_prawej()<<endl;
//     cout<<""<<endl;
//     cout<<"Odleglosc miedzy p1 i p2: "<<odleglosc(p1,p2)<<endl;
//     p2.przesuniecie(0,200);
//     cout<<"Odleglosc miedzy p1 i p2 po przesunieciu "<<odleglosc(p1,p2)<<endl;
//     cout<<""<<endl;
//     cout<<"Kolory piksela p2 oraz alfa: "<<"r="<<p2.getRed()<<" g="<<p2.getGreen()<<" b="<<p2.getBlue()<<" alfa="<<p2.getAlfa()<<endl;
//     cout<<""<<endl;
//     cout<<"Proby niefajnych rzeczy: "<<endl;
//     p2.przesuniecie(500,500);
//     k1.setBlue(256);
//     k3.setNazwa("Biały");
//     k2.setAlfa(256);
//     return 0;
// }
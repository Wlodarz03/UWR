#include <iostream>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

void wait(int x){
    std::chrono::milliseconds czas(x);
    std::this_thread::sleep_for(czas);
}

class Character{
    private:
        int hp;
        int at;
        int normalhp;
        bool czy_atak_spec_uzyty;
    public:
        Character(int h,int a) : hp(h),at(a),normalhp(h),czy_atak_spec_uzyty(false){}
        int rzut_kostka(){
            srand(time(nullptr));
            int wynik = (rand()%6) + 1;
            return wynik; 
        }
        void strac_zycie(int dmg){
            hp-=dmg;
        }
        int getat(){
            return at;
        }
        int gethp(){
            return hp;
        }
        bool isdead(){
            if (hp <= 0){
                return true;
            }
            return false;
        }
        void heal(){
            hp=normalhp;
            czy_atak_spec_uzyty = false;
        }
        virtual void showstats(){
            cout<<"Zycie: "<<gethp()<<endl;
            cout<<"Atak: "<<getat()<<endl;
            cout<<"Atak specjalny: Brak"<<endl;
        };
        virtual void zwiekszat(int x){
            at+=x;
        }
        virtual void zwiekszhp(int x){
            normalhp+=x;
        }
        bool getas(){
            return czy_atak_spec_uzyty;
        }
        void changeas(){
            czy_atak_spec_uzyty=true;
        }
        virtual int atspec(){
            return 0;
        };
};

class Damian : public Character{
    private:
    public:
        Damian() : Character(2,1){}
        int atspec() override {
            if (getas()==false){
                changeas();
                cout<<"Rzuczasz kostka"<<endl;
                int rzut = rzut_kostka();
                if (rzut-3>=0){
                    cout<<"Twoj atak z kostki na wrogu wynosi: "<<rzut-3<<endl;
                    return rzut-3;
                }
                else{
                    cout<<"Twoja atak z kostki na wrogu wynosi: "<<rzut<<endl;
                    return rzut;
                }
            }
            else{
                clog<<"Zuzyles juz atak specjalny na ta walke"<<endl;
                return 0;
            }
        }
        void showstats() override{
            cout<<"     DAMIAN     "<<endl;
            cout <<"Zycie: " << gethp()<<endl;
            cout<<"Atak: " << getat()<<endl;
            cout<<"Atak-specjalny - rzucasz kostka i tyle ile wypadnie odjac 3 (jezeli wypadnie od 1 do 3 to tyle - 0) zadajesz przeciwnikowi (raz na walke)"<<endl;
            cout<<"Czy atak uzyty: "<<getas()<<endl;
        }
};

class Darek : public Character{
    public:
        Darek() : Character(1,2){}
        int atspec() override{
            if (getas() == false){
                changeas();
                cout<<"Rzuczasz kostka"<<endl;
                int rzut = rzut_kostka();
                if (rzut == 1 or rzut == 2){
                    return 1;
                }
                if (rzut == 3 or rzut == 4){
                    return 2;
                }
                else return 3;
            }
            else{
                clog<<"Zuzyles już swoj atak na ta walke"<<endl;
                return 0;
            }
        }
        void showstats(){
            cout<<"     DAREK    "<<endl;
            cout <<"Zycie: " << gethp()<<endl;
            cout<< "Atak: " << getat()<<endl;
            cout<<"Atak-specjalny - rzucasz kostka i do twojego rzutu kostka przy walce dodana jest liczba: "<<endl;
            cout<<"1 jesli wylosowales 1 lub 2"<<endl;
            cout<<"2 jesli wylosowales 3 lub 4"<<endl;
            cout<<"3 jesli wylosowales 5 lub 6"<<endl;
            cout<<"Czy atak uzyty: "<<getas()<<endl;
        }
};

class Monster{
    private:
        int hp;
        int at;
        int ilosc_oczek;
    public:
        Monster(int h,int a,int i) : hp(h),at(a),ilosc_oczek(i){}
        int bij(){
            return at;
        };
        virtual void otrzymaj_dmg(int dmg){
            hp-=dmg;
        };
        bool isdead(){
            if (hp <= 0){
                return true;
            }
            return false;
        };
        int getHP(){
            return hp;
        };
        int getiloscoczek(){
            return ilosc_oczek;
        }
        virtual void zwieksz_at(int x){
            at+=x;
        }
        virtual void zwieksz_hp(int x){
            hp+=x;
        }
        virtual void zwieksz_iloscoczek(int x){
            ilosc_oczek+=x;
        }
        virtual void info(){
            cout<<"Zycie: "<<getHP()<<endl;
            cout<<"Atak: "<<bij()<<endl;
            cout<<"Ilosc oczek: "<<getiloscoczek()<<endl;
        };
};

class Ork : public Monster{
    private:
        int ilosc_oczek;
        bool czy;
    public:
        Ork() : Monster(4,1,2), czy(false) {}
        void otrzymaj_dmg(int dmg) override {
            Monster::otrzymaj_dmg(dmg);
            if (getHP() <=2 and czy==false){
                Monster::zwieksz_hp(1);
                cout<<"HP potwora sie zwieksza"<<endl;
                czy=true;
            }
        }
        void info() override {
            cout<<"    ORK    "<<endl;
            cout<<"Zycie: "<<getHP()<<endl;
            cout<<"Atak: "<< bij()<<endl;
            cout<<"Ilosc oczek: "<<getiloscoczek()<<endl;
            cout<<"Kiedy ork ma <= 2 zycia leczy sobie 1 pkt zycia"<<endl;
        }
};

class Trol : public Monster{
    private:
        int ilosc_oczek;
        bool czy;
    public:
        Trol() : Monster(3,2,3) , czy(false) {}
        void otrzymaj_dmg(int dmg) override {
            Monster::otrzymaj_dmg(dmg);
            if (getHP()<=1 and czy==false){
                cout<<"Ilosc oczek potwora zwieksza sie a jego atak maleje"<<endl;
                zwieksz_iloscoczek(2);
                zwieksz_at(-1);
                czy=true;
            }
        }
        void info() override {
            cout<<"     TROL    "<<endl;
            cout<<"Zycie: "<<getHP()<<endl;
            cout<<"Atak: "<< bij()<<endl;
            cout<<"Ilosc oczek: "<<getiloscoczek()<<endl;
            cout<<"Kiedy trol ma <= 1 zycia zwieksza sie jego ilosc oczek do zadania obrazen do 5 ale atak sie zmniejsza o 1"<<endl;
        }
};

class Boss : public Monster{
    private:
        int hp;
        int at;
        int ilosc_oczek;
    public:
        Boss() : Monster(5,3,4){}
        void info() override {
            cout<<"    BOSS      "<<endl;
            cout<<"Zycie: "<<getHP()<<endl;
            cout<<"Atak: "<<bij()<<endl;
            cout<<"Ilosc oczek: "<<getiloscoczek()<<endl;
            cout<<"Boss nie ma zadnej dodatkowej umiejetnosci, on po prostu jest trudny"<<endl;
        }
};
class Nagroda{
    private:
        int x;
    public:
        Nagroda(int x_) : x(x_){}
        virtual int getn(){
            return x;
        }
};
class NagrodaHP : public Nagroda{
    public:
        NagrodaHP(int HP) : Nagroda(HP){}
        int getn() override{
            return Nagroda::getn();
        } 
};

class NagrodaAT : public Nagroda{
    public:
        NagrodaAT(int AT) : Nagroda(AT) {}
        int getn() override {
            return Nagroda::getn();
        }
};

class Walka{
    private:
        Character* gracz;
        Monster* potwor;
        Nagroda* nagroda;
        bool wl;
    public:
        Walka(Character* gracz_ , Monster* potwor_, Nagroda* nagroda_) : gracz(gracz_),potwor(potwor_),nagroda(nagroda_){}
        void atakuj(int x){
            int rzut = gracz->rzut_kostka();
            cout<<"Rzut kostka: "<<rzut+x<<endl;
            if (rzut + x >= potwor->getiloscoczek()){
                cout<<"Brawo trafiles potwora"<<endl;
                potwor->otrzymaj_dmg(gracz->getat());
            }
            else{
                cout<<"Niestety nie trafiles"<<endl;
                gracz->strac_zycie(potwor->bij());
            }
        }
        bool getwinorlose(){
            return wl;
        }
        void rozpocznij(){
            cout<<"Start walki"<<endl;
            while (true){
                cout<<"Wybierz 1 jesli chcesz rzucic kostka aby zaatakowac"<<endl;
                cout<<"Wybierz 2 jesli chcesz uzyc swojego ataku specjalnego (o ile jeszcze mozesz)"<<endl;
                wait(1000);
                int numer;
                cout<<"Wprowadz numer: ";
                cin>>numer;
                if (numer == 1){
                    atakuj(0);
                }
                else if(numer == 2){
                    Damian* g1 = dynamic_cast<Damian*>(gracz);
                    Darek* g2 = dynamic_cast<Darek*>(gracz);
                    if (g1 != nullptr){
                        potwor->otrzymaj_dmg(gracz->atspec());
                    }
                    else{
                        int x = gracz->atspec();
                        cout<<"Bonus z ataku specjalnego: "<<x<<endl;
                        atakuj(x);
                    }
                }
                wait(3000);
                if (potwor->isdead()){
                    potwor->info();
                    NagrodaAT* nat = dynamic_cast<NagrodaAT*>(nagroda);
                    NagrodaHP* nhp = dynamic_cast<NagrodaHP*>(nagroda);
                    cout<<"Brawo zabiles potwora"<<endl;
                    if (nat != nullptr){
                        cout<<"Zwieksza ci sie atak o 1"<<endl;
                        gracz->zwiekszat(nagroda->getn());
                    }
                    else{
                        cout<<"Zwieksza ci sie zycie o 1"<<endl;
                        gracz->zwiekszhp(nagroda->getn());
                    }
                    wl=true;
                    gracz->heal();
                    break;
                }
                else if (gracz->isdead()){
                    gracz->showstats();
                    cout<<"Zginales, koniec gry"<<endl;
                    wl=false;
                    break;
                }
                else{
                    gracz->showstats();
                    cout<<""<<endl;
                    potwor->info();
                    cout<<""<<endl;
                    continue;
                }

            }
        }
};

int main(){
    cout<<"Witamy w grze!"<<endl;
    cout<<"Twoim celem bedzie pokonanie bossa, na swojej drodze do niego napotkasz 3 przeciwnikow"<<endl;
    cout<<"Walka polega na wyrzuceniu odpowiedniej ilosci oczek aby zadac im obrazenia"<<endl;
    cout<<"Jesli sie nie uda to ty otrzymujesz obrazenia, po kazdej wygranej walce czeka cie bonus"<<endl;
    cout<<"Jesli zginiesz game over :("<<endl;
    cout<<"ZACZYNAJMNY!"<<endl;
    cout<<""<<endl;
    wait(10000);
    cout<<"Wybierz postac (wybierz numer)" <<endl;
    cout<< "1. Damian"<<endl;
    cout<< "2. Darek"<<endl;
    wait(2000);
    Character* pDam = new Damian();
    cout<<""<<endl;
    Character* pDar = new Darek();
    pDam->showstats();
    pDar->showstats();
    int numer;
    cout<<"Wprowadz numer: ";
    cin>>numer;
    Character* gracz=nullptr;
    if (numer==1){
        gracz = new Damian();
    }
    else{
        gracz = new Darek();
    }
    wait(1000);
    cout<<"Pierwszy przeciwnik wyskakuje - Trol. Zaczynasz walke"<<endl;
    cout<<"Po kazdym ataku wyswietli sie aktualne info o przeciwniku"<<endl;
    wait(1000);
    Monster* trol = new Trol();
    Nagroda* nag1 = new NagrodaHP(1);
    trol->info();
    wait(5000);
    Walka w1(gracz, trol,nag1);
    w1.rozpocznij();
    wait(1000);
    if (w1.getwinorlose()){
        cout<<"Gratuluje pierwszej wygranej przed toba jeszcze 2 przeciwnikow a na koncu boss"<<endl;
    }
    else{
        cout<<"Niestety ale przegrales, dziekuje za gre"<<endl;
        return 0;
    }
    wait(7000);
    cout<<"Przed toba kolejny przeciwnik - Ork. Powodzenia!"<<endl;
    cout<<"Po kazdym ataku wyswietli sie aktualne info o przeciwniku"<<endl;
    wait(1000);
    Ork* ork = new Ork();
    Nagroda* nag2 = new NagrodaAT(1);
    ork->info();
    wait(5000);
    cout<<"Twoje aktualne zycie po ostatniej walce: "<<gracz->gethp()<<endl;
    Walka w2(gracz,ork,nag2);
    w2.rozpocznij();
    wait(2000);
    if (w2.getwinorlose()){
        cout<<"Gratulacje idzie ci coraz lepiej, zostal ci ostatni przeciwnik przed bossem"<<endl;
    }
    else{
        cout<<"Niestety konczy sie twoja przygoda, dziekuje za gre"<<endl;
        return 0;
    }
    wait(7000);
    cout<<"Po raz kolejny musisz zmierzyc sie z Trolem. Trzymam kciuki!"<<endl;
    cout<<"Po kazdym ataku wyswietli sie aktualne info o przeciwniku"<<endl;
    wait(1000);
    Monster* trol2 = new Trol();
    trol2->info();
    wait(4000);
    cout<<"Twoj aktualny atak po ostatniej walce: "<<gracz->getat()<<endl;
    Walka w3(gracz, trol2,nag1);
    w3.rozpocznij();
    if (w3.getwinorlose()){
        cout<<"Gratulacje pokonales juz wszystkich przeciwnikow, zostal ci BOSS"<<endl;
    }
    else{
        cout<<"Doszedles juz bardzo daleko, calkiem niezle ale niestety przegrywasz, dziekuje za gre"<<endl;
        return 0;
    }
    wait(7000);
    cout<<"Pojawia sie BOSS, twoja ostatnia walka, powodzenia ;)"<<endl;
    cout<<"Po kazdym ataku wyswietli sie aktualne info o przeciwniku"<<endl;
    wait(1000);
    Monster* boss = new Boss();
    boss->info();
    wait(4000);
    cout<<"Twoje aktualne zycie po poprzedniej walce: "<<gracz->gethp()<<endl;
    Walka w4(gracz,boss,nag2);
    w4.rozpocznij();
    if (w4.getwinorlose()){
        cout<<"BRAWO!!! Wygrales cala gre!"<<endl;
    }
    else{
        cout<<"Bardzo mi przykro ale niestety przegrales :( ale mozesz sprobowac ponownie"<<endl;
    }
    wait(4000);
   return 0;
}
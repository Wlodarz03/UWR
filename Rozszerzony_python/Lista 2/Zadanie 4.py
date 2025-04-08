import string
import random

tekst_z_zadania = "Podział peryklinalny inicjałów wrzecionowatych kambium charakteryzuje się ścianą podziałową inicjowaną w płaszczyźnie maksymalnej."

#do pobrania z inwokacji
#https://polska-poezja.pl/lista-wierszy/141-adam-mickiewicz-pan-tadeusz-inwokacja

with open('inwokacja.txt','r',encoding='utf-8') as plik:
    zawartosc = plik.read()


def uprosc_zdanie(tekst,dl_slowa,liczba_slow):

    slowa=tekst.split()
    slowa_bez_interpunkcji = [slowo.strip(string.punctuation) for slowo in slowa]
    nowy_tekst=[]

    for slowo in slowa_bez_interpunkcji:
        if len(slowo)<=dl_slowa:
            nowy_tekst.append(slowo)

    ilosc_do_usuniecia = len(nowy_tekst)-liczba_slow
    usuniete_slowa = random.sample(nowy_tekst,ilosc_do_usuniecia)

    for s in usuniete_slowa:
        nowy_tekst.remove(s)

    final_tekst = " ".join(nowy_tekst)
    return final_tekst

print(uprosc_zdanie(tekst_z_zadania,10,5))
print(uprosc_zdanie(zawartosc,10,20))
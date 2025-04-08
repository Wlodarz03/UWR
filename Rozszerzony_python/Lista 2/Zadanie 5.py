
def kompresja(tekst):
    #tekst = tekst.replace(" ","")
    komp = []
    for i in range(len(tekst)):
        j=0
        if i==0:
            komp.append((1,tekst[i]))
            j+=1
        else:
            if tekst[i]==tekst[i-1]:
                tup = komp[j-1]
                new_tup=(tup[0]+1,tup[1])
                komp[j-1]=new_tup
            else:
                komp.append((1,tekst[i]))
                j+=1
    return komp

def dekompresja(tekst_skompresowany):
    tekst=""
    for i in tekst_skompresowany:
        tekst+=i[0]*i[1]
    return tekst

#do pobrania z inwokacji
#https://polska-poezja.pl/lista-wierszy/141-adam-mickiewicz-pan-tadeusz-inwokacja
with open('inwokacja.txt','r',encoding='utf-8') as plik:
    zawartosc = plik.read()

skompresowany = kompresja(zawartosc)
dekompresowany = dekompresja(skompresowany)


print(dekompresowany==zawartosc)
print()
print(dekompresowany)

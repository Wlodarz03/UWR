
def dhondt(glosy,liczba_miejsc):
    suma=sum([glosy[g] for g in glosy])
    min = suma*0.05

    sorted_komitety = {}
    for komitet in glosy:
        if glosy[komitet]>min:
            sorted_komitety[komitet] = glosy[komitet] #przechodza dalej tylko te komitety które otrzymały więcej niż 5% głosów

    wyniki = {}
    for komitet in sorted_komitety:
        wyniki[komitet]=0 #inicjalizacja wynikow

    ilorazy={}
    for komitet in sorted_komitety:
        ilorazy[komitet]=2  #inicjalizacja ilorazów do późniejszego dzielenia

    for i in range(liczba_miejsc):
        m = max(sorted_komitety,key=sorted_komitety.get)
        #print(m)  kolejnosc mandatow (tak samo jak w wikipedii)
        wyniki[m]+=1
        sorted_komitety[m]=glosy[m]/ilorazy[m]
        ilorazy[m]+=1

    return wyniki


glosy = {
    'Komitet A': 720,
    'Komitet B': 300,
    'Komitet C': 480,
}
print(dhondt(glosy,8)) #Przykład z wikipedii
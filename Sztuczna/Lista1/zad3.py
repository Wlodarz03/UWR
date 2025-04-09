'''
Mam dwie talie (figuranta i blotkarza) z których będę losował rękę w funkcji losuj_reke()
Na podstawie wylosowanej reki sprawdzam jaka ma ocene (im wyższa liczba tym lepsza ręka)
Blotkarz wygrywa z figurantem tylko wtedy kiedy jego ręka jest lepsza od niego, bo jeżeli
każdy ma np. parę to wtedy i tak wygrywa figurant (każda jego para jest lepsza od najlepszej pary blotkarza)
Potem robię symulacje pojedynków blotkarza i figuranta i sprawdzam w ilu procentach wygrywa blotkarz.
Najlepszy deck blotkarza - funkcja, która jako input dostaje minimum kart jakie chcemy aby blotkarz miał w decku
Sprawdzam wtedy wszystkie kombinacje decku (gdzie w decku jest minimum podana przez nas ilosc kart)
z którego wyrzucam blotki. Np. podaje że w decku ma być 32 karty, czyli wyrzucam jedną blotkę
(wszystkie jej kolory) więc możliwe kombinacje to: deck bez 2, bez 3 ażd do 10 i dla każdej kombinacji
robię symulacje aby ocenić bez jakich blotek ten deck ma największe ppb wygrania z figurantem.
'''

import random
from collections import Counter
import itertools

figury = [f"{fig}{kolor}" for fig in "AKQJ" for kolor in "HDSC"]
blotki = [f"{blot}{kolor}" for blot in map(str, range(2, 11)) for kolor in "HDSC"]

wartosci_map = ['0', '0', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']

def losuj_reke(talia):
    return random.sample(talia, 5)

def czy_strit(wartosci):
    wartosci = sorted(wartosci_map.index(v) for v in wartosci)  # Zamiana na wartości numeryczne
    return wartosci == list(range(wartosci[0], wartosci[0] + 5))

def ocena_reki(reka):
    wartosci = [k[:-1] for k in reka]  # Usunięcie koloru, zostają same wartości
    kolory = [k[-1] for k in reka]  # Zostają same kolory

    licznik = Counter(wartosci)  # Liczymy wartości kart
    kolory_licznik = Counter(kolory)  # Liczymy kolory

    wartosci_count = sorted(licznik.values(), reverse=True)
    czy_kolor = max(kolory_licznik.values()) == 5
    czy_str = czy_strit(wartosci)

    if czy_str and czy_kolor:
        return 8  # Poker (Straight Flush)
    if wartosci_count == [4, 1]:
        return 7  # Kareta
    if wartosci_count == [3, 2]:
        return 6  # Full House
    if czy_kolor:
        return 5  # Kolor
    if czy_str:
        return 4  # Strit
    if wartosci_count == [3, 1, 1]:
        return 3  # Trójka
    if wartosci_count == [2, 2, 1]:
        return 2  # Dwie Pary
    if wartosci_count == [2, 1, 1, 1]:
        return 1  # Para
    return 0  # Wysoka Karta

def symulacja(liczba_gier, blot):
    wygrane_blotkarza = 0

    for _ in range(liczba_gier):
        reka_figuranta = losuj_reke(figury)
        reka_blotkarza = losuj_reke(blot)

        if ocena_reki(reka_blotkarza) > ocena_reki(reka_figuranta):
            wygrane_blotkarza += 1

    return wygrane_blotkarza / liczba_gier

# min_kart_w_decku musi być co najmniej 5 aby dało się wybrać 5 kart do ręki
def najlepszy_deck(min_kart_w_decku):
    best = 0
    best_deck = []
    # Muszą być co najmniej 2 blotki
    for i in range((min_kart_w_decku // 4) + 1, 10):
        kombinacje = itertools.combinations(range(2, 11), i)
        for k in kombinacje:
            blots = [f"{blot}{kolor}" for blot in map(str, k) for kolor in "HDSC"]
            wynik = symulacja(1000, blots)
            if wynik > best:
                best = wynik
                best_deck = blots
    return best, best_deck

best_ppb, best_deck = najlepszy_deck(8)
print(f"Największe prawdopodobieństwo wygranej Blotkarza: {best_ppb:.2%} z deckiem {best_deck}")

normal_ppb = symulacja(10000, blotki)
print(f"Prawdopodobieństwo wygranej Blotkarza: {normal_ppb:.2%} z normalnym deckiem")
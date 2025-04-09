import random
import numpy as np
from itertools import combinations
from collections import Counter

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

def count_combinations(deck):
    counts = np.zeros(9) #liczenie układów 
    all_combinations = combinations(deck, 5) # wszystkie możliwe kombinacji 5 kart
    for cards in list(all_combinations):
        counts[ocena_reki(cards)] += 1
    return counts

blots = count_combinations(blotki)
figs = count_combinations(figury)
all_possible_fights = blots.sum() * figs.sum()
print(all_possible_fights)
result = 0
for i in range(1, 9):
    for j in range(i):
        result += blots[i] * figs[j]
result = result / all_possible_fights
print(result * 100)
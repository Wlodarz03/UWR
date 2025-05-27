'''
Mam funkcję pomocniczą min_moves, która zwraca minimalną liczbę ruchów aby przejść ze stanu input do target.
Jest to po prostu policzenie miejsc w których bity się nie zgadzają i trzeba je tam zamienić.
Funkcja opt_dist tworzy targetowe listy bitów (wsadza blok '1' długości d w każde możliwe miejsce w wierszu)
i sprawdza pomocniczą funkcją ile potrzeba zmian bitów aby przejść z naszej listy w target.
Na koniec zwraca minimum ruchów z tych wszystkich możliwości.
'''

import math

with open('zad4_input.txt', 'r') as file:
    input_lines = [line.split(' ') for line in file]

def min_moves(input, target):
    moves = 0
    for i in range(len(input)):
        if input[i] != target[i]:
            moves += 1
    return moves

def opt_dist(list, d):
    list = [int(el) for el in list]
    possibilities = len(list) - d + 1
    minimum = math.inf
    for i in range(possibilities):
        target = [0 for _ in range(len(list))]
        for j in range(i, i+d):
            target[j] = 1
        min = min_moves(list, target)
        if min < minimum:
            minimum = min
    return minimum

def main():
    f = open('zad4_output.txt', "w")
    for line in input_lines:
        list = line[0]
        d = int(line[1])
        result = opt_dist(list, d)
        f.write(str(result) + "\n")
    f.close()

main()
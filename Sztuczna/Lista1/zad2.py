'''
Dynamik -> tablica d[i] zawiera max suma kwadratów długości słów w prefiksie od 0 do i
Sprawdzam wszystkie sufiksy tego prefiksu czy jest w nim słowo, które należy do zbioru słów.
Jeśli jest to sprawdzam czy dodanie tego sufiksu jako kolejne słowo (po spacji) zwiększa sume kwadratów
długości słów w tym prefiksie. Ten warunek sprawia, że jak mam słowo "księga" nie zrobi mi z tego
"k" i "sięga" bo wolimy długie słowa. Potem dzięki tablicy prev[i], która trzyma początek słowa
na indeksi i jestem w stanie odtworzyć ten wiersz ze spacjami.
'''
with open('words.txt', 'r') as file:
    words = [line[:-1] for line in file]

words = set(words)

with open('zad2_input.txt', 'r') as file:
    lines = [line.rstrip('\n') for line in file]

def add_whitespaces(line):
    n = len(line)
    d = [-1] * (n + 1) # d[i] - najdłuższe długości słów dla prefiksu line[0:i]
    prev = [-1] * (n + 1)  # prev[i] - początek ostatniego słowa, które kończy się na indeksie i w optymalnym podziale
    d[0] = 0

    for i in range(1, n + 1):
        for j in range(0, i):
            word = line[j:i]
            if word not in words:
                continue
            score = d[j] + len(word) ** 2
            if score > d[i]:
                d[i] = score
                prev[i] = j

    result = []
    i = n
    while i > 0:
        j = prev[i]
        result.append(line[j:i])
        i = j
    return " ".join(result[::-1])

def main():
    f = open("zad2_output.txt", "w")
    for line in lines:
        f.write(add_whitespaces(line) + "\n")
    f.close()
main()
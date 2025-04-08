from itertools import permutations

# w puzzle sa 3 stringi (nie mniej nie wiecej) i zakładam że wszystkie litery w każdym słowie są duże albo małe
# zeby jak wpisze sie literke T i t nie traktowano ich jako rozne

def kryptarytmy(puzzle, operator):
    word1, word2, result = puzzle[0], puzzle[1], puzzle[2]
    unique_chars = set("".join(puzzle))
    perms = permutations("0123456789",len(unique_chars))
    wyniki = []
    for perm in perms:
        my_dict = dict(zip(unique_chars, list(perm)))
        fst = "".join(my_dict.get(c) for c in word1)
        snd = "".join(my_dict.get(c) for c in word2)
        res = "".join(my_dict.get(c) for c in result)
        if (fst[0] == '0' and len(fst)>1 or snd[0] == '0' and len(snd)>1 or res[0] == '0' and len(res)>1):
            continue
        fst = int(fst)
        snd = int(snd)
        res = int(res)
        if operator == "+":
            if fst + snd == res:
                wyniki.append((fst, snd, res))
        elif operator == "-":
            if fst - snd == res:
                wyniki.append((fst, snd, res))
        elif operator == "*":
            if fst * snd == res:
                wyniki.append((fst, snd, res))
        else:
            if fst / snd == res:
                wyniki.append((fst, snd, res))
    return wyniki

test1 = kryptarytmy(["SEND","MORE","MONEY"],"+")
print("Test1: ")
for i in test1:
    print(i)
print("Liczba rozwiazań: ",len(test1))

test2 = kryptarytmy(["TRZY", "TRZY", "SZEŚĆ"],"+")
print("Test2: ")
for i in test2:
    print(i)
print("Liczba rozwiazań: ",len(test2))

test3 = kryptarytmy(["D","D","P"],"-")
print("Test3: ")
for i in test3:
    print(i)
print("Liczba rozwiazań: ",len(test3))

test4 = kryptarytmy(["KIOTO","OSAKA","TOKIO"],"+")
print("Test4: ")
for i in test4:
    print(i)
print("Liczba rozwiazań: ",len(test4))
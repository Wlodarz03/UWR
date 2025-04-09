def F(n):
    if n % 2 == 0:
        return n / 2
    else:
        return 3 * n + 1

def energia(n):
    A = []
    A.append(n)
    x = F(n)
    while x!=1:
        A.append(int(x))
        x = F(x)
    e = len(A)
    return e

def analiza_collatza(a,b):
    B = []
    for i in range(a, b+1):
        B.append(energia(i))
    B.sort()
    suma = 0
    for element in B:
        suma+=element
    srednia = suma/len(B)
    if len(B)%2 == 1:
        y = (len(B)//2)-1
        y2 = 0
    else:
        y = (len(B)//2)-1
        y2 = (len(B)//2)
    if y2>0:
        mediana = (B[y] + B[y2])//2
    else:
        mediana = B[y]
    min = B[0]
    max = B[len(B)-1]
    print('')
    #print("Energie rosnąco: ",B)
    print("Średnia: ",srednia)
    print("Mediana: ",mediana)
    print("Min: ",min)
    print("Max: ",max)

analiza_collatza(7,25)

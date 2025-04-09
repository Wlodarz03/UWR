import math

def czy_pierwsza(n):
    if n<2:
        return 0
    i = 2  # i - mozliwe dzielniki
    while i <= math.sqrt(n):
        if n%i==0:
            return 0
        i+=1
    return 1

y = set()

for i in range(1007777777,9997777778,10000000):
    if czy_pierwsza(i)==1:
        y.add(i)

for i in range(7777777000,7777778000):
    if czy_pierwsza(i)==1:
        y.add(i)

for i in range(1,10):
    for j in range(777777700,777777800):
        n = i*10**9+j
        if czy_pierwsza(n)==1:
            y.add(n)

for i in range(10,100):
    for j in range(77777770,77777780):
        m = i*10**8+j
        if czy_pierwsza(m)==1:
            y.add(m)

x = len(y)
print("Liczb hiper szczęśliwych w 10-cyfrowych jest: "+ str(x))

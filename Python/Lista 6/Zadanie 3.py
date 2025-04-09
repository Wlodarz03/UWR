import math

def czy_pierwsza(n):
    if n<=2:
        return 1
    i=2
    while i<=math.sqrt(n):
        if n%i == 0:
            return 0
        i+=1
    return 1

def pierw_dzielniki(n):
    A=[]
    for i in range(1,n+1):
        if n%i==0 and czy_pierwsza(i)==1:
            A.append(i)
    return A

n = int(input("Wprowadz liczbe n: "))
print(pierw_dzielniki(n))

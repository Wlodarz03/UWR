import math

def czy_palindrom(n):
    odw = 0
    temp = n
    while n>0:
        x = n%10
        odw = odw*10+x
        n//=10
    if temp==odw:
        return 1
    else:
        return 0

def pierwsza(n): #Algorytm Eratostenesa
    L=[]
    for i in range(2,n+1):
        L.append(i)
    x=min(L)
    while x<math.sqrt(n):
        for element in L:
            if element>x and element%x==0:
                L.remove(element)
        x+=1
    return L

def pierwpal(k,n):
    B = []
    L = pierwsza(n)
    for i in range(len(L)):
        if L[i]>=k and czy_palindrom(L[i])==1:
            B.append(L[i])
    return B

print(pierwpal(100,1100))

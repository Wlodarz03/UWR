wystapienia = [0,0,0,0,0,0,0,0,0,0,0]

def wys(n):
    sk = 0
    while n>0:
        i = n%10
        wystapienia[i]+=1
        n = n // 10
    for i in range(10):
        if wystapienia[i] > 0:
            sk +=1
    return sk

#na dole zadanie 8

def oc(n):
    wystapienia = [0,0,0,0,0,0,0,0,0,0]
    while n>0:
        i = n % 10
        wystapienia[i]+=1
        n = n//10
    return wystapienia

def podobne(n,m):
    x=oc(n)
    y=oc(m)
    o=0
    for i in range(10):
        if x[i]==y[i]:
            o+=1
        else:
            return 0
    if o==10:
        return 1
print(wys(1772))

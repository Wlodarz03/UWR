def czy_pierwsza(n):
    if n==2:
        return 1
    if n%2==0 or n<=1:
        return 0
    for dzielnik in range(3,n):
        if n%dzielnik==0:
            return 0
    return 1

y=0

for i in range(1777,100001):
    napis = str(i)
    x = '777'
    if czy_pierwsza(i)==1 and x in napis:
        print(i)
        y=y+1

print('Szczęśliwych liczb jest ' + str(y))

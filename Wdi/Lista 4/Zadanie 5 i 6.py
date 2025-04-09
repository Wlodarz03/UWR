def palindrom5(n):
    A=[] #odwrocona liczba
    licz=0
    while n>0:
        A.append(n%2)
        n//=2
        licz+=1
    B=[] #normalna liczba
    for i in range(1,licz+1):
        B.append(A[-i])
    x=0
    print(B)
    for i in range(licz//2):
        if A[i]==B[i]:
            x+=1
    if x==licz//2:
        print("Palindrom")
    else:
        print("Nie palindrom")

def palindrom6(n,k):
    A = [] #odwrocona liczba
    licz = 0
    while n > 0:
        A.append(n % k)
        n //= k
        licz += 1
    B = [] #normalna liczba
    for i in range(1, licz + 1):
        B.append(A[-i])
    print(A)
    print(B)
    print(licz)
    x = 0
    for i in range(licz // 2):
        if A[i] == B[i]:
            x += 1
    if x == licz // 2:
        print("Palindrom")
    else:
        print("Nie palindrom")


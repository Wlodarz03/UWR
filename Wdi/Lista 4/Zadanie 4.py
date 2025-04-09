def potega(x, p):
    a=x
    if p==0:
        return 1
    elif p==1:
        return 2
    else:
        for i in range(2, p+1):
            x=x*a
        return x

def p(n,k):
    q=0
    A = []
    for i in range(k):
        a = int(input("Wprowadz a: "))
        j=1
        while j>0:
            if n % potega(a, j)==0:
                j+=1
            else:
                j=j-1
                if j>=q:
                    A.append(a)
                    q=j
                    j=0
                else:
                    j=0
    print("Najwieksza potega p liczby a ktora dzieli n to:",q)
    print("Liczby a o tej potedze to:", A)

p(63000,4)

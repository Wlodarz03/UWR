def nwd(a,b):
    if b>0:
        return nwd(b,a%b)
    return a

def max(n):
    res = 0
    for i in range(n):
        a = int(input("Wprowadz a: "))
        res = nwd(res, a)
    print(res)

max(6)

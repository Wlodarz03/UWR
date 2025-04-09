def nwd(a,b):
    if b>0:
        return nwd(b,a%b)
    return a

def nww(a,b):
    return a*b/nwd(a,b)

def ulamek(a,b):
    licz=a/nwd(a,b)
    mian=b/nwd(a,b)
    print(int(licz))
    print("-")
    print(int(mian))
    print(licz/mian)
ulamek(16,24)

def a(n):
    if n%2==0:
        print(n)
    else:
        print(n*(-1))

def b(n):
    S=0
    x=1
    for i in range(1,n+1):
        x=x*(-1)
        S=S+(x/i)
    print(S)

def c(n,x):
    W=0
    a=x
    for i in range(1,n+1):
        if i==1:
            x=a*1
        else:
            x=x*a
        W=W+(x*i)
    print(W)

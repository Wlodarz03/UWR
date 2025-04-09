from turtle import *

def prostokat(a,b):
    fd(b)
    rt(90)
    fd(a)
    rt(90)
    fd(b)
    rt(90)
    fd(a)

def schody(a,b):
    i=0
    c=b
    while b<=70:
        prostokat(a,b)
        fd(a)
        rt(90)
        b=b+5
        i+=1
    fd(b + 5)
    rt(90)
    fd(a)
    rt(90)
    fd(b + 5)
    lt(90)
    fd(i * a)
    lt(90)
    fd(c)
    lt(90)
def wiatrak(a,b,x): # x - ilosc schodow w wiatraku
    p = 360/x # kąt
    s = 0
    while s!=360:
        schody(a,b)
        rt(p)
        fd(a)
        rt(90)
        s+=p
    done()

speed("fastest")

wiatrak(10,3,10)
input()

from turtle import *
import numpy as np

def kwadrat(bok,kolor):
    lt(90)
    fd(bok)
    rt(90)
    fillcolor(kolor)
    begin_fill()
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()

speed("fastest")
kolor1 = np.array([1,0,1])
kolor2 = np.array([1,1,0])
j=0
while j<15:
    for i in range(15-j):
        alfa = j/15
        mieszanka = (1-alfa) * kolor1 +alfa * kolor2
        kwadrat(20,mieszanka)
    rt(90)
    fd(20)
    rt(180)
    j+=1
done()
input()

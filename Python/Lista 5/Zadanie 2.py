from turtle import *
import math

speed("fastest")

def move(x,y):
    penup()
    goto(x,y)
    pendown()

def kwadrat(bok):
    for i in range(4):
        fd(bok)
        rt(90)

def wieza(bok):
    for i in range(5):
        kwadrat(bok-10*i)
        fd(bok-10*i)
        rt(90)
        fd(5)
        lt(90)

def figura(bok):
    for i in range(6):
        if i==0:
            x=0
            y=-bok
        if i==1:
            x=-math.sqrt(3)*bok/2
            y=-1.5*bok
        if i==2:
            x=-math.sqrt(3)*bok
            y=-bok
        if i==3:
            x=-math.sqrt(3)*bok
            y=0
        if i==4:
            x=-math.sqrt(3)*bok/2
            y=0.5*bok
        if i==5:
            x=0
            y=0
        wieza(bok)
        move(x,y)
        rt(60)

    done()

figura(50)
input()

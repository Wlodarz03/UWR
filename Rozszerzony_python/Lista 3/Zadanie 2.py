from collections import deque

def prio(operator):
    if operator == "+" or operator == "-":
        return 1
    elif operator == "*" or operator == "/":
        return 2
    else:
        return 0

def konwersja(infiksowe):
    onp = []
    stos = deque()
    for i in infiksowe:
        if isinstance(i, int):
            onp.append(i)
        elif i == "(":
            stos.append(i)
        elif i == ")":
            while stos and stos[-1] != "(":
                onp.append(stos.pop())
            stos.pop()
        else:
            while stos and stos[-1] != '(' and prio(stos[-1])>=prio(i):
                onp.append(stos.pop())
            stos.append(i)
    while stos:
        onp.append(stos.pop())
    return onp

def oblicz(onp):
    stos = deque()
    for i in onp:
        if isinstance(i,int):
            stos.append(i)
        else:
            a=stos.pop()
            b=stos.pop()
            if i == "+":
                stos.append(a+b)
            elif i == "-":
                stos.append(b-a)
            elif i == "*":
                stos.append(a*b)
            elif i == "/":
                stos.append(b/a)
    return stos.pop()

test = ['(', 2, '+', 3, ')', '*', 4]
test2 = [2,'+',2,'*',2]
print(konwersja(test2))
print(oblicz(konwersja(test2)))




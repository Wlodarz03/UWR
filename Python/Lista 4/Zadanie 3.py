import random
def randperm(n):
    og = []
    new = []
    for i in range(n+1):
        og.append(i)
    while len(new)!=n+1:
        x = random.choice(og)
        new.append(x)
        og.remove(x)
    print(new)
for i in range(10):
    randperm(9)

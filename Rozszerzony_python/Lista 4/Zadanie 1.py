import timeit

#imperatywnie
def pierwsze_imperatywna(n):
    primes = []
    if n < 2:
        return primes
    else:
        primes.append(2)
        for i in range(3, n):
            isprime = True
            for j in range(2, int(i**0.5 + 1)):
                if i % j == 0:
                    isprime = False
                    break
            if isprime:
                primes.append(i)
        return primes

#listy składane
def pierwsze_skladana(n):
    return [x for x in range(2, n) if all(x % y for y in range(2, int((x**0.5) + 1)))]

#funkcyjnie
def pierwsze_funkcyjna(n):
    return list(filter(lambda x: all(x % i for i in range(2, int((x**0.5)+1))) if x >= 2 else False, [x for x in range(n)]))

print(" n  skladana   imperatywna    funkcyjna")
for n in range(10, 100, 10):
    czas_skladana = timeit.timeit("pierwsze_skladana(n)", globals=globals() , number=1000)
    czas_imperatywna = timeit.timeit("pierwsze_imperatywna(n)", globals=globals(), number=1000)
    czas_funkcyjna = timeit.timeit("pierwsze_funkcyjna(n)", globals=globals(), number=1000)

    print(f"{n:2}  {czas_skladana:.4f}     {czas_imperatywna:.4f}         {czas_funkcyjna:.4f}")

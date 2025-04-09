def kwad1(n):
    print(' 1', n * '* ')
    for i in range(n - 2):
        if i<8:
            print('',i+2,(i + 1) * '* ' + (n - i - 2) * '  ' + '*')
        else:
            print(i + 2, (i + 1) * '* ' + (n - i - 2) * '  ' + '*')
    print(n, n * '* ')
kwad1(10)

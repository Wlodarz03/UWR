
znaki_zakazane = [" ","_",".",",","?","!",":",";","-","...","(",")"] #założenie że to wszystkie znaki przestankowe + spacja, ewentualnie można dodać

def is_palindrom(s):
    s1 = ''.join(ch for ch in s if ch not in znaki_zakazane)
    slowo1 = s1.lower()
    slowo2 = slowo1[::-1]
    return slowo1 == slowo2

print(is_palindrom("Kobyła")) #False
print(is_palindrom("Kobyła ma mały bok."))
print(is_palindrom("Kobyła, ma - mały bok ?"))
print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrom("Míč omočím."))
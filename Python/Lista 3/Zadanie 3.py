import re

def usun_w_nawiasach(n):
    n = re.sub("\(.*\)", "", n)
    print(n)

usun_w_nawiasach("Ala ma (kota perskiego)!")

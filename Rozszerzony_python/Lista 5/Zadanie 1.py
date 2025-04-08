class Wyrazenie:
    def oblicz(self, zmienne):
        pass

    def __str__(self):
        pass

    def __add__(self, other):
        return Dodaj(self, other)

    def __mul__(self, other):
        return Razy(self, other)

    def uproszczenie(self):
        return self

class Zmienna(Wyrazenie):
    def __init__(self, nazwa):
        self.nazwa = nazwa

    def oblicz(self, zmienne):
        if self.nazwa in zmienne:
            return zmienne[self.nazwa]
        else:
            raise VariableNotFound(self.nazwa)

    def __str__(self):
        return self.nazwa

class Stala(Wyrazenie):
    def __init__(self, wart):
        self.wart = wart

    def oblicz(self, zmienne):
        return self.wart

    def __str__(self):
        return str(self.wart)

class Dodaj(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        if (not isinstance(self.wyr1, Wyrazenie) or self.wyr1 is None):
            raise InvalidWyrazenie(self.wyr1)
        if (not isinstance(self.wyr2, Wyrazenie)) or (self.wyr2 is None):
            raise InvalidWyrazenie(self.wyr2)
        else:
            return self.wyr1.oblicz(zmienne) + self.wyr2.oblicz(zmienne)

    def __str__(self):
        return f"({self.wyr1} + {self.wyr2})"

    # B - reguły upraszczajace
    def uproszczenie(self):
        uproszczone_wyr1 = self.wyr1.uproszczenie()
        uproszczone_wyr2 = self.wyr2.uproszczenie()

        # 0+x = x
        if isinstance(uproszczone_wyr1, Stala) and uproszczone_wyr1.wart == 0:
            return uproszczone_wyr2

        # x+0 = x
        if isinstance(uproszczone_wyr2, Stala) and uproszczone_wyr2.wart == 0:
            return uproszczone_wyr1

        # stala + stala = stala
        if isinstance(uproszczone_wyr1, Stala) and isinstance(uproszczone_wyr2, Stala):
            return Stala(uproszczone_wyr1.wart + uproszczone_wyr2.wart)
        else:
            return Dodaj(uproszczone_wyr1, uproszczone_wyr2)

class Razy(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        if (not isinstance(self.wyr1, Wyrazenie) or self.wyr1 is None):
            raise InvalidWyrazenie(self.wyr1)
        if (not isinstance(self.wyr2, Wyrazenie)) or (self.wyr2 is None):
            raise InvalidWyrazenie(self.wyr2)
        else:
            return self.wyr1.oblicz(zmienne) * self.wyr2.oblicz(zmienne)

    def __str__(self):
        return f"({self.wyr1} * {self.wyr2})"

    # B - reguły upraszczajace
    def uproszczenie(self):

        uproszczone_wyr1 = self.wyr1.uproszczenie()
        uproszczone_wyr2 = self.wyr2.uproszczenie()

        # 0 * x = 0
        if isinstance(uproszczone_wyr1, Stala) and uproszczone_wyr1.wart == 0:
            return uproszczone_wyr1
        # x * 0 = 0
        if isinstance(uproszczone_wyr2, Stala) and uproszczone_wyr2.wart == 0:
            return uproszczone_wyr2

        # 1 * x = x
        if isinstance(uproszczone_wyr1, Stala) and uproszczone_wyr1.wart == 1:
            return uproszczone_wyr2
        # x * 1 = x
        if isinstance(uproszczone_wyr2, Stala) and uproszczone_wyr2.wart == 1:
            return uproszczone_wyr1

        # stala * stala = stala
        if isinstance(uproszczone_wyr1, Stala) and isinstance(uproszczone_wyr2, Stala):
            return Stala(uproszczone_wyr1.wart * uproszczone_wyr2.wart)

        else:
            return Razy(uproszczone_wyr1, uproszczone_wyr2)

class Odejmij(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        if (not isinstance(self.wyr1, Wyrazenie) or self.wyr1 is None):
            raise InvalidWyrazenie(self.wyr1)
        if (not isinstance(self.wyr2, Wyrazenie)) or (self.wyr2 is None):
            raise InvalidWyrazenie(self.wyr2)
        else:
            return self.wyr1.oblicz(zmienne) - self.wyr2.oblicz(zmienne)

    def __str__(self):
        return f"({self.wyr1} - {self.wyr2})"

class Podzielic(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        if (not isinstance(self.wyr1, Wyrazenie) or self.wyr1 is None):
            raise InvalidWyrazenie(self.wyr1)
        if (not isinstance(self.wyr2, Wyrazenie)) or (self.wyr2 is None):
            raise InvalidWyrazenie(self.wyr2)
        else:
            if self.wyr2.oblicz(zmienne) == 0:
                raise DzieleniePrzezZero()
            else:
                return self.wyr1.oblicz(zmienne) / self.wyr2.oblicz(zmienne)

    def __str__(self):
        return f"({self.wyr1} / {self.wyr2})"

#bledy
class WyrazenieException(Exception):
    def __str__(self):
        return str(self.args[0])

class DzieleniePrzezZero(WyrazenieException):
    def __init__(self):
        super().__init__("Dzielenie przez zero jest niedozwolone")

class VariableNotFound(WyrazenieException):
    def __init__(self, zmienna):
        self.zmienna = zmienna
        super().__init__(f"Zmiennej {zmienna} nie ma w zmiennych")

class InvalidWyrazenie(WyrazenieException):
    def __init__(self, wyr):
        self.wyr = wyr
        super().__init__(f"Niewlasciwe wyrazenie: {wyr}")

#Testy
zmienne = {"x": 5, "y": 3}

wyrazenie_dodawania = Dodaj(Zmienna("x"), Stala(2))
wyrazenie_razy = Razy(Zmienna("x"), Stala(2))
wyrazenie_dzielenie_przez_zero = Podzielic(Zmienna("x"), Stala(0))
wyrazenie_zle_wyrazenie = Razy(Zmienna("y"), 2)
wyrazenie_zla_zmienna = Razy(Zmienna("y"), Zmienna("z"))

wyrazenie_do_uproszczenia1 = Dodaj(Dodaj(Stala(2),Stala(2)), Zmienna("x"))
wyrazenie_do_uproszczenia2 = Dodaj(Razy(Stala(0), Zmienna("x")), Stala(2))

uproszczone1 = wyrazenie_do_uproszczenia1.uproszczenie()
uproszczone2 = wyrazenie_do_uproszczenia2.uproszczenie()


wyrazenie_dodania_dodawania_i_razy = wyrazenie_dodawania.__add__(wyrazenie_razy)
wyrazenie_iloczynu_dodawania_i_razy = wyrazenie_dodawania.__mul__(wyrazenie_razy)

try:
    wynik = wyrazenie_dodawania.oblicz(zmienne)
    print(wynik)
except WyrazenieException as e:
    print(f"Błąd: {e}")

try:
    wynik = wyrazenie_razy.oblicz(zmienne)
    print(wynik)
except WyrazenieException as e:
    print(f"Błąd: {e}")

try:
    wynik = wyrazenie_dzielenie_przez_zero.oblicz(zmienne)
    print(wynik)
except WyrazenieException as e:
    print(f"Błąd: {e}")

try:
    wynik = wyrazenie_zle_wyrazenie.oblicz(zmienne)
    print(wynik)
except WyrazenieException as e:
    print(f"Błąd: {e}")

try:
    wynik = wyrazenie_zla_zmienna.oblicz(zmienne)
    print(wynik)
except WyrazenieException as e:
    print(f"Błąd: {e}")

print(wyrazenie_dodania_dodawania_i_razy.__str__())
try:
    wynik = wyrazenie_dodania_dodawania_i_razy.oblicz(zmienne)
    print(wynik)
except WyrazenieException as e:
    print(f"Błąd: {e}")

print(wyrazenie_iloczynu_dodawania_i_razy.__str__())
try:
    wynik = wyrazenie_iloczynu_dodawania_i_razy.oblicz(zmienne)
    print(wynik)
except WyrazenieException as e:
    print(f"Błąd: {e}")

print(uproszczone1.__str__())
print(uproszczone2.__str__())
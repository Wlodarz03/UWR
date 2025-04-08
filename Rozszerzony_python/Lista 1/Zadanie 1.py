from decimal import Decimal

def vat_faktura(lista):
    suma = sum(lista)
    return (0.23*suma)

def vat_kasa(lista):
    suma=0
    for i in lista:
        suma+=0.23*i
    return suma

zakupy = [100.0,50.0,10.0] #przykład dla którego bedzie False

print(vat_faktura(zakupy) == vat_kasa(zakupy)) #False


#eksperyment
zakupy_decimal =[Decimal('100.0'),Decimal('50.0'),Decimal('10.0')]

def vat_faktura_decimal(lista):
    suma = sum(lista)
    return (Decimal('0.23')*suma)

def vat_kasa_decimal(lista):
    suma=Decimal('0')
    for i in lista:
        suma+=Decimal('0.23')*i
    return suma

print(vat_faktura_decimal(zakupy_decimal) == vat_kasa_decimal(zakupy_decimal)) #True


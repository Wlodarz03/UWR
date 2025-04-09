//a)
const p1 = {
    essa: 'essa',
    baza: 'baza'
}
console.log(p1.essa)
console.log(p1['essa'])
// operator . nie moze byc uzyty gdy nazwa wlasciwosci ma spacje lub zaczyna sie cyfra
// operator [] pozwala na uzycie zmiennych jako nazwy wlasciwosci


//b)
const p2 = {
    0: 'zero',
    1: 'one',
    2: 'two'
}

console.log(p2[1]) //dziala
console.log(p2['1']) //dziala

const p3 = {
    ok: 'essa'
}

const key = {
    prop: 'ok'
}

p3[key] = 5
console.log(p3[key])
console.log(p3)

// w obu przypadkach pelna kontrola nad kluczem pod ktorym zostanie zapisana wartosc

//c)
const tablica = ["haha","hello","weppo"]
console.log(tablica["1"])

const ob = {
    a: "1"
}
console.log(tablica[ob.a])

const tablica2 = ["haha","hello","weppo"]
tablica2["3"] = "matma"
console.log(tablica2)
//element zostanie dodany do tablicy

const tablica3 = ["haha","hello","weppo"]
console.log(tablica3.length)

tablica3.length = 10
console.log(tablica3)
// tablica zostanie zwiekszona do tej dlugosci pustymi elementami (undefined)

tablica3.length = 2
console.log(tablica3)
//tablica zostanie skrocona do tej dlugosci

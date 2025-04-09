//typeof sprawdza typ zmiennej i zwraca stringa z informacja o typie
console.log(typeof(5)) //->"number"
console.log(typeof("hello")) //->"string"
console.log(typeof(null)) //->"object" blad

//instanceof sprawdza czy zmienna jest instacja danej klasy i zwraca boolean

var x = ["weppo","hello"]
console.log(x instanceof Array) //->true
console.log(x instanceof Object) //->true
console.log(x instanceof String) //->false
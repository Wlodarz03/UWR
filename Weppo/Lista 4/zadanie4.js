var n = 1;

console.log( typeof Object.getPrototypeOf( n ) );

n.foo = "foo"
console.log( n.foo );

console.log(n.toFixed(1))

// Prototypem liczby jest object
// nie mozna zapisac do liczby pola
// ale mozna wywolac na wartosciach metody typu
// zatem wystepuje niejawna konwersja na obiekt
Worker.prototype = Person.prototype
// zmiany w prototypie Worker wplyna na prototyp Person

Wroker.prototype = new Person()
// tworzymy nowa instancje Person i przypisujemy jako prototyp Worker
// Zmiany w prototypie Worker moga wplynac na Person

Worker.prototype = Object.create(Person.prototype)
// tworzymy nowy obiekt prototypu dla Worker, ktory dziedziczy od
// prototypu Person bez modyfikacji prototypu Person
// Zmiany w prototypie Person nie wplyna na Worker
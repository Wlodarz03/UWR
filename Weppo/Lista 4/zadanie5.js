function Foo() {
    var privateVar = 'ok';
    this.Bar = function () {
        console.log('Bar done');
        Qux();
    };
    function Qux() {
        console.log(privateVar);
    }
}

var obiekt = new Foo()

obiekt.Bar()

//obiekt.Qux() to nie dziala
function getLastProto(o) {
    var p = o
    do {
        o = p
        p = Object.getPrototypeOf(o)
    } while (p)
    return o
}

var o = {
    foo: null
}

var p = {
    name : 'jan',
    say : function() {
        return this.name
    }
};

var proto = {
    foo1: 1,
    bar: 2
}

//obiekty dziedzicza Object a jego prototypem jest null

prototyp1 = getLastProto(o)
prototyp2 = getLastProto(p)
prototyp3 = getLastProto(proto)

console.log(prototyp1)
console.log(prototyp2)
console.log(prototyp3)

console.log(prototyp1 === prototyp2  && prototyp2 === prototyp3)

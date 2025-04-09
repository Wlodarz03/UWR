function isOwn(obj, prop) {
    return obj.hasOwnProperty(prop)
}

var p = {
    name: 'jan'
}

var q = {
    surname: 'kowalski'
}

Object.setPrototypeOf( p, q );

console.log( p.name );
console.log( p.surname );

console.log( isOwn(p, 'name') );
console.log( isOwn(p, 'surname') );

console.log("\nPola/funkcje w obiekcie p: ")
for (var key in p){
    if(isOwn(p, key))
        console.log(key)
}

console.log("\nPola/funkcje w obiekcie i prototypach p: ")
for (var key in p){
    if(isOwn(p, key))
        console.log(key)

    var prototype = Object.getPrototypeOf(p)
    while (prototype) {
        if (isOwn(prototype, key)) {
            console.log(key);
        }
        prototype = Object.getPrototypeOf(prototype)
    }
}
//Object.keys klucze samego obiektu
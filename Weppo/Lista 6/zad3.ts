function forEach<T>(a: T[], f: (t: T) => void): void{
    for(let i = 0; i < a.length; i++){
        f(a[i])
    }
}


function map<T,U>( a: T[], f: (x: T) => U ): U[] {
    const newtab = []
    for (let i = 0; i < a.length; i++ ) {
        newtab.push(f(a[i]))
    }
    return newtab;
}


function filter<T>( a: T[], f: (x: T) => boolean): T[] {
    const newtab = []
    for(let i = 0; i < a.length; i++){
        if (f(a[i])){
            newtab.push(a[i])
        }
    }
    return newtab;
}

var tab = [1,2,3,4]

forEach(tab, _ => {console.log( _ )})

console.log(filter(tab, _ => _ < 3))

console.log(map(tab, _ => _ * 2))
function forEach(a, f){
    for(let i = 0; i < a.length; i++){
        f(a[i])
    }
}

function map(a , f){
    const newtab = []
    for(let i = 0; i<a.length; i++){
        newtab.push(f(a[i]))
    }
    return newtab;
}

function filter(a, f){
    const newtab = []
    for(let i = 0; i<a.length; i++){
        if (f(a[i])){
            newtab.push(a[i])
        }
    }
    return newtab
}

var a = [1,2,3,4]

forEach(a, _ => {console.log( _ );})

console.log(filter(a, _ => _ < 3))

console.log(map(a, _ => _ * 2))
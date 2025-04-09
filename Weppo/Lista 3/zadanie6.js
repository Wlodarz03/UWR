function fib(){
    var a = 0
    var b = 1
    return {
        next : function(){
            var temp = b
            b = a + temp
            a = temp
            return{
                value: a,
                done: false
            }
        }
    }
}

function *fib() {
    var a = 0
    var b = 1
    while(true){
        yield a
        var tmp = b
        b = a + b
        a = tmp
    }    
}

var _it = fib();

for ( var _result; _result = _it.next(), !_result.done; ){
    console.log( _result.value );
}


//zad7

function* take(it, top) {
    for(let i = 0; i < top; i++){
        var {value, done} = it.next()
        yield value
        if(done)
            break
    }
}

// "nieskończonego" iteratora/generatora
// zwróć dokładnie 10 wartości z potencjalnie

for (let num of take( fib(), 10 ) ) {
    console.log(num);
}
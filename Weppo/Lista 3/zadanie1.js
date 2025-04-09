function fib(n){
    if (n == 0){
        return 0
    }
    if (n == 1){
        return 1
    }
    else{
        return fib(n-1)+fib(n-2)
    }
}

function memoize(fn){

    var cache = {};
    
    return function(n){
        if (n in cache){
            return cache[n]
        }
        else{
            var result = fn(n)
            cache[n] = result
            return result
        }
    }
}
fib = memoize(fib)

console.time("memofib")
fib(43)
console.timeEnd("memofib")

// console.time("memofib")
// fib(43)
// console.timeEnd("memofib")

// console.time("fib")
// fib(43)
// console.timeEnd("fib")
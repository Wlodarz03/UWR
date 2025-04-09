function fib_recur(n){
    if (n==0){
        return 0;
    }
    if (n==1){
        return 1;
    }
    else{
        return fib_recur(n-1)+fib_recur(n-2);
    }
}

function fib_iter(n){
    if (n==0){
        return 0;
    }
    else{
        var x = 0;
        var y = 1;
        for (let i=1;i<n;i++){
            var z = x+y;
            x = y;
            y = z;
        }
        return y
    }
}

const n_values = []
for (let n = 10; n<=45;n+=5){
    n_values.push(n)
}

console.log("ITERACJA")
for (const n of n_values){
    console.time(`n=${n}`)
    fib_iter(n)
    console.timeEnd(`n=${n}`)
}
console.log("REKURENCJA")
for (const n of n_values){
    console.time(`n=${n}`)
    fib_recur(n)
    console.timeEnd(`n=${n}`)
}
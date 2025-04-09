function createGenerator(n) {
    return function(){
        var _state = 0;
        return {
            next : function() {
                return {
                    value : _state,
                    done : _state++ >= n
                }
            }
        }
    }
}

var foo1 = {
    [Symbol.iterator]: createGenerator(7)
}

var foo2 = {
    [Symbol.iterator]: createGenerator(3)
}

for (var f of foo1){
    console.log(f)
}

console.log("-")

for (var f of foo2){
    console.log(f)
}
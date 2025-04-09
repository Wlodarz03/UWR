//a)

function createFs(n){
    var fs = []
    for (let i = 0; i<n; i++){
        fs[i] = function(){
            return i
        }
    }
    return fs;
}

var myFs = createFs(10)

console.log(myFs[0]())
console.log(myFs[2]())
console.log(myFs[7]())

//b)
function createFs2(n) { 
    var fs = []
    for ( var i=0; i<n; i++ ) {
        fs[i] =
            (function (j) {
                return function () {
                    return j;
            }
        })(i);
    }
    return fs;
}
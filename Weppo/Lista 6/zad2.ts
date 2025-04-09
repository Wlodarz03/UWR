///poprzedni fibonacci

function FibRec(n: number): number {
	if (n < 2) {
		return n;
	}
	return FibRec(n - 1) + FibRec(n - 2);
}


///fibonacci z memoizacja

///z wykładu:
function memoize(fn: Function): Function {
    var cache: { [key: number]: any} = {};
    return function (n: number) {
        if (n in cache) {
            return cache[n]
        }
        else {
                var result = fn(n);
                cache[n] = result;
                return result;
        }
    }
}

const FibMemo = memoize(FibRec);

console.time("FibMemo");
const recResult = FibMemo(25);
console.timeEnd("FibMemo");
console.log(recResult);


console.time("FibMemo");
const recResult2 = FibMemo(25);
console.timeEnd("FibMemo");
console.log(recResult2);
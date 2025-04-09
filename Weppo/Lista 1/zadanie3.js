function isprime(n){
    for (let i = 2; i<n;i++){
        if (n%i==0){
            return false;
        }
    }
    return true;
}

function prime_zbior(){
    const zbior = [];
    for (let i = 2; i<=100000;i++){
        if (isprime(i)){
            zbior.push(i);
        }
    }
    return zbior;
}

var wynik = prime_zbior();
var dlugosc = wynik.length;
console.log("Ilosc liczb pierwszych w zbiorze: ",dlugosc);
console.log(wynik);


// for (const n of wynik){
//     console.log(n);
// }
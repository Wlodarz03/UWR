function czy_podzielne(n){
    const cyfry = Array.from(String(n),Number);
    var sum = 0;
    for (let i = 0; i<cyfry.length;i++){
        sum+=cyfry[i];
    }
    for (let i = 0; i<cyfry.length;i++){
        if (cyfry[i]==0){
            return false;
        }
        else{
            if (n%cyfry[i] != 0){
                return false;
            }
        }
    }
    if (n%sum !=0){
        return false;
    }
    else{
        return true;
    }
}

function wyznacz_zbior(){
    const zbior = [];
    for (let numer = 1; numer <=100000;numer++){
        if (czy_podzielne(numer)){
            zbior.push(numer);
        }
    }
    return zbior;
}

const wynik = wyznacz_zbior();
// for (const n of wynik){
//     console.log(n);
// }
console.log("Ile takich jest: ",wynik.length)
console.log("Liczby spelniajace warunek: ",wynik)
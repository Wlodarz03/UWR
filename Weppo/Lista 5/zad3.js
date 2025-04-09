const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const wylosowanaLiczba = Math.floor(Math.random() * 101);

function graj() {
    rl.question("Sprobuj zgadnac liczbe: ", (odpowiedz) =>{
        const liczba = parseInt(odpowiedz);

        if (liczba == wylosowanaLiczba){
            console.log("Gratulacje zgadles liczbe");
            rl.close();
        }
        else if (liczba < wylosowanaLiczba){
            console.log("Moja liczba jest wieksza");
            graj();
        }
        else{
            console.log("Moja liczba jest mniejsza");
            graj();
        }
    });
}

graj();

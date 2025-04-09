const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.question('Podaj swoje imię: ', (imie) => {
  console.log(`Witaj, ${imie}!`);
  rl.close();
});
var fs = require('fs')

const path = "./zad7.txt"


//standardowe z callback

fs.readFile(path, 'utf-8', function (err, data) {
    if(err) {
        console.error(`Error: ${err}`)
    }
    else  {
        console.log(`Data: ${data}`)
    }
})

//recznie ze zwracaniem promise

function fspromise( path, enc ) {
    return new Promise( function (res, rej) {
        fs.readFile( path, enc, function (err, data) {
            if ( err )
                rej(err);
            res(data);
        });
    });
}

fspromise(path, 'utf-8')
    .then(data => {
        console.log(`Data: ${data}`)
    })
    .catch(err => {
        console.log(`Error: ${err}`)
    });

//util.promisify
const util = require('util')
const utilreader = util.promisify(fs.readFile)

utilreader(path, 'utf-8')
    .then(data => {
        console.log(`Data: ${data}`)
    })
    .catch(err => {
        console.log(`Error: ${err}`)
    }); 

//fs.promises
async function dataReadpromisify(){
    try {
        var dat = await fs.promises.readFile(path, 'utf-8')

        console.log(`Data: ${dat}`)
    }
    catch (err) {
        console.log(`Error: ${err}`)
    }
}

dataReadpromisify()
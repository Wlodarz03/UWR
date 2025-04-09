var express = require('express')
var app = express()
var http = require ('http');

app.set('view engine', 'ejs')
app.set('views', './views')

app.use(express.urlencoded({ extended: true}))

function val(x) {
    if (x == '')
        return 0;
    else
        return x;
}

app.get('/', (req, res) => {
    res.render('index',{name: '', surname: '', subject: '', z1: '', z2: '', z3: '', z4: '', z5: '', z6: '', z7: '', z8: '', z9: '', z10: ''})
})

app.post('/', (req, res) => {
    if(req.body.name && req.body.surname && req.body.subject) {
        res.redirect(`/print?name=${req.body.name}&surname=${req.body.surname}&subject=${req.body.subject}&z1=${val(req.body.z1)}&z2=${val(req.body.z2)}&z3=${val(req.body.z3)}&z4=${val(req.body.z4)}&z5=${val(req.body.z5)}&z6=${val(req.body.z6)}&z7=${val(req.body.z7)}&z8=${val(req.body.z8)}&z9=${val(req.body.z9)}&z10=${val(req.body.z10)}`);
    }
    else{
        res.render('index', {
            name: req.body.name,
            surname: req.body.surname,
            subject: req.body.subject,
            z1: req.body.z1,
            z2: req.body.z2,
            z3: req.body.z3,
            z4: req.body.z4,
            z5: req.body.z5,
            z6: req.body.z6,
            z7: req.body.z7,
            z8: req.body.z8,
            z9: req.body.z9,
            z10: req.body.z10,
            message : 'Nalezy podac poprawne dane'});
    }
})

app.get('/print', (req, res) => {
    var name = req.query.name;
    var surname = req.query.surname;
    var subject = req.query.subject;
    var z1 = req.query.z1;
    var z2 = req.query.z2;
    var z3 = req.query.z3;
    var z4 = req.query.z4;
    var z5 = req.query.z5;
    var z6 = req.query.z6;
    var z7 = req.query.z7;
    var z8 = req.query.z8;
    var z9 = req.query.z9;
    var z10 = req.query.z10;

    res.render('print', {name, surname, subject, z1, z2, z3, z4, z5, z6, z7, z8, z9, z10});
}) 

http.createServer(app).listen(3000);
console.log('started on http://localhost:3000')
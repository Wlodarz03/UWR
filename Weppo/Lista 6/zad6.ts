//skorygowanie definicji typów User i Admin tak, 
//aby zawierały dodatkowe pole type (typ: 'user' | 'admin')
//? oznacza, że pole jest opcjonalne

export type User = {
    typ: 'user' //zmiana
    name: string;
    age: number;
    occupation: string; //zmiana
}

//zmiana
export type Admin = {
    typ: 'admin'; //zmiana
    name: string;
    age: number;
    role: string; //zmiana
}

export type Person = User | Admin;

export const persons: Person[] = [ 
    {
        typ: 'user', //zmiana
        name: "Jan Kowalski",
        age: 17,
        occupation: "Student"
    },
    {
        typ: 'admin',//zmiana
        name: "Tomasz Malinowski",
        age: 20,
        role: "Administrator"
    }
];


//skorygowane definicje funkcji logPerson, isAdmin i isUser
//dodanie strażnika typów 
export function isAdmin(person: Person): person is Admin {
    return person.typ === 'admin';
}

export function isUser(person: Person): person is User {
    return person.typ === 'user';
}


function logPerson(person: Person) {
    let additionalInformation: string = '';
    if (isAdmin(person)) {
        additionalInformation = person.role;
    }
    if (isUser(person)) {
        additionalInformation = person.occupation;
    }
    console.log(` - ${person.name}, ${person.age}, ${additionalInformation}`);
}
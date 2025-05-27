// Wyzwanie 1 do poprawy
// console.log(capitalize("alice"));

// const capitalize = (str) => {
//   return str.charAt(0).toUpperCase() + str.slice(1);
// };

// Wersja poprawiona - zamiana funkcji strzałkowej na function
console.log(capitalize("alice"));

function capitalize(str) {
  return str.charAt(0).toUpperCase() + str.slice(1);
}

// Deklaracje funkcji są przenoszone na początek swojego zakresu (hoisting), więc można ich używać przed definicją

// Wyzwanie 2

function capitalizeSentence(sentence) {
    return sentence
      .split(" ")
      .map(capitalize)
      .join(" ");
}

// Weryfikacja
console.log(capitalizeSentence("alice"));
console.log(capitalizeSentence("alice in wonderland"));

// Wyzwanie 3

const ids = [];

const generateId = () => {
  let id = 0;

  do {
    id++;
  } while (ids.includes(id));

  ids.push(id);
  return id;
};

// Nowa wersja
const ids2 = new Set();

const generateId2 = () => {
  let id = 0;

  do {
    id++;
  } while (ids2.has(id));

  ids2.add(id);
  return id;
};

console.time("generateId");

for (let i = 0; i < 3000; i++) {
  generateId();
}

console.timeEnd("generateId");

console.time("generateId2")

for (let i = 0; i < 3000; i++) {
    generateId2();
  }

console.timeEnd("generateId2")

// Wyzwanie 4

function compareObjects(obj1, obj2) {
    if (typeof obj1 !== "object" || obj1 === null ||
        typeof obj2 !== "object" || obj2 === null) {
      return obj1 === obj2;
    }
  
    const keys1 = Object.keys(obj1);
    const keys2 = Object.keys(obj2);
  
    if (keys1.length !== keys2.length) {
      return false;
    }
  
    for (const key of keys1) {
      if (!obj2.hasOwnProperty(key)) {
        return false;
      }
  
      if (!compareObjects(obj1[key], obj2[key])) {
        return false;
      }
    }
  
    return true;
}

const obj1 = {
  name: "Alice",
  age: 25,
  address: {
    city: "Wonderland",
    country: "Fantasy",
  },
};

const obj2 = {
  name: "Alice",
  age: 25,
  address: {
    city: "Wonderland",
    country: "Fantasy",
  },
};

const obj3 = {
  age: 25,
  address: {
    city: "Wonderland",
    country: "Fantasy",
  },
  name: "Alice",
};

const obj4 = {
  name: "Alice",
  age: 25,
  address: {
    city: "Not Wonderland",
    country: "Fantasy",
  },
};

const obj5 = {
  name: "Alice",
};

console.log("Should be True:", compareObjects(obj1, obj2));
console.log("Should be True:", compareObjects(obj1, obj3));
console.log("Should be False:", compareObjects(obj1, obj4));
console.log("Should be True:", compareObjects(obj2, obj3));
console.log("Should be False:", compareObjects(obj2, obj4));
console.log("Should be False:", compareObjects(obj3, obj4));
console.log("Should be False:", compareObjects(obj1, obj5));
console.log("Should be False:", compareObjects(obj5, obj1));

// Wyzwanie 5
let library = [];

const addBookToLibrary = (title, author, pages, isAvailable, ratings) => {
  if (typeof title !== "string" || title.trim() === "") {
    throw new Error("Title powinien być niepustym napisem");
  }

  if (typeof author !== "string" || author.trim() === "") {
    throw new Error("Author powinien być niepustym napisem");
  }

  if (typeof pages !== "number" || pages <= 0 || !Number.isFinite(pages)) {
    throw new Error("Pages powinna być dodatnią liczbą");
  }

  if (typeof isAvailable !== "boolean") {
    throw new Error("isAvailable powinno być wartością typu boolean");
  }

  if (!Array.isArray(ratings)) {
    throw new Error("Ratings jest tablicą");
  }

  for (const rating of ratings) {
    if (typeof rating !== "number" || rating < 0 || rating > 5) {
      throw new Error("Każdy rating ma być liczbą pomiędzy 0 a 5");
    }
  }

  library.push({
    title,
    author,
    pages,
    available: isAvailable,
    ratings,
  });
};

addBookToLibrary("The Hobbit", "J.R.R. Tolkien", 310, true, [5, 4.5, 4.8]); // OK
addBookToLibrary("Dune", "Frank Herbert", 412, false, []); // OK
//addBookToLibrary("", "Author", 100, true, []); // błąd

// Wyzwanie 6

function testAddingBooks(testCases) {
    for (const { testCase, shouldFail } of testCases) {
      try {
        addBookToLibrary(...testCase);
        if (shouldFail) {
          console.log("Test failed (powinien być wyjątek): ", testCase);
        } else {
          console.log("Test passed (nie ma błędu): ", testCase);
        }
      } catch (error) {
        if (shouldFail) {
          console.log("Test passed (wyłapało wyjątek): ", testCase);
          console.log("Error: ", error.message);
        } else {
          console.log("Test failed (nie powinno wyłapywać wyjątku): ", testCase);
          console.log("Error: ", error.message);
        }
      }
    }
}

const testCases = [
    { testCase: ["", "Author", 200, true, []], shouldFail: true },
    { testCase: ["Title", "", 200, true, []], shouldFail: true },
    { testCase: ["Title", "Author", -1, true, []], shouldFail: true },
    { testCase: ["Title", "Author", 200, "yes", []], shouldFail: true },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3, 6]], shouldFail: true },
    {
      testCase: ["Title", "Author", 200, true, [1, 2, 3, "yes"]],
      shouldFail: true,
    },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3, {}]], shouldFail: true },
    { testCase: ["Title", "Author", 200, true, []], shouldFail: false },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3]], shouldFail: false },
    { testCase: ["Title", "Author", 200, true, [1, 2, 3, 4]], shouldFail: false },
    {
      testCase: ["Title", "Author", 200, true, [1, 2, 3, 4, 5]],
      shouldFail: false,
    },
    {
      testCase: ["Title", "Author", 200, true, [1, 2, 3, 4, 5]],
      shouldFail: false,
    },
];

testAddingBooks(testCases)

// Wyzwanie 7
const addBooksToLibrary = (booksArray) => {
    for (const bookArgs of booksArray) {
      addBookToLibrary(...bookArgs);
    }
};

const books = [
    ["Alice in Wonderland", "Lewis Carroll", 200, true, [1, 2, 3]],
    ["1984", "George Orwell", 300, true, [4, 5]],
    ["The Great Gatsby", "F. Scott Fitzgerald", 150, true, [3, 4]],
    ["To Kill a Mockingbird", "Harper Lee", 250, true, [2, 3]],
    ["The Catcher in the Rye", "J.D. Salinger", 200, true, [1, 2]],
    ["The Hobbit", "J.R.R. Tolkien", 300, true, [4, 5]],
    ["Fahrenheit 451", "Ray Bradbury", 200, true, [3, 4]],
    ["Brave New World", "Aldous Huxley", 250, true, [2, 3]],
    ["The Alchemist", "Paulo Coelho", 200, true, [1, 2]],
    ["The Picture of Dorian Gray", "Oscar Wilde", 300, true, [4, 5]],
];
  
addBooksToLibrary(books);
console.log(library);
  
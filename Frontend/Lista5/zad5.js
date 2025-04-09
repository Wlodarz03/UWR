/**
 * @typedef {Object} Product
 * @property {number} id - Unikalny identyfikator produktu
 * @property {string} name - Nazwa produktu
 * @property {number} quantity - Liczba sztuk do zakupienia
 * @property {Date} dueDate - Data, do której produkt powinien być zakupiony
 * @property {boolean} purchased - Status informujący, czy produkt został zakupiony
 * @property {number} [price] - Opcjonalna cena za sztukę (dotyczy tylko zakupionych produktów)
 */

/**
 * @type {Product[]}
 */
let shoppingList = [];

/**
 * Dodaje nowy produkt do listy zakupów
 * @param {string} name - Nazwa produktu
 * @param {number} quantity - Liczba sztuk
 * @param {string} dueDateString - Data w dobrym formacie
 * @returns {void}
 */
function addProduct(name, quantity, dueDateString) {
    var id = Math.floor(Math.random() * 1e9);
    var dueDate = new Date(dueDateString);
    shoppingList.push({ id: id, name: name, quantity: quantity, dueDate: dueDate, purchased: false });
}

/**
 * Usuwa produkt na podstawie id
 * @param {number} id
 * @returns {void}
 */
function removeProduct(id) {
    shoppingList = shoppingList.filter(function(product) {
        return product.id !== id;
    });
}

/**
 * Edytuje nazwę produktu
 * @param {number} id 
 * @param {string} newName 
 * @returns {void}
 */
function editProductName(id, newName) {
    var product = shoppingList.find(function(p) {
        return p.id === id;
    });
    if (product) product.name = newName;
}

/**
 * Edytuje status zakupu produktu
 * @param {number} id 
 * @param {boolean} purchased 
 * @returns {void}
 */
function editProductStatus(id, purchased) {
    var product = shoppingList.find(function(p) {
        return p.id === id;
    });
    if (product) product.purchased = purchased;
}

/**
 * Edytuje liczbę sztuk produktu
 * @param {number} id 
 * @param {number} newQuantity 
 * @returns {void}
 */
function editProductQuantity(id, newQuantity) {
    var product = shoppingList.find(function(p) {
        return p.id === id;
    });
    if (product) product.quantity = newQuantity;
}

/**
 * Edytuje datę zakupu produktu
 * @param {number} id 
 * @param {string} newDueDateString 
 * @returns {void}
 */
function editProductDueDate(id, newDueDateString) {
    var product = shoppingList.find(function(p) {
        return p.id === id;
    });
    if (product) product.dueDate = new Date(newDueDateString);
}

/**
 * Zmienia kolejność produktów
 * @param {number} fromIndex - Aktualna pozycja
 * @param {number} toIndex - Nowa pozycja
 * @returns {void}
 */
function moveProduct(fromIndex, toIndex) {
    if (fromIndex < 0 || toIndex < 0 || fromIndex >= shoppingList.length || toIndex >= shoppingList.length) return;
    var movedProduct = shoppingList.splice(fromIndex, 1)[0];
    shoppingList.splice(toIndex, 0, movedProduct);
}

/**
 * Ustawia cenę dla zakupionego produktu
 * @param {number} id 
 * @param {number} price 
 * @returns {void}
 */
function setProductPrice(id, price) {
    var product = shoppingList.find(function(p) {
        return p.id === id;
    });
    if (product && product.purchased) {
        product.price = price;
    }
}

/**
 * Usuwa wszystkie produkty, które nie mają dzisiejszej daty
 * @returns {void}
 */
function getProductsToBuyToday(){
    var date = new Date();
    date.setHours(0, 0, 0, 0);
    shoppingList = shoppingList.filter(function(product){
        if (!product.purchased){
            var dueDate = new Date(product.dueDate);
            dueDate.setHours(0, 0, 0, 0);
            return dueDate.getTime() === date.getTime();
        }
    })
}

/**
 * Oblicza koszt zakupów danego dnia
 * @param {string} dateString - Data w dobrym formacie
 * @returns {number} - Całkowity koszt zakupów
 */
function calculateTotalCost(dateString) {
    var date = new Date(dateString).toDateString();
    return shoppingList.reduce(function(sum, product) {
        if (product.purchased && product.dueDate.toDateString() === date && product.price !== undefined) {
            return sum + product.price * product.quantity;
        }
        return sum;
    }, 0);
}

/**
 * Masowe formatowanie listy zakupów
 * @param {number[]} ids - Lista ID produktów do zmodyfikowania
 * @param {function(Product): void} modifyFunction - Funkcja modyfikująca
 * @returns {void}
 */
function ModifyProducts(ids, modifyFunction) {
    shoppingList.forEach(function(product) {
        if (ids.includes(product.id)) {
            modifyFunction(product);
        }
    });
}

/**
 * Przykładowa funkcja modyfikująca - ustawiająca ilość na 42
 * @param {Product} product
 * @returns {void}
 */
function ChangeQuantity(product) {
    product.quantity = 42;
}

addProduct("Mleko", 2, "2025-04-02");
addProduct("Chleb", 1, "2025-04-03");
addProduct("Jajka", 12, "2025-04-03");
removeProduct(shoppingList[2].id);
editProductName(shoppingList[0].id, "Jogurt");
editProductDueDate(shoppingList[1].id, "2025-04-03");
editProductQuantity(shoppingList[1].id, 2);
moveProduct(0, 1);
//getProductsToBuyToday();
console.log("Lista zakupów:", shoppingList);

editProductStatus(shoppingList[1].id, true);
setProductPrice(shoppingList[1].id, 5);
console.log("Koszt zakupów na 2025-04-02:", calculateTotalCost("2025-04-02"));

ModifyProducts([shoppingList[0].id, shoppingList[1].id], ChangeQuantity);
console.log("Lista po masowej modyfikacji:", shoppingList);
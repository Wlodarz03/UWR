// Controller - Klasa kontrolera powinna być odpowiedzialna za koordynację akcji wykonywanych przez wiele klas. 
// Kontroler może korzystać z innych klas, ale nie powinien być zależny od nich.

// Klasa reprezentująca model (logikę biznesową)
public class Order
{
    public int Id { get; }
    public string Product { get; }
    public int Quantity { get; }

    public Order(int id, string product, int quantity)
    {
        Id = id;
        Product = product;
        Quantity = quantity;
    }

    public void Process()
    {
        Console.WriteLine($"Processing order {Id} for {Quantity}x {Product}.");
    }
}

// Klasa Controller zarządza operacjami na zamówieniach
public class OrderController
{
    public void PlaceOrder(int id, string product, int quantity)
    {
        Order order = new Order(id, product, quantity);
        order.Process(); // Process dzieje się w Order, Controller tylko koordynuje
    }
}

//--------------------------------------------------------------------------------

// Creator - określa, kto jest odpowiedzialny za tworzenie obiektów i kiedy powinny one być tworzone.

// Klasa reprezentująca produkt
public class Product
{
    public string Name { get; }
    public int Price { get; }

    public Product(string name, int price)
    {
        Name = name;
        Price = price;
    }
}

// Klasa koszyka (Cart) pełni rolę Creator
public class Cart
{
    private List<Product> products = new List<Product>();

    public void AddProduct(string name, int price)
    {
        Product product = new Product(name, price); // Cart tworzy obiekt Product i dodaje do listy produktów
        products.Add(product);
    }

    public void ShowProducts()
    {
        foreach (var product in products)
        {
            Console.WriteLine($"{product.Name}: {product.Price}");
        }
    }
}

// Przykładowe użycie
class Program
{
    static void Main()
    {
        OrderController controller = new OrderController();
        controller.PlaceOrder(1, "Laptop", 2);
        controller.PlaceOrder(2, "Telefon", 1);

        Cart cart = new Cart();
        cart.AddProduct("Telefon", 3000);
        cart.AddProduct("Mikrofon", 200);
        cart.AddProduct("Laptop", 5000);
        cart.ShowProducts();
    }
}

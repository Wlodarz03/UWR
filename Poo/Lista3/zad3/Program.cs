// Klasa CashRegister nie spełnia OCP (Open-Closed Principle) ponieważ nie można dodawać nowych rozszerzeń bez modyfikacji klasy CashRegister.
// Rozszerzenie o nowy sposób obliczania podatku wymagałoby modyfikacji klasy CashRegister.
// CashRegister ma tylko TaxCalculator, który oblicza podatek w ten sam sposób. 
// Printuje też ciągle w taki sam sposób, więc trzeba by zmieniać klasę CashRegister, żeby zmienić sposób wyświetlania.

// Rozwiązanie: Stworzenie interfejsu ITaxCalculator, który będzie implementowany przez różne klasy obliczające podatek 
// oraz interfejsu IPrinter, który będzie implementowany przez różne klasy wyświetlające rachunek.

public class TaxCalculator
{
    public decimal CalculateTax(decimal price)
    {
        return price * 0.22m;
    }
}
public class Item
{
    public Item(string Name, decimal Price) 
    {
        this.Name = Name;
        this.Price = Price;
    }
    public decimal Price { get; set; }
    public string Name { get; set; }
}

public class CashRegister
{
    public TaxCalculator taxCalc = new TaxCalculator();
    public decimal CalculatePrice(Item[] Items)
    {
        decimal _price = 0;
        foreach (Item item in Items)
        {
        _price += item.Price + taxCalc.CalculateTax(item.Price);
        }
        return _price;
    }
    public void PrintBill(Item[] Items)
    {
        foreach (var item in Items)
        Console.WriteLine("towar {0} : cena {1} + podatek {2}",
        item.Name, item.Price, taxCalc.CalculateTax(item.Price));
    }
}

class Program{
    public static void Main(string[] args)
    {
        Item[] items = new Item[2];
        items[0] = new Item("item1", 100);
        items[1] = new Item("item2", 200);
        CashRegister cashRegister = new CashRegister();
        cashRegister.PrintBill(items);
        Console.WriteLine(cashRegister.CalculatePrice(items));
    }
}
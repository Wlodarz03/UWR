public interface ITaxCalculator {
    decimal CalculateTax(decimal price);
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

public class StandardTaxCalculator : ITaxCalculator {
    public decimal CalculateTax(decimal price) => price * 0.22m;
}

public class ReducedTaxCalculator : ITaxCalculator {
    public decimal CalculateTax(decimal price) => price * 0.10m;
}


public interface IReceiptPrinter {
    void PrintBill(Item[] items, ITaxCalculator taxCalculator);
}


public class StandardPrinter : IReceiptPrinter {
    public void PrintBill(Item[] items, ITaxCalculator taxCalculator) {
        foreach (var item in items) {
            Console.WriteLine($"towar {item.Name} : cena {item.Price} + podatek {taxCalculator.CalculateTax(item.Price)}");
        }
    }
}

public class AlphabeticalPrinter : IReceiptPrinter {
    public void PrintBill(Item[] items, ITaxCalculator taxCalculator) {
        var sortedItems = items.OrderBy(i => i.Name).ToArray();
        foreach (var item in sortedItems) {
            Console.WriteLine($"towar {item.Name} : cena {item.Price} + podatek {taxCalculator.CalculateTax(item.Price)}");
        }
    }
}

public class CategoryPrinter : IReceiptPrinter {
    public void PrintBill(Item[] items, ITaxCalculator taxCalculator) {
        var sortedItems = items.OrderBy(i => i.Name.Length).ToArray();
        foreach (var item in sortedItems) {
            Console.WriteLine($"towar {item.Name} : cena {item.Price} + podatek {taxCalculator.CalculateTax(item.Price)}");
        }
    }
}

public class CashRegister {
    private readonly ITaxCalculator _taxCalculator;
    private readonly IReceiptPrinter _printer;

    public CashRegister(ITaxCalculator taxCalculator, IReceiptPrinter printer) {
        _taxCalculator = taxCalculator;
        _printer = printer;
    }

    public decimal CalculatePrice(Item[] items) {
        decimal totalPrice = 0;
        foreach (Item item in items) {
            totalPrice += item.Price + _taxCalculator.CalculateTax(item.Price);
        }
        return totalPrice;
    }

    public void PrintBill(Item[] items) {
        _printer.PrintBill(items, _taxCalculator);
    }
}

class Program {
    static void Main() {
        Item[] items = {
            new Item ("Ser", 12.00m),
            new Item("Chleb", 5.00m),
            new Item ("Mleko", 3.50m)
        };

        var register1 = new CashRegister(new StandardTaxCalculator(), new StandardPrinter());
        register1.PrintBill(items);

        Console.WriteLine("\n--- Drukowanie alfabetyczne ---\n");
        
        var register2 = new CashRegister(new StandardTaxCalculator(), new AlphabeticalPrinter());
        register2.PrintBill(items);

        Console.WriteLine("\n--- Drukowanie według długości + inny tax ---\n");

        var register3 = new CashRegister(new ReducedTaxCalculator(), new CategoryPrinter());
        register3.PrintBill(items);
    }
}

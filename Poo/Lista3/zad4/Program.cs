// LSP (Liskov Substitution Principle) mówi, że każda klasa pochodna powinna móc zastąpić 
// swoją klasę bazową bez zmiany poprawności działania programu.
// Czyli Square powininien być w stanie zastąpić Rectangle bez zmiany działania programu.

// Wersja 1
public class Rectangle
{
    public virtual int Width { get; set; }
    public virtual int Height { get; set; }
}
public class Square : Rectangle
{
    public override int Width
    {
        get { return base.Width; }
        set { base.Width = base.Height = value; }
    }
    public override int Height
    {
        get { return base.Height; }
        set { base.Width = base.Height = value; }
    }
}

public class AreaCalculator
{
    public int CalculateArea(Rectangle rect)
    {
        return rect.Width * rect.Height;
    }
}

// Wersja 2 
public class Square1
{
    protected int Width;
    protected int Height;

    public int GetWidth()
    {
        return Width;
    }
    public virtual void SetWidth(int value)
    {
        SetHeight(value);
    }
    
    public int GetHeight()
    {
        return Height;
    }
    public virtual void SetHeight(int value)
    {
        Height = value;
        Width = value;
    }
    public Square1 (int Width, int Height)
    {
        SetWidth(Width);
        SetHeight(Height);
    }
}
public class Rectangle1 : Square1
{
    public override void SetWidth(int value) { Width = value; }
    public override void SetHeight(int value) { Height = value; }

    public Rectangle1(int Width, int Height) : base(Width, Height) { }
}

public class AreaCalculator1
{
    public int CalculateArea(Square1 square)
    {
        return square.GetWidth() * square.GetHeight();
    }
}

public class Program{
    public static void Main()
    {
        // Test wersji 1
        AreaCalculator areaCalculator = new AreaCalculator();
        int w = 4;
        int h = 5;
        Rectangle rect = new Square();
        rect.Width = w;
        rect.Height = h;
        // każda zmiana Width lub Height na rect powoduje zmianę obu wartości :(
        Console.WriteLine(areaCalculator.CalculateArea(rect));

        // Test wersji 2
        AreaCalculator1 areaCalculator1 = new AreaCalculator1();
        Square1 square = new Rectangle1(w, h);
        Console.WriteLine(areaCalculator1.CalculateArea(square));

    }
}

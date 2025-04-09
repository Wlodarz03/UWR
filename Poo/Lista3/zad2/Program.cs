// Zasada Single Responsibility Principle (SRP) mówi, że każda klasa powinna mieć jedną odpowiedzialność i tylko jeden powód do zmiany.

// Wersja pierwsza 

// Dlaczego narusza SRP?
// Klasa ReportPrinter ma trzy odpowiedzialności: pobieranie danych, formatowanie dokumentu i drukowanie raportu.
// Jeśli zmieni się sposób pobierania danych, formatowania dokumentu lub drukowania raportu (3 powody do zmiany zamiast jednego), to klasa ReportPrinter będzie musiała zostać zmodyfikowana.

public class ReportPrinter
{
    string report = "";
    public string GetData()
    {
        return "Report Data";
    }

    public void FormatDocument()
    {
        report = "Formatted Report";
    }

    public void PrintReport()
    {
        report = GetData();
        FormatDocument();
        Console.WriteLine(report);
    }
}

// Wersja druga

// Klasa odpowiedzialna za pobieranie danych
public class ReportData
{
    public string GetData()
    {
        return "Report Data";
    }
}

// Klasa odpowiedzialna za formatowanie dokumentu
public class ReportFormatter
{
    public string report = "";
    public void FormatDocument()
    {
        // Formatowanie dokumentu
        report = "Formatted Report";
    }

}

// Klasa odpowiedzialna za drukowanie raportu
public class ReportPrinter2
{
    ReportData reportData = new ReportData();
    ReportFormatter reportFormatter = new ReportFormatter();
    public void PrintReport()
    {
        reportFormatter.report = reportData.GetData();
        reportFormatter.FormatDocument();
        Console.WriteLine(reportFormatter.report);
    }
}


// Przykładowe użycie
class Program
{
    static void Main()
    {
        ReportPrinter printer = new ReportPrinter();
        printer.PrintReport();

        // ------------------------------------------------

        ReportPrinter2 printer2 = new ReportPrinter2();
        printer2.PrintReport();
    }
}

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
    public string FormatDocument(string data)
    {   
        Console.WriteLine("Formatting document...");
        // Formatowanie dokumentu
        return data;
    }
}

// Klasa odpowiedzialna za drukowanie raportu
public class ReportPrinter
{
    private readonly ReportComposer reportComposer;

    public ReportPrinter(ReportComposer reportComposer)
    {
        this.reportComposer = reportComposer;
    }
    public void PrintReport(ReportComposer reportComposer)
    {
        Console.WriteLine(reportComposer.ComposeReport());
    }
}

public class ReportComposer
{
    private readonly ReportData _reportData;
     private readonly ReportFormatter _reportFormatter;

    public ReportComposer(ReportData reportData, ReportFormatter reportFormatter)
    {
        this._reportData = reportData;
        this._reportFormatter = reportFormatter;
    }

    public string ComposeReport()
    {
        var data = _reportData.GetData();
        string format = _reportFormatter.FormatDocument(data);
        return format;
    }

}
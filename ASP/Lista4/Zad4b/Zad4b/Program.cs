using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Options;
using Microsoft.Extensions.DependencyInjection;

var builder = WebApplication.CreateBuilder(args);

builder.Configuration
    .AddJsonFile("AddJsonFile.json", optional: true, reloadOnChange: true)
    .AddXmlFile("AddXmlFile.xml", optional: true, reloadOnChange: true);

builder.Services.AddOptions<AppSettingsConfig>().Bind(builder.Configuration.GetSection("AppSettings"));

var app = builder.Build();

// Endpoint odczytujący dane za pomocą IConfiguration i indekserów
app.MapGet("/config",
    (IConfiguration config) =>
    {
        var daneSetting = config["imie"];
        var dane2Setting = config["nazwisko:lat"];
        var daneSettingxml = config["test"];
        var dane2Settingxml = config["test1:test2"];
        return $"Setting: {daneSetting}, dane2Setting: {dane2Setting} \n  daneSettingxml: {daneSettingxml}, dane2Settingxml: {dane2Settingxml}";
    });

// Endpoint odczytujący dane za pomocą IConfiguration i GetSection
app.MapGet("/section",
    (IConfiguration config) =>
    {
        var settings = config.GetSection("AppSettings").Get<AppSettingsConfig>();
        return $"Settings (via section): {string.Join(", ", settings.Settings.Select(s => $"{s.Key}={s.Value}"))}";

    });

// Endpoint odczytujący dane za pomocą wzorca IOptions
app.MapGet("/options",
    (IOptions<AppSettingsConfig> options) =>
    {
        var settings = options.Value.Settings;
        return $"Settings (via IOptions): {string.Join(", ", settings.Select(s => $"{s.Key}={s.Value}"))}";
    });

app.Run();


public class AppSettingsConfig
{
    public KeyValueConfig[] Settings { get; set; } = [];
}


public class KeyValueConfig
{
    public string? Key { get; set; }
    public string? Value { get; set; }
}

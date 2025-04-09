using Microsoft.AspNetCore.Routing.Matching;
using System.Text.Json;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddSingleton<EndpointSelector, CustomEndpointSelector>();
var app = builder.Build();

app.UseRouting();
app.UseEndpoints((endpoints) => { });


app.MapGet("/", () => "Hello World!");

app.MapGet("/hello", () => "Hello1");
app.MapGet("/hello", () => "Hello2");

app.MapGet("/{param}", (string param) =>
{
    return $"Parametr: {param}";
});

app.MapGet("/{param:int}", (int param) =>
{
    return $"Parametr typu int: {param}";
});

app.MapGet("/{param:length(1,10)}", (string param) =>
{
    return $"Parametr z ograniczeniem długości: {param}";
});

app.MapGet("/{param:required}", (string param) =>
{
    return $"Parametr wymagany: {param}";
});

app.MapGet("/{param:regex(^\\d{{4}}$)}", (string param) =>
{
    return $"Parametr spełniający wyrażenie regularne: {param}";
});


app.Run();

class CustomEndpointSelector : EndpointSelector
{
    public override async Task SelectAsync(HttpContext httpContext, CandidateSet candidates)
    {
        CandidateState selectedCandidate = new CandidateState();

        for (var i = 0; i < candidates.Count; i++)
        {
            if (candidates.IsValidCandidate(i))
            {
                selectedCandidate = candidates[i];
                break;
            }
        }

        httpContext.SetEndpoint(selectedCandidate.Endpoint);
        httpContext.Request.RouteValues = selectedCandidate.Values;
    }
}
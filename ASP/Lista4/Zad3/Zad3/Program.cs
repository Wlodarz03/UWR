using System;
using System.ComponentModel.DataAnnotations.Schema;
using Zad3;


var builder = WebApplication.CreateBuilder(args);
builder.Services.AddScoped(typeof(IDapperRepository<>), typeof(DapperRepository<>)); // zwalnia zasoby
var app = builder.Build();

app.MapGet("/", (IDapperRepository<Student> repository) =>
{
    var data = repository.GetAll();
    return Results.Ok(data);
});

app.Run();

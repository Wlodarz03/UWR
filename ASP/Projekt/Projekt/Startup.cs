using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.EntityFrameworkCore;
using Projekt.Models;
using Microsoft.Extensions.Configuration;

namespace Projekt
{
    public class Startup
    {
        public IConfiguration Configuration { get; }

        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddSession(options =>
            {
                options.IdleTimeout = TimeSpan.FromMinutes(30); // Czas, po którym sesja wygasa
                options.Cookie.HttpOnly = true;  // Ochrona przed dostępem z JavaScript
                options.Cookie.IsEssential = true;  // Niezbędne dla działania aplikacji
            });
            services.AddDbContext<ApplicationDbContext>(options =>
                options.UseSqlServer(Configuration.GetConnectionString("DefaultConnection"))); ;

            services.AddControllersWithViews();
        }

        public void Configure(IApplicationBuilder app, IWebHostEnvironment env, ApplicationDbContext context)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            else
            {
                app.UseExceptionHandler("/Home/Error");
                app.UseHsts();
            }

            app.UseSession();
            app.UseHttpsRedirection();
            app.UseStaticFiles();
            app.UseRouting();
            app.UseAuthorization();

            if (!context.Products.Any())
            {
                context.Products.AddRange(
                    new Product { Name = "Produkt 1", Description = "Opis produktu 1", Price = 19.99m, Stock = 50 },
                    new Product { Name = "Produkt 2", Description = "Opis produktu 2", Price = 29.99m, Stock = 30 },
                    new Product { Name = "Produkt 3", Description = "Opis produktu 3", Price = 15.99m, Stock = 100 },
                    new Product { Name = "Produkt 4", Description = "Opis produktu 4", Price = 9.99m, Stock = 25 },
                    new Product { Name = "Produkt 5", Description = "Opis produktu 5", Price = 49.99m, Stock = 75 },
                    new Product { Name = "Produkt 6", Description = "Opis produktu 6", Price = 12.99m, Stock = 40 },
                    new Product { Name = "Produkt 7", Description = "Opis produktu 7", Price = 39.99m, Stock = 60 },
                    new Product { Name = "Produkt 8", Description = "Opis produktu 8", Price = 59.99m, Stock = 10 },
                    new Product { Name = "Produkt 9", Description = "Opis produktu 9", Price = 99.99m, Stock = 5 },
                    new Product { Name = "Produkt 10", Description = "Opis produktu 10", Price = 25.99m, Stock = 80 }
                );
                context.SaveChanges();
            }

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllerRoute(
                    name: "default",
                    pattern: "{controller=Product}/{action=Index}/{id?}");
            });
        }
    }
}

using Microsoft.AspNetCore.Mvc;
using Projekt.Models;
using Microsoft.EntityFrameworkCore;
using System.Linq;
using Microsoft.AspNetCore.Http;
using Projekt;

public class CartController : Controller
{
    private readonly ApplicationDbContext _context;

    public CartController(ApplicationDbContext context)
    {
        _context = context;
    }

    // Widok koszyka
    public IActionResult Cart()
    {
        var cart = GetCart();
        return View(cart);
    }

    // Dodawanie produktu do koszyka
    public IActionResult AddToCart(int productId)
    {
        var username = HttpContext.Session.GetString("Username");
        if (string.IsNullOrEmpty(username))
        {
            // Jeśli użytkownik nie jest zalogowany, przekieruj go do strony logowania lub wyświetl komunikat
            TempData["Message"] = "Musisz być zalogowany, aby dodać produkty do koszyka.";
            return RedirectToAction("Details", "Product", new { id = productId });
        }
        else
        {
            var product = _context.Products.Find(productId);
            if (product != null)
            {
                var cart = GetCart();

                // Sprawdź, czy produkt już istnieje w koszyku
                var existingItem = cart.Items.FirstOrDefault(i => i.ProductId == productId);

                if (existingItem != null)
                {
                    existingItem.Quantity++;
                }
                else
                {
                    cart.Items.Add(new CartItem
                    {
                        ProductId = product.Id,
                        Name = product.Name,
                        Price = product.Price,
                        Quantity = 1
                    });
                }

                SaveCart(cart);
            }

            return RedirectToAction("Details", "Product", new { id = productId });
        }
        
    }

    // Usuwanie produktu z koszyka
    public IActionResult RemoveFromCart(int productId)
    {
        var cart = GetCart();

        var item = cart.Items.FirstOrDefault(i => i.ProductId == productId);
        if (item != null)
        {
            cart.Items.Remove(item);
            SaveCart(cart);
        }

        return RedirectToAction("Cart");
    }

    public IActionResult Checkout()
    {
        ClearCart();
        return View("End");
    }

    // Pobieranie koszyka z sesji
    private Cart GetCart()
    {
        var cart = HttpContext.Session.Get<Cart>("Cart") ?? new Cart();
        return cart;
    }

    // Zapisywanie koszyka do sesji
    private void SaveCart(Cart cart)
    {
        HttpContext.Session.Set("Cart", cart);
    }

    // Czyszczenie koszyka
    private void ClearCart()
    {
        HttpContext.Session.Remove("Cart");
    }
}

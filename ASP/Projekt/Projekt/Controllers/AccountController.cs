using Microsoft.AspNetCore.Mvc;
using Projekt.Models;
using Projekt;
using System.Linq;
using Microsoft.AspNetCore.Http;

public class AccountController : Controller
{
    private readonly ApplicationDbContext _context;

    public AccountController(ApplicationDbContext context)
    {
        _context = context;
    }

    // Akcja do wyświetlania formularza rejestracji
    public IActionResult Register()
    {
        return View();
    }

    // Akcja do obsługi rejestracji
    [HttpPost]
    public IActionResult Register(User user)
    {
        if (ModelState.IsValid)
        {
            // Sprawdzanie, czy użytkownik o tym samym loginie już istnieje
            var existingUser = _context.User.FirstOrDefault(u => u.Username == user.Username);
            if (existingUser != null)
            {
                // Jeśli użytkownik już istnieje, wyświetlamy błąd
                ModelState.AddModelError("Username", "Użytkownik o tym loginie już istnieje.");
                return View(user); // Powrót do formularza rejestracji
            }

            // Dodanie nowego użytkownika
            _context.User.Add(user);
            _context.SaveChanges();

            // Logowanie użytkownika po rejestracji (zapisywanie w sesji)
            HttpContext.Session.SetString("Username", user.Username);

            // Po rejestracji, przekierowanie na stronę główną
            return RedirectToAction("Index", "Product");
        }

        return View(user); // W przypadku błędów w formularzu, powróć do widoku rejestracji
    }

    // Akcja do wyświetlania formularza logowania
    public IActionResult Login()
    {
        return View();
    }

    // Akcja do obsługi logowania
    [HttpPost]
    public IActionResult Login(string username, string password)
    {
        // Szukanie użytkownika w bazie
        var user = _context.User
            .FirstOrDefault(u => u.Username == username && u.Password == password);

        if (user != null)
        {
            // Zalogowanie użytkownika (zapisanie w sesji)
            HttpContext.Session.SetString("Username", user.Username);

            // Usuwanie koszyka
            HttpContext.Session.Remove("Cart");

            // Po logowaniu, przekierowanie na stronę główną
            return RedirectToAction("Index", "Product");
        }

        // Jeśli dane logowania są błędne, wyświetlenie komunikatu
        ModelState.AddModelError("", "Nieprawidłowy login lub hasło");
        return View();  // W przypadku błędów, wróć do widoku logowania
    }

    // Lista użytkowników (dla administratora)
    public IActionResult Users()
    {
        var users = _context.User.ToList();
        return View(users);
    }
}

using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using Zad5.Models;

namespace Zad5.Controllers
{
    public class LoginController : Controller
    {
        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }
        [HttpPost]
        public IActionResult Login(LoginModel model)
        {
            if (ModelState.IsValid)
            {
                return RedirectToAction("Index", "Login");
            }
            // If invalid, redisplay the form
            return View(model);
        }
        public IActionResult Index()
        {
            return View();
        }
    }
}
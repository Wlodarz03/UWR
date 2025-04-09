using Microsoft.AspNetCore.Mvc;
using Projekt.Models;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace Projekt.Controllers
{
    public class ProductController : Controller
    {
        private readonly ApplicationDbContext _context;

        public ProductController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index(string search)
        {
            string username = HttpContext.Session.GetString("Username");

            var products = from p in _context.Products
                           select p;

            if (!string.IsNullOrEmpty(search))
            {
                products = products.Where(p => p.Name.Contains(search) || p.Description.Contains(search));
            }

            var productList = await products.ToListAsync();
            if (!productList.Any())
            {
                Console.WriteLine("Brak produktów w bazie!");
            }

            ViewData["Username"] = username;

            return View(productList);
        }


        public async Task<IActionResult> Details(int id)
        {
            var product = await _context.Products.FindAsync(id);
            if (product == null)
            {
                return NotFound();
            }

            return View(product);
        }
    }
}

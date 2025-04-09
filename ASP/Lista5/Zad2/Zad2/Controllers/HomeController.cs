using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using Zad2.Models;

namespace Zad2.Controllers
{
    public class HomeController : Controller
    {
        //wbudowane
        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        [HttpGet]
        public IActionResult Start()
        {
            var model = new HomeStartModel
            {
                Tasks = new List<int?> { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
            };
            return View(model);
        }
        [HttpPost]
        public IActionResult Start(HomeStartModel model)
        {

            for (int i = 0; i < model.Tasks.Count; i++)
            {
                if (!model.Tasks[i].HasValue)
                {
                    model.Tasks[i] = 0;
                }
            }
            if (ModelState.IsValid)
            {
                var queryString = $"?name={model.Name}&surname={model.Surname}&subject={model.Subject}&setnumber={model.SetNumber}&date={model.Date}&tasks={string.Join(",", model.Tasks)}";
                return Redirect("Home/Print" + queryString);
            }
            else
            {
                return Redirect("Home/Error");
            }
        }
        [HttpGet]
        public IActionResult Error()
        {
            return View();
        }

        [HttpGet]
        public IActionResult Print(string name, string surname, string subject, string setnumber, string date, string tasks)
        {
            var model = new HomeStartModel
            {
                Name = name,
                Surname = surname,
                Subject = subject,
                SetNumber = setnumber,
                Date = date,
                Tasks = tasks
                             .Split(',')
                             .Select(score =>
                             {
                                 if (int.TryParse(score, out int s))
                                 {
                                     return (int?)s;
                                 }
                                 return null;
                             })
                             .ToList()
            };
            return View(model);
        }

    }
}
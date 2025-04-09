using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Zad1.Models;

namespace Zad1.Controllers
{
    public class HomeController : Controller
    {
        // GET: Home
        // akcja Index
        //domysle sciezki:
        // /home
        // /home/index
        // / jest to spowodowane tym co mamy w App_Start
        //ActionResult to klasa abstrakcyjna ktora ma jedyna metode execute ktory otrzymuje context z kontrolera
        [HttpGet]
        public ActionResult Start()
        {
            var model = new HomeStartModel
            {
                Tasks = new List<int?> { null, null, null, null, null, null, null, null, null, null }
            };
            return View(model);
        }
        [HttpPost]
        public ActionResult Start(HomeStartModel model)
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
        public ActionResult Error()
        {
            return View();

        }

        [HttpGet]
        public ActionResult Print(string name, string surname, string subject, string setnumber, string date, string tasks)
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
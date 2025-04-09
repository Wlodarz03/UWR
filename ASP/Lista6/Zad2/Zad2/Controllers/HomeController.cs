using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using Zad2.Models;
using Microsoft.Data.SqlClient;

namespace WebApplication2.Controllers
{
    public class HomeController : Controller
    {
        private readonly SqlConnection _sqlConnection;
        public HomeController(SqlConnection sqlConnection)
        {
            _sqlConnection = sqlConnection;
            this._sqlConnection.Open();
        }

        public IActionResult Index()
        {
            ViewBag.ConnectionState = _sqlConnection.State.ToString();
            return View();
        }

        [HttpPost]
        public IActionResult CloseConnection()
        {
            if (_sqlConnection.State == System.Data.ConnectionState.Open)
            {
                _sqlConnection.Close();
            }
            ViewBag.ConnectionState = _sqlConnection.State.ToString();
            return View("Index");
        }
    }
}
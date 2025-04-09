using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Zad4.Models
{
    public class SampleViewModel
    {
        public bool AcceptTerms { get; set; } = true;
        public string SelectedOption { get; set; } = "Java";
        public List<string> Options { get; set; } = new List<string> { "ASP.NET", "Java", ".NET" };
        public string Name { get; set; } = "Wlod";
        public string Password { get; set; }
        public string Description { get; set; } = "Opis: ";
    }
}
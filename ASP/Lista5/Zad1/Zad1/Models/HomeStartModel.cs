using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Zad1.Models
{   // definiujemy sobie wszystkie pola ktore sa w naszej deklaracji
    public class HomeStartModel
    {
        [Required]
        public string Name { get; set; } = string.Empty;

        [Required]
        public string Surname { get; set; } = string.Empty;

        [Required]
        public string Subject { get; set; } = string.Empty;

        [Required]
        public string SetNumber { get; set; } = string.Empty;

        [Required]
        public string Date { get; set; } = string.Empty;

        public List<int?> Tasks { get; set; } = new List<int?>();
    }
}
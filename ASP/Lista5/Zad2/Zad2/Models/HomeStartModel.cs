using System.ComponentModel.DataAnnotations;

namespace Zad2.Models
{
    public class HomeStartModel
    {
        [Required(ErrorMessage = "Imię jest wymagane")]
        public string Name { get; set; } = string.Empty;

        [Required(ErrorMessage = "Nazwisko jest wymagane")]
        public string Surname { get; set; } = string.Empty;

        [Required(ErrorMessage = "Przedmiot jest wymagany")]
        public string Subject { get; set; } = string.Empty;

        [Required(ErrorMessage = "Numer zestawu jest wymagany")]
        public string SetNumber { get; set; } = string.Empty;

        [Required(ErrorMessage = "Data jest wymagana")]
        public string Date { get; set; } = string.Empty;

        public List<int?> Tasks { get; set; } = new List<int?>();
    }
}

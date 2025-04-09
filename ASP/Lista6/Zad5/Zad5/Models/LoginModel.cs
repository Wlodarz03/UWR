using System.ComponentModel.DataAnnotations;

namespace Zad5.Models
{
    public class LoginModel
    {
        [Required]
        [PeselValidator("value")]
        public string PESEL { get; set; } = string.Empty;

        [Required]
        [SignsValidator("value")]
        public string Password { get; set; } = string.Empty;
    }
}

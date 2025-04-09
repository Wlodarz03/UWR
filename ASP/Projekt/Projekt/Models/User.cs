namespace Projekt.Models
{
    public class User
    {
        public int Id { get; set; } // Identyfikator użytkownika
        public string Username { get; set; } // Login użytkownika
        public string Password { get; set; } // Zaszyfrowane hasło
    }
}

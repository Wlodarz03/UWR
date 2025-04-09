using System.ComponentModel.DataAnnotations;
using System.Text.RegularExpressions;

namespace Zad5
{
    public class SignsValidator : ValidationAttribute
    {
        private string _value { get; set; }

        public SignsValidator(string value)
        {
            this._value = value;
        }

        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            if (value == null)
                return new ValidationResult("Wartość nie może być pusta.");

            var input = value.ToString();
            var regex = new Regex(@"^[a-zA-ZąćęłńóśźżĄĆĘŁŃÓŚŹŻ0-9\s]*$");

            if (regex.IsMatch(input))
                return ValidationResult.Success;
            else
                return new ValidationResult("Wartość może zawierać tylko litery łacińskie, polskie znaki diakrytyczne, spacje i cyfry.");
        }
    }
}


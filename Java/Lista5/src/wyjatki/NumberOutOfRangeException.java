package wyjatki;

public class NumberOutOfRangeException extends Exception {
    public NumberOutOfRangeException(int number, int max) {
        super("Liczba " + number + " jest poza zakresem 1 do " + max + ".");
    }
}

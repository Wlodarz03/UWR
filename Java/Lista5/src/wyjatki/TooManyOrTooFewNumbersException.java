package wyjatki;

public class TooManyOrTooFewNumbersException extends Exception {
    public TooManyOrTooFewNumbersException(int expected, int provided) {
        super("Oczekiwano " + expected + " cyfr, a podano " + provided + ".");
    }
}
package wyjatki;

public class DuplicateNumberException extends Exception {
    public DuplicateNumberException(int num) {
        super("Cyfra " + num + " występuje więcej niż raz.");
    }
}

import java.util.*;
import java.util.logging.*;
import java.io.*;
import java.util.stream.Collectors;

import wyjatki.*;

/**
 * Reprezentuje element historii gry, zawierający próbę (listę liczb) i odpowiedź.
 */
class HistoryElement{
    /** Lista liczb zgadywanych przez gracza */
    public List<Integer> proba;
     /** Odpowiedź na próbę gracza */
    public String odpowiedz;

    /**
     * Konstruktor inicjalizujący element historii.
     * 
     * @param p Lista liczb zgadywanych przez gracza
     * @param o Odpowiedź na próbę gracza
     */
    public HistoryElement(List<Integer> p, String o){
        this.proba = p;
        this.odpowiedz = o;
    }

    /**
     * Zwraca reprezentację tekstową elementu historii.
     * 
     * @return Reprezentacja prób oraz odpowiedzi w formacie "Proba: [liczby] -> Odpowiedz: [odpowiedz]"
     */
    @Override
    public String toString() {
        String probaAsString = proba.stream()
                                    .map(String::valueOf)
                                    .collect(Collectors.joining(" "));
        return "Proba: " + probaAsString + " -> Odpowiedz: " + odpowiedz;
    }
}

/**
 * Klasa reprezentująca stan gry, zarządzająca permutacją, próbami oraz historią gry.
 */
public class GameState{
    private final int N; // Liczba elementów w permutacji
    private List<Integer> target; // Permutacja do zgadnięcia
    private int liczba_prob; // Liczba wykonanych prób
    private List<HistoryElement> history; // Historia prób i odpowiedzi
    private static final Logger logger = Logger.getLogger(GameState.class.getName());

     /**
     * Konstruktor stanu gry.
     * 
     * @param N Liczba elementów w permutacji
     * @throws IllegalArgumentException Jeżeli N jest mniejsze niż 3 lub większe niż 9
     */
    public GameState(int N) {
        if (N > 9 || N < 3){
            throw new IllegalArgumentException("N musi byc miedzy 3 a 9");
        }
        this.N = N;
        this.liczba_prob = 0;
        this.history = new ArrayList<>();
        this.target = generatePermutation();
        logger.log(Level.INFO, "Rozpoczęcie nowej gry");
        history.add(new HistoryElement(target, "START GRY"));
    }

    /**
     * Czyści permutację docelową, ustawiając ją na pustą.
     */
    public void ClearTarget(){
        this.target = new ArrayList<>();
    }

    /**
     * Generuje losową permutację liczb od 1 do N.
     * 
     * @return Losowa permutacja liczb od 1 do N
     */
    private List<Integer> generatePermutation(){
        List<Integer> perm = new ArrayList<>();
        for (int i = 1; i <= N; i++){
            perm.add(i);
        }
        Collections.shuffle(perm);
        return perm;
    }

    /**
     * Sprawdza próbę gracza i porównuje ją z permutacją docelową.
     * 
     * @param guess Lista liczb zgadywanych przez gracza
     * @return Odpowiedź na próbę (komunikat o wyniku)
     * @throws DuplicateNumberException Jeżeli próba zawiera duplikaty liczb
     * @throws TooManyOrTooFewNumbersException Jeżeli próba zawiera niewłaściwą liczbę liczb
     * @throws NumberOutOfRangeException Jeżeli któraś liczba jest poza zakresem
     */
    public String checkGuess(List<Integer> guess) throws DuplicateNumberException, TooManyOrTooFewNumbersException, NumberOutOfRangeException{

        liczba_prob++;
        assert liczba_prob <= N * N : "Liczba prob przekroczyla dozwolony limit";

        // sprawdzenie czy ilość cyfr w próbie się zgadza
        // if (guess.size() != N){
        //     throw new TooManyOrTooFewNumbersException(N, guess.size());
        // }

        Set<Integer> uniqueNumbers = new HashSet<>();
        for (int num : guess){
            
            // sprawdzenie czy liczba jest w zakresie
            if (num < 1 || num > N){
                throw new NumberOutOfRangeException(num, N);
            }

            // sprawdzenie czy cyfra się nie powtórzyła
            if (!uniqueNumbers.add(num)){
                throw new DuplicateNumberException(num);
            }
        }

        logger.log(Level.INFO, " Gracz zgaduje permutacje: " + guess);
        String result;
        if (guess.equals(target)){
            logger.log(Level.INFO, "Gracz odgadł permutację: " + guess);
            result = "Gratulacje! Odgadłeś poprawnie.";
            history.add(new HistoryElement(guess, result));
        }
        else{
            // zliczanie błędnie położonych liczb i zbieranie tych liczb
            int incorrect = 0;
            List<Integer> incorrectNumbers = new ArrayList<>();
            for (int i = 0; i < N; i++) {
                if (!guess.get(i).equals(target.get(i))){
                    incorrect++;
                    incorrectNumbers.add(guess.get(i));
                }
            }
            Random random = new Random();
            int randomIndex = random.nextInt(incorrectNumbers.size());
            int wrongNumber = incorrectNumbers.get(randomIndex);
            String hint = target.indexOf(wrongNumber) < guess.indexOf(wrongNumber) ? "w lewo" : "w prawo";
            if (incorrect < 5 && incorrect > 1){
                result = incorrect + " cyfry na złych pozycjach, cyfra: " + wrongNumber + " powinna być " + hint;
            }
            else if (incorrect >= 5){
                result = incorrect + " cyfr na złych pozycjach, cyfra: " + wrongNumber + " powinna być " + hint;
            }
            else{
                result = incorrect + " cyfra na złych pozycjach, cyfra: " + wrongNumber + " powinna być " + hint;
            }

            history.add(new HistoryElement(guess, result));
            logger.log(Level.INFO, "Próba " + liczba_prob + ": " + guess + " -> " + result);
        }
        return result;
    }

    /**
     * Zwraca historię prób i odpowiedzi.
     * 
     * @return Lista elementów historii
     */
    public List<HistoryElement> getHistory(){
        return history;
    }

    /**
     * Zapisuje historię gry do pliku logu.
     */
    public void saveGameLog() {
        try (FileWriter writer = new FileWriter("rozgrywka.log", true);
             BufferedWriter bufferedWriter = new BufferedWriter(writer)) {
            for (HistoryElement record : history) {
                bufferedWriter.write(record.toString());
                bufferedWriter.newLine();
            }
            logger.log(Level.INFO, "Zapisano historię rozgrywki do pliku rozgrywka.log.");
        }
        catch (IOException e) {
            logger.log(Level.SEVERE, "Błąd przy zapisywaniu logu gry", e);
        }
    }
}

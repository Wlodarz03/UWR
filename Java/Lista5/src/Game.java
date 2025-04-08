import java.io.*;
import java.util.*;
import java.util.logging.*;

import wyjatki.*;

/**
 * Główna klasa gry, zarządzająca rozgrywką i interakcją z użytkownikiem.
 */
public class Game {
    private static final Logger logger = Logger.getLogger(Game.class.getName());

    /**
     * Główna metoda programu. Umożliwia rozpoczęcie gry, wprowadzanie prób oraz zapis historii gry.
     * 
     * @param args Argumenty wejściowe (nie są wykorzystywane)
     */
    public static void main(String[] args) {
        configureLogger();
        clearGameLog();

        Scanner scanner = null;
        GameState gameState = null;

        try{
            scanner = new Scanner(System.in);
            boolean playAgain = true;
    
            while (playAgain) {
                
                int N = 0;
                boolean validDifficulty = false;

                while (!validDifficulty){
                    try{
                        System.out.print("Wybierz poziom trudności od 3 do 9: ");
                        N = scanner.nextInt();
                        gameState = new GameState(N);
                        validDifficulty = true;
                    }
                    catch (IllegalArgumentException e) {
                        logger.log(Level.WARNING, "Nieprawidłowa wartość N: " + N + ". N musi być pomiędzy 3 a 9.");
                    }
                }
                
                boolean guessedCorrectly = false;
    
                while (!guessedCorrectly) {
                    System.out.print("Podaj permutację długości " + N + " lub wpisz koniec by zakończyć: ");

                    List<Integer> guess = new ArrayList<>();
                    for (int i = 0; i < N; i++){ 
                        String input = scanner.next();
                        if (input.equalsIgnoreCase("koniec")) {
                            logger.log(Level.INFO, "Koniec gry, gracz sie poddal");
                            gameState.ClearTarget();
                            return;
                        }
                        guess.add(Integer.parseInt(input));
                    }

                    boolean validGuess = false;
                    while (!validGuess) {
                        try {
                            String response = gameState.checkGuess(guess);
                            if (response.contains("Gratulacje")) {
                                System.out.println(response);
                                guessedCorrectly = true;
                                gameState.ClearTarget();
                            }
                            validGuess = true;
                        }
                        catch (DuplicateNumberException | TooManyOrTooFewNumbersException | NumberOutOfRangeException e) {
                            logger.log(Level.WARNING, "Nieprawidłowa próba: " + e.getMessage());
                            System.out.print("Spróbuj ponownie: ");
                            guess.clear();
                            for (int i = 0; i < N; i++) {
                                String input = scanner.next();
                                if (input.equalsIgnoreCase("koniec")) {
                                    logger.log(Level.INFO, "Koniec gry, gracz sie poddal");
                                    gameState.ClearTarget();
                                    return;
                                }
                                guess.add(Integer.parseInt(input));
                            }
                        }
                    }
                }
    
                gameState.saveGameLog();
    
                System.out.print("Chcesz zagrać jeszcze raz? (tak/nie): ");
                playAgain = scanner.next().equalsIgnoreCase("tak");
                clearGameLog();
            }
        }
        finally{
            if (scanner != null) {
                scanner.close();
            }
        }
        
    }

    private static void configureLogger() {
        try {
            LogManager.getLogManager().readConfiguration(new FileInputStream("logging.properties"));
        }
        catch (IOException e) {
            System.err.println("Nie udało się załadować konfiguracji loggera.");
        }
    }

    private static void clearGameLog() {
        try (FileWriter writer = new FileWriter("rozgrywka.log")) {
        }
        catch (IOException e) {
            System.err.println("Nie udało się wyczyścić pliku rozgrywka.log");
        }
    }
}

package obliczenia;

import struktury.*;

public class Main {
    public static void main(String[] args){

        // Ustaw na początku programu testowego zmienną x na wartość 1.618.
        Zmienna.dodajZmienna("x", 1.618);

        // 7 + x * 5
        Wyrazenie w0 = new Dodaj(
                new Liczba(7),
                new Mnoz(
                        new Zmienna("x"),
                        new Liczba(5)
                )
        );
        System.out.println(w0.toString());
        System.out.println(w0.oblicz());

        // 7 + 5 * 3 - 1
        Wyrazenie w1 = new Odejmij(
            new Dodaj(
                new Liczba(7),
                new Mnoz(new Liczba(5), new Liczba(3))
            ),
            new Liczba(1)
        );
        System.out.println(w1.toString());
        System.out.println(w1.oblicz());

        // ~ (2 - x) * e
        Wyrazenie w2 = new Mnoz(
            new Przeciwny(
                new Odejmij(
                    new Liczba(2),
                    new Zmienna("x"))
                ),
            new E()
        );
        System.out.println(w2.toString());
        System.out.println(w2.oblicz());

        //(3 * π - 1) / (! x + 5)
        Wyrazenie w3 = new Dziel(
            new Odejmij(
                new Mnoz(
                    new Liczba(3),
                    new Pi()
                ),
                new Liczba(1)
            ),
            new Dodaj(
                new Odwrotny(new Zmienna("x")),
                new Liczba(5)
            )
        );
        System.out.println(w3.toString());
        System.out.println(w3.oblicz());

        // sin((x + 13) * π / (1 - x))
        Wyrazenie w4 = new Sin(
            new Dziel(
                new Mnoz(
                    new Dodaj(new Zmienna("x"), new Liczba(13)),
                    new Pi()
                ),
                new Odejmij(new Liczba(1), new Zmienna("x"))
            )
        );
        System.out.println(w4.toString());
        System.out.println(w4.oblicz());

        // exp(5) + x * log(e, x) 

        Wyrazenie w5 = new Dodaj(
            new Exp(new Liczba(5)),
            new Mnoz(
                new Zmienna("x"),
                new Log(new E(), new Zmienna("x"))
            )
        );
        System.out.println(w5.toString());
        System.out.println(w5.oblicz());

        // wyrażenia błędne

        // Wyrazenie w6 = new Dziel(new Liczba(1), new Liczba(0));
        // Wyrazenie w7 = new Log(new Liczba(1), new Liczba(-2));
        // System.out.println(w6.toString());
        // System.out.println(w6.oblicz());
        // System.out.println(w7.toString());
        // System.out.println(w7.oblicz());

        // Klonowanie par

        Para p = new Para("fein", 3.10);
        Para p2 = p.clone();
        System.out.println(p.toString());
        System.out.println(p2.toString());
    }
}

package obliczenia;

import struktury.ZbiorTablicowy;
import struktury.Para;

public abstract class Operand extends Wyrazenie{
}

class Liczba extends Operand{
    private double wartosc;

    public Liczba(double wart){
        this.wartosc = wart;
    }

    @Override
    public double oblicz(){
        return wartosc;
    }

    @Override
    public String toString() {
        return Double.toString(wartosc);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Liczba liczba)) return false;

        return wartosc == liczba.wartosc;
    }
}

class Stala extends Operand{
    protected String nazwa;
    protected double wartosc;

    public Stala(String nazwa, double wartosc) {
        this.nazwa = nazwa;
        this.wartosc = wartosc;
    }

    @Override
    public double oblicz() {
        return wartosc;
    }

    @Override
    public String toString() {
        return nazwa;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Stala stala)) return false;

        return nazwa.equals(stala.nazwa);
    }
}

class Pi extends Stala{
    public Pi() {
        super("pi", Math.PI);
    }
}

class E extends Stala {
    public E() {
        super("e", Math.E);
    }
}

class Zmienna extends Operand{
    private static final ZbiorTablicowy zbior = new ZbiorTablicowy(10);
    private final String nazwa;

    public Zmienna(String nazwa) {
        this.nazwa = nazwa;
    }

    public static void dodajZmienna(String nazwa, double wartosc) {
        zbior.wstaw(new Para(nazwa, wartosc));
    }

    public static double odczytajZmienna(String nazwa) {
        if(zbior.szukaj(nazwa) == null)
            throw new IllegalArgumentException("Nie ma takiej zmiennej");
        return zbior.szukaj(nazwa).getWartosc();
    }

    @Override
    public double oblicz() {
        return odczytajZmienna(nazwa);
    }

    @Override
    public String toString() {
        return nazwa;
    }
}

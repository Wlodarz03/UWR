package struktury;

public class Para implements Cloneable, Comparable<Para> {
    public final String klucz;
    private double wartosc;

    // konstruktor 
    public Para(String klucz, double wartosc) {
        if (klucz == null) {
            throw new IllegalArgumentException("Nie moze byc null");
        }
        if (!klucz.matches("[a-z]+")) {
            throw new IllegalArgumentException("Tylko male litery alfabetu angielskiego");
        }
        else {
            this.klucz = klucz;
            this.wartosc = wartosc;
        }
    }

    // getter wartosci
    public double getWartosc(){
        return wartosc;
    }

    // setter wartosci
    public void setWartosc(double w){
        this.wartosc = w;
    }

    @Override
    public String toString(){
        return "Para{ " + 
                "klucz=" + klucz + ", " +
                "wartosc=" + wartosc + "}";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Para para)) return false;
        return klucz.equals(para.klucz);
    }

    @Override
    public Para clone(){
        return new Para(this.klucz, this.wartosc);
    }

    @Override
    public int compareTo(Para p){
        return this.klucz.compareTo(p.klucz);
    }
}
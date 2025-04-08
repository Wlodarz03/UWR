package figury;

public class Odcinek {
    private Punkt p1;
    private Punkt p2;

    public Odcinek(Punkt p1, Punkt p2) {
        this.p1 = new Punkt(p1.getx(), p1.gety());
        this.p2 = new Punkt(p2.getx(), p2.gety());
        sprawdzDlugoscOdcinka();
    }

    public Punkt getP1() {
        return p1;
    }
    public Punkt getP2() {
        return p2;
    }

    private void sprawdzDlugoscOdcinka() {
        double epsilon = 1e-10;
        if (Math.abs(p1.getx() - p2.getx()) < epsilon && Math.abs(p1.gety() - p2.gety()) < epsilon) {
            throw new IllegalArgumentException("Nie mozna utworzyc odcinka o dlugosci 0");
        }
    }

    public void przesun(Wektor w) {
        p1.przesun(w);
        p2.przesun(w);
    }

    public void obroc(Punkt p, double kat) {
        p1.obroc(p, kat);
        p2.obroc(p, kat);
    }

    public void odbij(Prosta k) {
        p1.odbij(k);
        p2.odbij(k);
    }

    // do testów
    public double dlugosc_odcinka() {
        return Math.sqrt(Math.pow(p1.getx() - p2.getx(), 2) + Math.pow(p1.gety() - p2.gety(), 2));
    }
}

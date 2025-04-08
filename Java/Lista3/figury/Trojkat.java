package figury;

public class Trojkat {
    private Punkt p1;
    private Punkt p2;
    private Punkt p3;

    public Trojkat(Punkt p1, Punkt p2, Punkt p3) {
        this.p1 = new Punkt(p1.getx(), p1.gety());
        this.p2 = new Punkt(p2.getx(), p2.gety());
        this.p3 = new Punkt(p3.getx(), p3.gety());
        sprawdzBoki();
        sprawdzCzyWspoliniowe();
        sprawdzDlugosciBokow();
    }

    public Punkt getP1() {
        return p1;
    }
    public Punkt getP2() {
        return p2;
    }
    public Punkt getP3() {
        return p3;
    }

    private void sprawdzBoki() {
        double epsilon = 1e-10;
        if (Math.abs(p1.getx() - p2.getx()) < epsilon && Math.abs(p1.gety() - p2.gety()) < epsilon ||
            Math.abs(p1.getx() - p3.getx()) < epsilon && Math.abs(p1.gety() - p3.gety()) < epsilon ||
            Math.abs(p2.getx() - p3.getx()) < epsilon && Math.abs(p2.gety() - p3.gety()) < epsilon){
            throw new IllegalArgumentException("Bok o dlugosci 0");
        }
    }

    private void sprawdzCzyWspoliniowe() {
        if ((p2.getx() - p1.getx()) * (p3.gety() - p1.gety()) == (p3.getx() - p1.getx()) * (p2.gety() - p1.gety())) {
            throw new IllegalArgumentException("Nie mozna utworzyc trojkata z podanych punktow");
        }
    }

    private void sprawdzDlugosciBokow() {
        Odcinek o1 = new Odcinek(p1, p2);
        Odcinek o2 = new Odcinek(p1, p3);
        Odcinek o3 = new Odcinek(p2, p3);
        double a = o1.dlugosc_odcinka();
        double b = o2.dlugosc_odcinka();
        double c = o3.dlugosc_odcinka();
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw new IllegalArgumentException("Nie mozna utworzyc trojkata");
        }
    }

    public void przesun(Wektor w) {
        p1.przesun(w);
        p2.przesun(w);
        p3.przesun(w);
    }

    public void obroc(Punkt p, double kat) {
        p1.obroc(p, kat);
        p2.obroc(p, kat);
        p3.obroc(p, kat);
    }

    public void odbij(Prosta k) {
        p1.odbij(k);
        p2.odbij(k);
        p3.odbij(k);
    }
}

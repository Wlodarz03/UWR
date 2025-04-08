package figury;

public class Prosta {
    public final double a;
    public final double b;
    public final double c;

    public Prosta(double a, double b, double c){
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public static Prosta przesun(Prosta p, Wektor w){
        double noweC = p.c - p.a*w.dx - p.b*w.dy;
        return new Prosta(p.a, p.b, noweC);
    }

    public static boolean czyRownolegle(Prosta p1, Prosta p2){
        double epsilon = 1e-10;
        return Math.abs(p1.a/p1.b - p2.a/p2.b) < epsilon;
    }

    public static boolean czyProstopadle(Prosta p1, Prosta p2){
        double epsilon = 1e-10;
        return Math.abs(p1.a/p1.b + p2.b/p2.a) < epsilon;
    }

    public static Punkt punktPrzeciecia(Prosta p1, Prosta p2){
        if(czyRownolegle(p1, p2)){
            throw new IllegalArgumentException("Proste sa rownolegle");
        }
        double x = (p2.b*p1.c - p1.b*p2.c)/(p2.a*p1.b - p1.a*p2.b);
        double y = (p1.a*p2.c - p2.a*p1.c)/(p2.a*p1.b - p1.a*p2.b);
        return new Punkt(x, y);
    }
}

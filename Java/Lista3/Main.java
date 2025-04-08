import figury.*;

public class Main {
    public static void main(String[] args){

        Wektor v = new Wektor(1, -2);
        Wektor v2 = new Wektor(2, 2);
        Wektor v3 = Wektor.zloz(v, v2); // (3, 0)
        Prosta pr1 = new Prosta(-1, 1, 0); // y = x
        Prosta pr2 = new Prosta(1, 1, 0); // y = -x
        Prosta pr3 = new Prosta(-1, 1, 2); // y = x - 2
        Prosta przesunieta = Prosta.przesun(pr1, v);
        boolean b1 = Prosta.czyProstopadle(pr1, pr2); // TRUE
        boolean b2 = Prosta.czyProstopadle(pr1, pr3); // FALSE
        boolean b3 = Prosta.czyRownolegle(pr1, pr3); // TRUE
        boolean b4 = Prosta.czyRownolegle(pr2, pr3); // FALSE
        Punkt przeciecie = Prosta.punktPrzeciecia(pr1, pr2);
        System.out.println("v3.x: " + v3.dx + " v3.y: " + v3.dy); 
        System.out.println("Prosta x przesunieta o v, A: " + przesunieta.a + "B: " + przesunieta.b + "C: " + przesunieta.c);
        System.out.println(b1);
        System.out.println(b2);
        System.out.println(b3);
        System.out.println(b4);
        System.out.println("Punkt przeciecia prostych x i -x");
        System.out.println("x: " + przeciecie.getx() + " y: " + przeciecie.gety());
        //--------------------------------------------
        System.out.println("TESTY NA PUNKT");
        Punkt p = new Punkt(0,0);
        Punkt q = new Punkt(2, 4);
        p.przesun(v);
        System.out.print("Po przesunieciu: " + p.getx() + " " + p.gety());
        System.out.println();
        p.odbij(pr1);
        System.out.print("Po odbiciu: " + p.getx() + " " + p.gety());
        System.out.println();
        p.obroc(q,90);
        System.out.print("Po obrocie: " + p.getx() + " " + p.gety());
        System.out.println();
        //=================================================
        System.out.println("TESTY NA ODCINEK");
        Punkt p1 = new Punkt();
        Punkt p2 = new Punkt(4,0);

        // zly odcinek
        //Odcinek o = new Odcinek(p1, p1);

        Odcinek o1 = new Odcinek(p1, p2);
        System.out.println("Dlugosc: " + o1.dlugosc_odcinka());

        o1.przesun(v);
        System.out.println("Po przesunieciu odcinka: ");
        System.out.println("x1: "+o1.getP1().getx()+", y1: "+o1.getP1().gety());
        System.out.println("x2: "+o1.getP2().getx()+", y2: "+o1.getP2().gety());

        o1.odbij(pr1);
        System.out.println("Po odbiciu odcinka: ");
        System.out.println("x1: "+o1.getP1().getx()+", y1: "+o1.getP1().gety());
        System.out.println("x2: "+o1.getP2().getx()+", y2: "+o1.getP2().gety());

        o1.obroc(new Punkt(), 90);
        System.out.println("Po odrocie odcinka: ");
        System.out.println("x1: "+o1.getP1().getx()+", y1: "+o1.getP1().gety());
        System.out.println("x2: "+o1.getP2().getx()+", y2: "+o1.getP2().gety());
        //=========================================================================
        System.out.println("TESTY NA TROJKAT");
        Punkt a = new Punkt();
        Punkt b = new Punkt(4,0);
        Punkt c = new Punkt(2,4);
        Punkt d = new Punkt(6,0); // z nim wspolliniowe
        Trojkat t = new Trojkat(a,b,c);

        // nie dzialajacy trojkat
        // Trojkat t2 = new Trojkat(a, b, d);
        t.przesun(v);
        System.out.println("Trojkat po przesunieciu: ");
        System.out.println("ax: " + t.getP1().getx()+" ay: " + t.getP1().gety());
        System.out.println("bx: " + t.getP2().getx()+" by: " + t.getP2().gety());
        System.out.println("cx: " + t.getP3().getx()+" cy: " + t.getP3().gety());

        t.odbij(pr1);
        System.out.println("Trojkat po odbiciu: ");
        System.out.println("ax: " + t.getP1().getx()+" ay: " + t.getP1().gety());
        System.out.println("bx: " + t.getP2().getx()+" by: " + t.getP2().gety());
        System.out.println("cx: " + t.getP3().getx()+" cy: " + t.getP3().gety());

        t.obroc(new Punkt(),90);
        System.out.println("Trojkat po obrocie: ");
        System.out.println("ax: " + t.getP1().getx()+" ay: " + t.getP1().gety());
        System.out.println("bx: " + t.getP2().getx()+" by: " + t.getP2().gety());
        System.out.println("cx: " + t.getP3().getx()+" cy: " + t.getP3().gety());
    }
}

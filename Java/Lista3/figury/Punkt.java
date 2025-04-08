`package figury;

public class Punkt {
    private double x;
    private double y;

    public Punkt(double x, double y){
        this.x = x;
        this.y = y;
    }
    public Punkt(){
        this.x = 0;
        this.y = 0;
    }
    public double getx(){
        return x;
    }
    public double gety(){
        return y;
    }
    //przesuniecie punktu o wektor
    public void przesun(Wektor w){
        this.x += w.dx;
        this.y += w.dy;
    }
    //obrot punktu o kat wokol punktu p
    public void obroc(Punkt p, double kat){
        double x = this.x;
        double y = this.y;
        double rad = kat*Math.PI/180;

        //przesuwamy układ współrzędnych tak aby P = (0,0) -> obracamy -> przesuwamy z powrotem dodając p.x/p.y

        this.x = p.x + (x-p.x)*Math.cos(rad) - (y-p.y)*Math.sin(rad);
        this.y = p.y + (x-p.x)*Math.sin(rad) + (y-p.y)*Math.cos(rad);
    }
    
    public void odbij(Prosta k){
        double a = k.a;
        double b = k.b;
        double c = k.c;
        double x = this.x;
        double y = this.y;
        this.x = (b*b-a*a)*x - 2*a*b*y - 2*a*c;
        this.x /= (a*a+b*b);
        this.y = (a*a-b*b)*y - 2*a*b*x - 2*b*c;
        this.y /= (a*a+b*b);
    }
}
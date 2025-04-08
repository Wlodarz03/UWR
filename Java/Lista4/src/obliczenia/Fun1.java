package obliczenia;

public class Fun1 extends Dzialanie{
    protected String nazwa;
    protected Wyrazenie arg;

    public Fun1(String nazwa, Wyrazenie arg) {
        this.nazwa = nazwa;
        this.arg = arg;
    }

    // gettery
    public String getNazwa() {
        return nazwa;
    }

    public Wyrazenie getArg() {
        return arg;
    }

    @Override
    public String toString() {
        return nazwa + "(" + arg + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Fun1 fun1)) return false;

        if (!nazwa.equals(fun1.nazwa)) return false;
        return arg.equals(fun1.arg);
    }

    @Override
    public double oblicz() {
        return 0;
    }
}

class Ln extends Fun1{
    public Ln(Wyrazenie arg){
        super("ln", arg);
    }

    @Override
    public double oblicz() {
        double argument = super.oblicz();
        if (argument <= 0) throw new ArithmeticException("Liczba logarytmowana musi byc dodatnia");
        return Math.log(argument);
    }
}

class Exp extends Fun1{
    public Exp(Wyrazenie arg){
        super("exp", arg);
    }

    @Override
    public double oblicz(){
        return Math.exp(arg.oblicz());
    }
}

class Sin extends Fun1{
    public Sin(Wyrazenie arg){
        super("sin", arg);
    }

    @Override
    public double oblicz(){
        return Math.sin(arg.oblicz());
    }
}

class Cos extends Fun1{
    public Cos(Wyrazenie arg){
        super("cos", arg);
    }

    @Override
    public double oblicz(){
        return Math.cos(arg.oblicz());
    }
}

class Fun2 extends Fun1{
    protected Wyrazenie arg2;

    public Fun2(String nazwa, Wyrazenie arg, Wyrazenie arg2) {
        super(nazwa, arg);
        this.arg2 = arg2;
    }

    public Wyrazenie getArg2() {
        return arg2;
    }

    @Override
    public String toString() {
        return nazwa +"(" + arg.toString() + ", " + arg2.toString() + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Fun2 fun2)) return false;
        if (!super.equals(o)) return false;

        return arg.equals(fun2.arg) && arg2.equals(fun2.arg2);
    }
}

class Log extends Fun2{
    public Log(Wyrazenie arg, Wyrazenie arg2) {
        super("log", arg, arg2);
    }

    @Override
    public double oblicz() {
        double a = arg.oblicz();
        double b = arg2.oblicz();
        if (a <= 0 || a == 1 || b <= 0) throw new ArithmeticException("Niepoprawne argumenty do logarytmu");
        return Math.log(a) / Math.log(b);
    }
}

class Pot extends Fun2 {
    public Pot(Wyrazenie arg, Wyrazenie arg2) {
        super("pot", arg, arg2);
    }

    @Override
    public double oblicz() {
        return Math.pow(arg.oblicz(), arg2.oblicz());
    }
}
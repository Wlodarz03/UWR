package obliczenia;

public abstract class Oper1 extends Dzialanie{
    protected Wyrazenie arg;

    public Oper1() {
        this.arg = null;
    }

    public Oper1(Wyrazenie arg) {
        this.arg = arg;
    }

    public Wyrazenie getArg() {
        return arg;
    }

    public void setArg(Wyrazenie w){
        this.arg = w;
    }

    @Override
    public String toString() {
        return arg.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Oper1 oper1)) return false;

        return arg.equals(oper1.arg);
    }

    @Override
    public double oblicz() {
        return 0;
    }
}

class Przeciwny extends Oper1 {
    public Przeciwny(Wyrazenie arg) {
        super(arg);
    }

    @Override
    public double oblicz() {
        return -super.arg.oblicz();
    }

    @Override
    public String toString() {
        return "~(" + super.toString() + ")";
    }
}

class Odwrotny extends Oper1 {
    public Odwrotny(Wyrazenie arg) {
        super(arg);
    }

    @Override
    public double oblicz() {
        double value = super.arg.oblicz();
        if (value == 0) throw new ArithmeticException("Dzielenie przez zero.");
        return 1 / value;
    }

    @Override
    public String toString() {
        return "(1.0 / " + super.arg.toString() + ")";
    }
}

class Oper2 extends Oper1 {
    protected Wyrazenie arg2;

    public Oper2() {
        this.arg = null;
        this.arg2 = null;
    }
    public Oper2(Wyrazenie arg, Wyrazenie arg2) {
        super(arg);
        this.arg2 = arg2;
    }

    public Wyrazenie getArg2() {
        return arg2;
    }

    public void setArg2(Wyrazenie w) {
        this.arg2 = w;
    }

    @Override
    public String toString() {
        return arg.toString() + ", " + arg2.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Oper2 oper2)) return false;

        return arg.equals(oper2.arg) && arg2.equals(oper2.arg2);
    }
}

class Dodaj extends Oper2{
    public Dodaj(Wyrazenie arg, Wyrazenie arg2) {
        super(arg, arg2);
    }

    @Override
    public double oblicz() {
        return arg.oblicz() + arg2.oblicz();
    }

    @Override
    public String toString() {
        return arg.toString() + " + " + arg2.toString();
    }
}

class Odejmij extends Oper2{
    public Odejmij(Wyrazenie arg, Wyrazenie arg2) {
        super(arg, arg2);
    }

    @Override
    public double oblicz() {
        return arg.oblicz() - arg2.oblicz();
    }

    @Override
    public String toString() {
        return arg.toString() + " - " + arg2.toString();
    }
}

class Mnoz extends Oper2 {
    public Mnoz(Wyrazenie arg, Wyrazenie arg2) {
        super(arg, arg2);
    }

    @Override
    public double oblicz() {
        return arg.oblicz() * arg2.oblicz();
    }

    @Override
    public String toString() {
        String left = (arg instanceof Dodaj || arg instanceof Odejmij) ? "(" + arg.toString() + ")" : arg.toString();
        String right = (arg2 instanceof Dodaj || arg2 instanceof Odejmij) ? "(" + arg2.toString() + ")" : arg2.toString();
        return left + " * " + right;
    }
}

class Dziel extends Oper2 {
    public Dziel(Wyrazenie arg, Wyrazenie arg2) {
        super(arg, arg2);
    }

    @Override
    public double oblicz() {
        double prawy = arg2.oblicz();
        if (prawy == 0) throw new ArithmeticException("Dzielenie przez zero.");
        return arg.oblicz() / prawy;
    }

    @Override
    public String toString() {
        String left = (arg instanceof Dodaj || arg instanceof Odejmij) ? "(" + arg.toString() + ")" : arg.toString();
        String right = (arg2 instanceof Dodaj || arg2 instanceof Odejmij) ? "(" + arg2.toString() + ")" : arg2.toString();
        return left + " / " + right;
    }
}
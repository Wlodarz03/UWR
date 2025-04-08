package struktury;

public class ZbiorTablicowy implements Zbior, Cloneable {
    private Para[] zbior;
    private int zapelnienie;

    public ZbiorTablicowy(int rozmiar) {
        if (rozmiar <= 0) {
            throw new IllegalArgumentException("Rozmiar musi byc wiekszy od 0");
        }
        this.zbior = new Para[rozmiar];
        this.zapelnienie = 0;
    }

    public Para szukaj(String k) {
        for (int i = 0; i < zapelnienie; i++) {
            if (zbior[i].klucz.equals(k)) {
                return zbior[i];
            }
        }
        return null;
    }

    public void wstaw(Para p) {
        if (this.zapelnienie == this.zbior.length) {
            throw new IllegalStateException("Zbior jest pelny");
        }
        if (this.szukaj(p.klucz) != null) {
            this.szukaj(p.klucz).setWartosc(p.getWartosc());
            return;
        }
        this.zbior[this.zapelnienie] = p;
        this.zapelnienie++;
    }

    public void usun(String k) {
        for (int i = 0; i < this.zapelnienie; i++) {
            if (this.zbior[i].klucz.equals(k)) {
                this.zbior[i] = this.zbior[this.zapelnienie - 1];
                this.zapelnienie--;
                return;
            }
        }
    }

    public void czysc(){
        this.zbior = new Para[zbior.length];
        this.zapelnienie = 0;
    }

    public boolean pusty(){
        return zapelnienie == 0;
    }

    public int ile(){
        return zapelnienie;
    }

    @Override
    public ZbiorTablicowy clone(){
        ZbiorTablicowy zbiorTablicowy = new ZbiorTablicowy(this.zbior.length);
        for (int i = 0; i < this.zapelnienie; i++) {
            zbiorTablicowy.wstaw(this.zbior[i].clone());
        }
        return zbiorTablicowy;
    }
}

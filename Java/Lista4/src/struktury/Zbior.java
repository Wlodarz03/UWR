package struktury;

public interface Zbior {
    Para szukaj(String k);
    void wstaw(Para p);
    void usun(String k);
    void czysc();
    boolean pusty();
    int ile();
}

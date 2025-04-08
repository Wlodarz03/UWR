import java.awt.*;
import java.awt.event.*;

public class Powierzchnia extends Canvas {
    private Kreska[] kreski = new Kreska[10];
    private int liczbaKresek = 0;
    private Point poczatek;
    private Point koniec;
    private boolean rysowanie = false;
    private Color biezacyKolor = Color.BLACK;

    public Powierzchnia() {
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                poczatek = e.getPoint();
                rysowanie = true;
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                koniec = e.getPoint();
                rysowanie = false;
                if (poczatek != null && koniec != null) {
                    dodajKreske(new Kreska(poczatek, koniec, biezacyKolor));
                }
                repaint();
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                koniec = e.getPoint();
                repaint();
            }
        });

        setFocusable(true);
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_BACK_SPACE -> usunWszystkie();
                    case KeyEvent.VK_F -> usunPierwsza();
                    case KeyEvent.VK_B, KeyEvent.VK_L -> usunOstatnia();
                }
            }
        });
    }

    public void ustawKolor(Color kolor) {
        biezacyKolor = kolor;
    }

    private void dodajKreske(Kreska kreska) {
        if (liczbaKresek == kreski.length) {
            Kreska[] nowaTablica = new Kreska[kreski.length * 2];
            System.arraycopy(kreski, 0, nowaTablica, 0, kreski.length);
            kreski = nowaTablica;
        }
        kreski[liczbaKresek++] = kreska;
    }

    public void usunWszystkie() {
        liczbaKresek = 0;
        kreski = new Kreska[10];
        repaint();
    }

    public void usunPierwsza() {
        if (liczbaKresek > 0) {
            System.arraycopy(kreski, 1, kreski, 0, liczbaKresek - 1);
            liczbaKresek--;
            repaint();
        }
    }

    public void usunOstatnia() {
        if (liczbaKresek > 0) {
            System.arraycopy(kreski, 0, kreski, 0, liczbaKresek - 1);
            liczbaKresek--;
            repaint();
        }
    }

    @Override
    public void paint(Graphics gr) {
        if (rysowanie) {
            gr.setColor(Color.GRAY);
            gr.drawLine(poczatek.x, poczatek.y, koniec.x, koniec.y);
        }
        for (int i = 0; i < liczbaKresek; i++) {
            kreski[i].draw(gr);
        }
    }
}


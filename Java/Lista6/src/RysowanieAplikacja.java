import java.awt.*;
import java.awt.event.*;

public class RysowanieAplikacja extends Frame {
    private Powierzchnia powierzchnia;
    private CheckboxGroup kolorGroup;
    private Checkbox czarny, czerwony, zielony, niebieski;

    public RysowanieAplikacja() {
        super("Rysowanie aplikacja");
        setSize(800, 600);
        setLayout(new BorderLayout());

        powierzchnia = new Powierzchnia();
        add(powierzchnia, BorderLayout.CENTER);

        Panel panelBoczny = new Panel();
        panelBoczny.setLayout(new GridLayout(4, 1));
        kolorGroup = new CheckboxGroup();

        czarny = new Checkbox("Czarny", kolorGroup, true);
        czerwony = new Checkbox("Czerwony", kolorGroup, false);
        zielony = new Checkbox("Zielony", kolorGroup, false);
        niebieski = new Checkbox("Niebieski", kolorGroup, false);

        czarny.addItemListener(e -> powierzchnia.ustawKolor(Color.BLACK));
        czerwony.addItemListener(e -> powierzchnia.ustawKolor(Color.RED));
        zielony.addItemListener(e -> powierzchnia.ustawKolor(Color.GREEN));
        niebieski.addItemListener(e -> powierzchnia.ustawKolor(Color.BLUE));

        panelBoczny.add(czarny);
        panelBoczny.add(czerwony);
        panelBoczny.add(zielony);
        panelBoczny.add(niebieski);

        add(panelBoczny, BorderLayout.EAST);

        powierzchnia.requestFocusInWindow();
        
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        new RysowanieAplikacja();
    }
}


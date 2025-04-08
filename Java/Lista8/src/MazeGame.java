import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class MazeGame extends JFrame {
    private MazePanel mazePanel;
    private JLabel statusLabel;
    private Timer ghostTimer;
    private Maze maze;
    private int movesCount;
    private long startTime;
    private boolean isGameActive;

    public MazeGame() {
        setTitle("Labirynt Podróżnika");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(800, 800);
        setLayout(new BorderLayout());

        maze = new Maze(10, 10);
        mazePanel = new MazePanel(maze);
        statusLabel = new JLabel("Stan: Startowy");
        statusLabel.setHorizontalAlignment(SwingConstants.CENTER);

        add(createMenuBar(), BorderLayout.NORTH);
        add(mazePanel, BorderLayout.CENTER);
        add(statusLabel, BorderLayout.SOUTH);

        initGhostTimer();
    }


    private JMenuBar createMenuBar() {
        JMenuBar menuBar = new JMenuBar();

        // Menu Gra
        JMenu gameMenu = new JMenu("Gra");
        JMenuItem startGame = new JMenuItem("Start");
        JMenuItem resign = new JMenuItem("Rezygnacja");
        JMenuItem exit = new JMenuItem("Koniec");

        startGame.setMnemonic(KeyEvent.VK_S);
        startGame.setAccelerator(KeyStroke.getKeyStroke("control S"));
        resign.setMnemonic(KeyEvent.VK_R);
        resign.setAccelerator(KeyStroke.getKeyStroke("control R"));
        exit.setMnemonic(KeyEvent.VK_K);
        exit.setAccelerator(KeyStroke.getKeyStroke("control K"));

        startGame.addActionListener(e -> startGame());
        resign.addActionListener(e -> endGame(false));
        exit.addActionListener(e -> System.exit(0));

        gameMenu.add(startGame);
        gameMenu.add(resign);
        gameMenu.addSeparator();
        gameMenu.add(exit);

        // Menu Ustawienia
        JMenu settingsMenu = new JMenu("Ustawienia");
        JCheckBoxMenuItem markFields = new JCheckBoxMenuItem("Oznaczenie pól");
        markFields.addActionListener(e -> mazePanel.setMarkFields(markFields.isSelected()));
        settingsMenu.add(markFields);


        // Podmenu Kolory
        JMenu colorMenu = new JMenu("Kolory");
        JMenuItem backgroundColor = new JMenuItem("Tło");
        JMenuItem wallColor = new JMenuItem("Ściany");

        backgroundColor.addActionListener(e -> chooseBackgroundColor());
        wallColor.addActionListener(e -> chooseWallColor());

        colorMenu.add(backgroundColor);
        colorMenu.add(wallColor);
        settingsMenu.add(colorMenu);

        // Podmenu Rozmiary
        JMenu sizeMenu = new JMenu("Rozmiary");
        JMenuItem widthItem = new JMenuItem("Szerokość");
        JMenuItem heightItem = new JMenuItem("Wysokość");

        widthItem.addActionListener(e -> setMazeWidth());
        heightItem.addActionListener(e -> setMazeHeight());

        sizeMenu.add(widthItem);
        sizeMenu.add(heightItem);
        settingsMenu.add(sizeMenu);

        // Menu Ruchy
        JMenu moveMenu = new JMenu("Ruchy");
        JMenuItem up = new JMenuItem("W górę");
        JMenuItem right = new JMenuItem("W prawo");
        JMenuItem down = new JMenuItem("W dół");
        JMenuItem left = new JMenuItem("W lewo");

        up.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_UP, 0));
        right.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0));
        down.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_DOWN, 0));
        left.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0));

        up.addActionListener(e -> moveTraveler(0, -1));
        right.addActionListener(e -> moveTraveler(1, 0));
        down.addActionListener(e -> moveTraveler(0, 1));
        left.addActionListener(e -> moveTraveler(-1, 0));

        moveMenu.add(up);
        moveMenu.add(right);
        moveMenu.add(down);
        moveMenu.add(left);

        // Menu Pomoc
        JMenu helpMenu = new JMenu("Pomoc");
        JMenuItem aboutGame = new JMenuItem("O aplikacji");
        JMenuItem aboutAuthor = new JMenuItem("O autorze");

        aboutGame.addActionListener(e -> JOptionPane.showMessageDialog(this,
                "Gra logiczna polegajaca na przeprowadzeniu Podroznika do wyjscia.\n Gracz porusza się klawiszami strzałek aby dojść graczem do prawego dolnego rogu. \n W labiryncie porusza się również duch, który blokuje komnaty. \n Powodzenia :)",
                "O aplikacji", JOptionPane.INFORMATION_MESSAGE));
        aboutAuthor.addActionListener(e -> JOptionPane.showMessageDialog(this,
                "Autor: Michal Wlodarczak", "O autorze",
                JOptionPane.INFORMATION_MESSAGE));

        helpMenu.add(aboutGame);
        helpMenu.add(aboutAuthor);

        menuBar.add(gameMenu);
        menuBar.add(settingsMenu);
        menuBar.add(moveMenu);
        menuBar.add(helpMenu);
        menuBar.add(Box.createHorizontalGlue());

        return menuBar;
    }

    private void chooseBackgroundColor() {
        Color chosenColor = JColorChooser.showDialog(this, "Wybierz kolor tła", mazePanel.getBackground());
        if (chosenColor != null) {
            mazePanel.setBackgroundColor(chosenColor);
        }
    }
    
    private void chooseWallColor() {
        Color chosenColor = JColorChooser.showDialog(this, "Wybierz kolor ścian", Color.BLACK);
        if (chosenColor != null) {
            mazePanel.setWallColor(chosenColor);
        }
    }

    private void setMazeWidth() {
        String input = JOptionPane.showInputDialog(this, "Podaj szerokość (5-26):");
        if (input != null) {
            try {
                int width = Integer.parseInt(input);
                if (width >= 5 && width <= 26) {
                    maze = new Maze(width, maze.getHeight());
                    mazePanel.setMaze(maze);
                } else {
                    JOptionPane.showMessageDialog(this, "Niepoprawny zakres! (5-26)");
                }
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(this, "Podano nieprawidłową liczbę.");
            }
        }
    }
    
    private void setMazeHeight() {
        String input = JOptionPane.showInputDialog(this, "Podaj wysokość (5-26):");
        if (input != null) {
            try {
                int height = Integer.parseInt(input);
                if (height >= 5 && height <= 26) {
                    maze = new Maze(maze.getWidth(), height);
                    mazePanel.setMaze(maze);
                } else {
                    JOptionPane.showMessageDialog(this, "Niepoprawny zakres! (5-26)");
                }
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(this, "Podano nieprawidłową liczbę.");
            }
        }
    }

    private void initGhostTimer() {
        ghostTimer = new Timer(1000, e -> {
            maze.blockRandomPath();
            mazePanel.repaint();
        });
    }

    private void startGame() {
        maze.generateMaze();
        mazePanel.setTravelerPosition(0, 0);
        isGameActive = true;
        movesCount = 0;
        startTime = System.currentTimeMillis();
        ghostTimer.start();
        statusLabel.setText("Stan: W trakcie gry");
    }

    private void endGame(boolean success) {
        isGameActive = false;
        ghostTimer.stop();
        String result = success ? "Sukces!" : "Porazka.";
        long elapsedTime = (System.currentTimeMillis() - startTime) / 1000;
        statusLabel.setText(String.format("Stan: %s Czas: %d sek., Ruchy: %d",
                result, elapsedTime, movesCount));
        JOptionPane.showMessageDialog(this,
                String.format("%s Czas: %d sek., Ruchy: %d", result, elapsedTime, movesCount),
                "Koniec gry", JOptionPane.INFORMATION_MESSAGE);
    }

    private void moveTraveler(int dx, int dy) {
        if (!isGameActive) return;

        if (maze.moveTraveler(dx, dy)) {
            movesCount++;
            mazePanel.repaint();

            if (maze.isAtExit()) {
                endGame(true);
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MazeGame game = new MazeGame();
            game.setVisible(true);
        });
    }
}

class Maze {
    private int width, height;
    private boolean[][][] maze; 
    private boolean[][][] blockedPaths; // Do ducha
    private int travelerX, travelerY;
    private Random random = new Random();

    public Maze(int width, int height) {
        this.width = width;
        this.height = height;
        maze = new boolean[width][height][4];
        blockedPaths = new boolean[width][height][4];
    }

    // Generowanie labiryntu za pomocą algorytmu DFS
    public void generateMaze() {
        travelerX = 0;
        travelerY = 0;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                for (int d = 0; d < 4; d++) {
                    maze[x][y][d] = false;
                    blockedPaths[x][y][d] = false;
                }
            }
        }
        dfs(0, 0);
    }

    private void dfs(int x, int y) {
        int[] directions = {0, 1, 2, 3};
        shuffleArray(directions);

        for (int dir : directions) {
            int nx = x, ny = y;

            switch (dir) {
                case 0 -> ny--; // Góra
                case 1 -> nx++; // Prawo
                case 2 -> ny++; // Dół
                case 3 -> nx--; // Lewo
            }

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && !hasVisited(nx, ny)) {
                maze[x][y][dir] = true;
                maze[nx][ny][(dir + 2) % 4] = true; // Przeciwny kierunek
                dfs(nx, ny);
            }
        }
    }

    public boolean moveTraveler(int dx, int dy) {
        int nx = travelerX + dx;
        int ny = travelerY + dy;

        if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
            int dir = getDirection(dx, dy);
            if (maze[travelerX][travelerY][dir] && !blockedPaths[travelerX][travelerY][dir]) {
                travelerX = nx;
                travelerY = ny;
                return true;
            }
        }
        return false;
    }

    public void blockRandomPath() {
        int x = random.nextInt(width);
        int y = random.nextInt(height);
        int dir = random.nextInt(4);

        if (maze[x][y][dir]) {
            blockedPaths[x][y][dir] = true;
            int nx = x, ny = y;

            switch (dir) {
                case 0 -> ny--;
                case 1 -> nx++;
                case 2 -> ny++;
                case 3 -> nx--;
            }

            if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                blockedPaths[nx][ny][(dir + 2) % 4] = true;
            }
        }
    }

    public boolean isBlocked(int x, int y, int direction) {
        return blockedPaths[x][y][direction];
    }

    public int getTravelerX() {
        return travelerX;
    }

    public int getHeight(){
        return height;
    }

    public int getWidth(){
        return width;
    }

    public int getTravelerY() {
        return travelerY;
    }

    public boolean[][][] getMazeStructure() {
        return maze;
    }

    private boolean hasVisited(int x, int y) {
        for (int d = 0; d < 4; d++) {
            if (maze[x][y][d]) {
                return true;
            }
        }
        return false;
    }

    private void shuffleArray(int[] array) {
        for (int i = array.length - 1; i > 0; i--) {
            int index = random.nextInt(i + 1);
            int temp = array[index];
            array[index] = array[i];
            array[i] = temp;
        }
    }

    private int getDirection(int dx, int dy) {
        if (dx == 1) return 1; // Prawo
        if (dx == -1) return 3; // Lewo
        if (dy == 1) return 2; // Dół
        return 0; // Góra
    }

    public boolean isAtExit() {
        return travelerX == width - 1 && travelerY == height - 1;
    }
}


class MazePanel extends JPanel {
    private Maze maze;
    private int CELL_SIZE; //= 50;
    private Image travelerImage;
    private boolean markFields;
    private Color backgroundColor = Color.WHITE;
    private Color wallColor = Color.BLACK;

    public MazePanel(Maze maze) {
        this.maze = maze;
        loadTravelerImage();
    }

    private void getCellSize() {
        int panelWidth = getWidth();
        int panelHeight = getHeight();
        int mazeWidth = maze.getMazeStructure().length;
        int mazeHeight = maze.getMazeStructure()[0].length;

        CELL_SIZE =  Math.min(panelWidth / mazeWidth, panelHeight / mazeHeight);
    }

    private void loadTravelerImage() {
        String filename = "Player.jpg";
        ImageIcon podroznik = new ImageIcon(filename);
        travelerImage = podroznik.getImage();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(backgroundColor);
        g.fillRect(0, 0, getWidth(), getHeight());
        drawMaze(g);
        drawTraveler(g);
    }

    public void setTravelerPosition(int x, int y) {
        maze.moveTraveler(x - maze.getTravelerX(), y - maze.getTravelerY());
        repaint();
    }

    public void setMarkFields(boolean markFields){
        this.markFields = markFields;
        repaint();
    }

    public void setBackgroundColor(Color color) {
        backgroundColor = color;
        repaint();
    }

    public void setWallColor(Color color) {
        wallColor = color;
        repaint();
    }

    public void setMaze(Maze maze) {
        this.maze = maze;
        repaint();
    }

    private void drawMaze(Graphics g) {
        boolean[][][] structure = maze.getMazeStructure();
        int width = structure.length;
        int height = structure[0].length;
        getCellSize();

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int xPos = x * CELL_SIZE;
                int yPos = y * CELL_SIZE;

                if (markFields) {
                    g.setColor(Color.GRAY);
                    g.drawString(String.valueOf((char) ('A' + y)), xPos + CELL_SIZE / 4, yPos + CELL_SIZE / 4); // Wiersze
                    g.drawString(String.valueOf(x + 1), xPos + 2 * CELL_SIZE / 4, yPos + CELL_SIZE / 4); // Kolumny
                }

                // Rysowanie ścian
                if (!structure[x][y][0]) { // Góra
                    g.setColor(wallColor);
                    g.drawLine(xPos, yPos, xPos + CELL_SIZE, yPos);
                } else if (maze.isBlocked(x, y, 0)) { // Zamurowane przez Ducha
                    g.setColor(Color.RED);
                    g.drawLine(xPos, yPos, xPos + CELL_SIZE, yPos);
                }

                if (!structure[x][y][1]) { // Prawo
                    g.setColor(wallColor);
                    g.drawLine(xPos + CELL_SIZE, yPos, xPos + CELL_SIZE, yPos + CELL_SIZE);
                } else if (maze.isBlocked(x, y, 1)) {
                    g.setColor(Color.RED);
                    g.drawLine(xPos + CELL_SIZE, yPos, xPos + CELL_SIZE, yPos + CELL_SIZE);
                }

                if (!structure[x][y][2]) { // Dół
                    g.setColor(wallColor);
                    g.drawLine(xPos, yPos + CELL_SIZE, xPos + CELL_SIZE, yPos + CELL_SIZE);
                } else if (maze.isBlocked(x, y, 2)) {
                    g.setColor(Color.RED);
                    g.drawLine(xPos, yPos + CELL_SIZE, xPos + CELL_SIZE, yPos + CELL_SIZE);
                }

                if (!structure[x][y][3]) { // Lewo
                    g.setColor(wallColor);
                    g.drawLine(xPos, yPos, xPos, yPos + CELL_SIZE);
                } else if (maze.isBlocked(x, y, 3)) {
                    g.setColor(Color.RED);
                    g.drawLine(xPos, yPos, xPos, yPos + CELL_SIZE);
                }
            }
        }
    }

    private void drawTraveler(Graphics g) {
        int x = maze.getTravelerX();
        int y = maze.getTravelerY();

        int xPos = x * CELL_SIZE;
        int yPos = y * CELL_SIZE;

        g.drawImage(travelerImage, xPos + 5, yPos + 5, CELL_SIZE - 10, CELL_SIZE - 10, this);
    }
}
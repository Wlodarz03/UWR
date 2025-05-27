'''
WERSJA Z PONOWNYM GENEROWANIEM OBRAZKA POCZĄTKOWEGO PO MAX_ITERATIONS
Generuje randomowy obrazek (random 0 i 1 na każdej współrzędnej)
Robię tak jak w treści - losuje wiersz lub kolumne, jeżeli wylosuje wiersz a wszystkie wiersze są ok
to zamieniam że mój wybór to kolumna (i analogicznie na odwrót). Losuje który wiersz/kolumne dopóki
nie wylosuje wiersza/kolumny który/a nie spełnia wymagań nonogramu.
Teraz korzystam z poprzedniego zadania (sprawdzanie minimum kroków do stworzenia dobrej linii)
do oceny który piksel na wierszu/kolumnie najbardziej opłaca mi się zamienić,
ostatecznie zmieniam piksel (i, j), który najbardziej zmniejsza mi ilość kroków do przejścia do dobrego
wiersza i oraz kolumny j. Robię tak dopóki nie otrzymam poprawnego obrazka.
'''
import random
import math

with open('zad5_input.txt', 'r') as file:
    input_lines = [line.split(' ') for line in file]

rows_len = int(input_lines[0][0])
cols_len = int(input_lines[0][1])
rows = []
cols = []

for i in range(1, len(input_lines)):
    if i <= rows_len:
        rows.append(int(input_lines[i][0]))
    else:
        cols.append(int(input_lines[i][0]))

MAX_ITERATIONS = 5000

# Funkcja generująca obrazek początkowy
def generate_board(rows_len, cols_len):
    return [[random.randint(0, 1) for _ in range(cols_len)] for _ in range(rows_len)]

# Funkcja sprawdza czy w linii jest jeden blok o odpowiedniej długości
def if_one_block(line, target):
    count = 0
    blocks = []
    for i in range(len(line)):
        if line[i] == 1:
            count += 1
        else:
            if count != 0:
                blocks.append(count)
            count = 0
    if count != 0:
        blocks.append(count)
    return len(blocks) == 1 and blocks[0] == target

# Funkcja sprawdzająca czy board już jest poprawny
def is_board_ok(board, correct_rows, correct_cols):

    for i in range(len(correct_rows)):
        if not if_one_block(board[i], correct_rows[i]):
            return False
    
    for j in range(len(correct_cols)):
        col = [board[i][j] for i in range(len(correct_rows))]
        if not if_one_block(col, correct_cols[j]):
            return False
    
    return True

# Sprawdzenie tylko wierszy
def are_rows_ok(board, correct_rows):
    for i in range(len(correct_rows)):
        if not if_one_block(board[i], correct_rows[i]):
            return False
    return True

# Sprawdzanie tylko kolumn
def are_cols_ok(board, correct_rows, correct_cols):
    for j in range(len(correct_cols)):
        col = [board[i][j] for i in range(len(correct_rows))]
        if not if_one_block(col, correct_cols[j]):
            return False
    return True

# Funkcja pomocnicza do opt_dist (sprawdza minimum ilość ruchów z przejścia od inputu do targeta)
def min_moves(input, target):
    moves = 0
    for i in range(len(input)):
        if input[i] != target[i]:
            moves += 1
    return moves

# Zwraca minimum liczbę ruchów z przejścia od listy do linii, która ma czarny blok długości d
def opt_dist(list, d):
    list = [int(el) for el in list]
    possibilities = len(list) - d + 1
    minimum = math.inf
    for i in range(possibilities):
        target = [0 for _ in range(len(list))]
        for j in range(i, i+d):
            target[j] = 1
        min = min_moves(list, target)
        if min < minimum:
            minimum = min
    return minimum

# Funkcja do zmiany koloru na współrzędnych i,j
def swap_pixel(board, i, j):
    if board[i][j] == 1:
        board[i][j] = 0
    else:
        board[i][j] = 1

# Funkcja do rysowania boarda
def draw_board_to_file(board, rows, cols, filename="zad5_output.txt"):
    with open(filename, "w") as file:
        for i in range(rows):
            for j in range(cols):
                if board[i][j] == 1:
                    file.write("#")
                else:
                    file.write(".")
            file.write("\n")

def nonogram(correct_rows, correct_cols):
    rows = len(correct_rows)
    cols = len(correct_cols)
    board = generate_board(rows, cols)

    iteration = 0
    while True:
        # if k == MAX_ITERATIONS - 1:
        #     draw_board_to_file(board, rows, cols)
        if iteration >= MAX_ITERATIONS:
            board = generate_board(rows, cols)
        iteration += 1
        if is_board_ok(board, correct_rows, correct_cols):
            return board
        row_or_col = random.choice(["row", "col"])

        if row_or_col == "row":
            if are_rows_ok(board, correct_rows):
                row_or_col = "col"
        elif are_cols_ok(board, correct_rows, correct_cols):
            row_or_col = "row"

        if row_or_col == "row":
            row = random.randint(0, rows - 1)
            target = correct_rows[row]
            # Dopóki wybieramy poprawny wiersz to losujemy dalej
            while (if_one_block(board[row], target)):
                row = random.randint(0, rows - 1)
                target = correct_rows[row]
            best_j = -1
            min_moves = math.inf
            for j in range(cols):
                swap_pixel(board, row, j)
                new_opt_rows = opt_dist(board[row], correct_rows[row])
                new_opt_cols = opt_dist([board[i][j] for i in range(rows)], correct_cols[j])
                if min_moves >= new_opt_cols + new_opt_rows:
                    min_moves = new_opt_cols + new_opt_rows
                    best_j = j
                swap_pixel(board, row, j)
            swap_pixel(board, row, best_j)
        else:
            col = random.randint(0, cols - 1)
            target = correct_cols[col]
            # Dopóki wybieram poprawną kolumnę losuje dalej
            while (if_one_block([board[i][col] for i in range(rows)], target)):
                col = random.randint(0, cols -1)
                target = correct_cols[col]
            best_i = -1
            min_moves = math.inf
            for i in range(rows):
                swap_pixel(board, i, col)
                col_line = [board[i][col] for i in range(rows)]
                new_opt_rows = opt_dist(board[i], correct_rows[i])
                new_opt_cols = opt_dist(col_line, correct_cols[col])
                if min_moves >= new_opt_rows + new_opt_cols:
                    min_moves = new_opt_rows + new_opt_cols
                    best_i = i
                swap_pixel(board, i, col)
            swap_pixel(board, best_i, col)
    return None

result = nonogram(rows, cols)
if result:
    draw_board_to_file(result, len(rows), len(cols))
else:
    print("Nie udało się")
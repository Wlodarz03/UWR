import random
import math
import itertools

with open('zad_input.txt', 'r') as file:
    input_lines = [line.split(' ') for line in file]

rows_len = int(input_lines[0][0])
cols_len = int(input_lines[0][1])
rows = []
cols = []

for i in range(1, len(input_lines)):
    if i <= rows_len:
        row = []
        for j in range(len(input_lines[i])):
            row.append(int(input_lines[i][j]))
        rows.append(row)
    else:
        col = []
        for j in range(len(input_lines[i])):
            col.append(int(input_lines[i][j]))
        cols.append(col)

MAX_ITERATIONS = 10000


def generate_board(rows_len, cols_len):
    return [[random.randint(0, 1) for _ in range(cols_len)] for _ in range(rows_len)]

# Funkcja sprawdza czy w linii są bloki zgodne z targetem
def if_line_match(line, target):
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
    return blocks == target


# # Funkcja sprawdzająca czy board już jest poprawny
def is_board_ok(board, correct_rows, correct_cols):

    for i in range(len(correct_rows)):
        if not if_line_match(board[i], correct_rows[i]):
            return False
    
    for j in range(len(correct_cols)):
        col = [board[i][j] for i in range(len(correct_rows))]
        if not if_line_match(col, correct_cols[j]):
            return False
    
    return True

# Sprawdzenie tylko wierszy
def are_rows_ok(board, correct_rows):
    for i in range(len(correct_rows)):
        if not if_line_match(board[i], correct_rows[i]):
            return False
    return True

# Sprawdzanie tylko kolumn
def are_cols_ok(board, correct_rows, correct_cols):
    for j in range(len(correct_cols)):
        col = [board[i][j] for i in range(len(correct_rows))]
        if not if_line_match(col, correct_cols[j]):
            return False
    return True

# Funkcja pomocnicza do opt_dist (sprawdza minimum ilość ruchów z przejścia od inputu do targeta)
def min_moves(input, target):
    moves = 0
    for i in range(len(input)):
        if input[i] != target[i]:
            moves += 1
    return moves

# =================================================================================================

def generate_possibilities(length, blocks):
    if not blocks:
        return [0] * length
    
    total = sum(blocks)
    n = len(blocks)
    min_spaces = n - 1
    free = length - total - min_spaces
    
    if free < 0:
        return []
    
    patterns = []
    for spaces in itertools.product(range(free + 1), repeat=n + 1):
        if sum(spaces) != free:
            continue
        
        line = [0] * length
        pos = spaces[0]
        for i, block in enumerate(blocks):
            for k in range(block):
                if pos + k >= length:
                    break
                line[pos + k] = 1
            pos += block + (1 if i < n-1 else 0) + spaces[i+1]
        
        patterns.append(line)
    
    return patterns

def pre_generate(row_len, col_len, correct_rows, correct_cols):
    rows_targets = [generate_possibilities(row_len, blocks) for blocks in correct_rows]
    cols_targets = [generate_possibilities(col_len, blocks) for blocks in correct_cols]
    return rows_targets, cols_targets

# Zwraca minimum liczbę ruchów z przejścia od linii do oczekiwanej linii
def opt_dist(line, targets):
    line = [int(el) for el in line]
    best_moves = float('inf')
    
    for target in targets:
        moves = min_moves(line, target)
        best_moves = min(best_moves, moves)
    
    return best_moves

# =================================================================================================

# Funkcja do zmiany koloru na współrzędnych i,j
def swap_pixel(board, i, j):
    if board[i][j] == 1:
        board[i][j] = 0
    else:
        board[i][j] = 1

# Funkcja do rysowania boarda
def draw_board_to_file(board, rows, cols, filename="zad_output.txt"):
    with open(filename, "w") as file:
        for i in range(rows):
            for j in range(cols):
                if board[i][j] == 1:
                    file.write("#")
                else:
                    file.write(".")
            file.write("\n")

def nonogram(correct_rows, correct_cols):
    random.seed(0)
    rows = len(correct_rows)
    cols = len(correct_cols)
    board = generate_board(rows, cols)
    rows_targets, cols_targets = pre_generate(cols, rows, correct_rows, correct_cols)

    iteration = 0
    while True:
        # if k == MAX_ITERATIONS - 1:
        #     draw_board_to_file(board, rows, cols)
        if iteration >= MAX_ITERATIONS:
            iteration = 0
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
            while (if_line_match(board[row], target)):
                row = random.randint(0, rows - 1)
                target = correct_rows[row]
            best_j = -1
            min_moves = math.inf
            for j in range(cols):
                swap_pixel(board, row, j)
                new_opt_rows = opt_dist(board[row], rows_targets[row])
                new_opt_cols = opt_dist([board[i][j] for i in range(rows)], cols_targets[j])
                if min_moves >= new_opt_cols + new_opt_rows:
                    min_moves = new_opt_cols + new_opt_rows
                    best_j = j
                swap_pixel(board, row, j)
            swap_pixel(board, row, best_j)
        else:
            col = random.randint(0, cols - 1)
            target = correct_cols[col]
            # Dopóki wybieram poprawną kolumnę losuje dalej
            while (if_line_match([board[i][col] for i in range(rows)], target)):
                col = random.randint(0, cols -1)
                target = correct_cols[col]
            best_i = -1
            min_moves = math.inf
            for i in range(rows):
                swap_pixel(board, i, col)
                col_line = [board[i][col] for i in range(rows)]
                new_opt_rows = opt_dist(board[i], rows_targets[i])
                new_opt_cols = opt_dist(col_line, cols_targets[col])
                if min_moves >= new_opt_rows + new_opt_cols:
                    min_moves = new_opt_rows + new_opt_cols
                    best_i = i
                swap_pixel(board, i, col)
            swap_pixel(board, best_i, col)
    return None

result = nonogram(rows, cols)
if result:
    draw_board_to_file(result, len(rows), len(cols))
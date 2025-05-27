import itertools

def main():
    with open('zad_input.txt', 'r') as f:
        lines = f.readlines()
    
    rows, cols = map(int, lines[0].split())
    row_hints = [list(map(int, line.split())) for line in lines[1 : rows + 1]]
    col_hints = [list(map(int, line.split())) for line in lines[rows + 1 : rows + cols + 1]]

    solution = solve_nonogram(rows, cols, row_hints, col_hints)
    
    with open('zad_output.txt', 'w') as f:
        for row in solution:
            f.write(''.join(['#' if x else '.' for x in row]) + '\n')

def solve_nonogram(rows, cols, row_hints, col_hints):
    row_possibilities = [generate_possibilities(cols, hint) for hint in row_hints]
    col_possibilities = [generate_possibilities(rows, hint) for hint in col_hints]

    solution = [[None for _ in range(cols)] for _ in range(rows)]
    
    while any(None in row for row in solution):
        
        for i in range(rows):
            if None not in solution[i]:
                continue
                
            filtered = []
            for pattern in row_possibilities[i]:
                match = True
                for j in range(cols):
                    if solution[i][j] is not None and pattern[j] != solution[i][j]:
                        match = False
                        break
                if match:
                    filtered.append(pattern)
            
            row_possibilities[i] = filtered
            
            # Znajdujemy wspólne wartości dla każdej kolumny
            for j in range(cols):
                if solution[i][j] is not None:
                    continue
                    
                all_same = True
                val = row_possibilities[i][0][j]
                for pattern in row_possibilities[i][1:]:
                    if pattern[j] != val:
                        all_same = False
                        break
                
                if all_same:
                    solution[i][j] = val
        
        for j in range(cols):
            if all(solution[i][j] is not None for i in range(rows)):
                continue
                
            filtered = []
            for pattern in col_possibilities[j]:
                match = True
                for i in range(rows):
                    if solution[i][j] is not None and pattern[i] != solution[i][j]:
                        match = False
                        break
                if match:
                    filtered.append(pattern)
            
            col_possibilities[j] = filtered
            
            for i in range(rows):
                if solution[i][j] is not None:
                    continue
                    
                all_same = True
                val = col_possibilities[j][0][i]
                for pattern in col_possibilities[j][1:]:
                    if pattern[i] != val:
                        all_same = False
                        break
                
                if all_same:
                    solution[i][j] = val
    
    return solution

def generate_possibilities(length, blocks):
    if not blocks:
        return [[False]*length]
    
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
        
        line = [False]*length
        pos = spaces[0]
        for i, block in enumerate(blocks):
            for k in range(block):
                if pos + k >= length:
                    break
                line[pos + k] = True
            pos += block + (1 if i < n-1 else 0) + spaces[i+1]
        
        patterns.append(line)
    
    return patterns

if __name__ == '__main__':
    main()
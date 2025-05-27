"""
Używam BFS-a do znajdowania najmniejszej ilości ruchów do zmatowania czarnego króla.
BFS gwarantuje mi minimum, ponieważ idzie po poziomach (ruchac) i sprawdza najpierw czy w danym poziomie był możliwy mat.
Czyli najpierw sprawdza wszystkie możliwości z 1 ruchem, potem 2 ruchami itd.

Dodatkowo mam kilka funkcji, które zwracają możliwe ruchy każdej figury (get_rook_moves, get_bk_moves, get_wk_moves)
Wieża - pionowo lub poziomo w obrębie planszy, ale nie przeskakuje nad królami
Król biały - o ile danego pola nie chroni czarny król lub nie stoi na nim wieża to może tam iść
Król czarny - podobnie jak biały tylko musi uważać jeszcze na pole bronione przez wieże 
(jeżeli wieża stoi obok i nie jest chroniona to zbicie jej jest legalnym ruchem i nie ma wtedy mata,
natomiast zbicie wieży prowadzi do pata a tego nie chcemy bo mając 3 figury mat jest osiągalny)

Do tego stworzyłem kilka pomocniczych funkcji takich jak:
is_bk_checked() - jak czarny król nie ma już możliwych ruchów to sprawdzamy czy jest on szachowany (jak tak to mamy mata, jak nie to jest to pat)
is_rook_protected() - sprawdza czy obok wieży stoi jej król (do uwzględnienia tego legalnego ruchu)
is_mate() - sprawdza czy doszło do mata

No i ostatecznie funkcja min_moves_to_mate() - która BFS-em szuka minimalnej ilości ruchów do mata
Do każdego możliwego ruchu danej figury (w zależności od tury może być to czarny król lub dwa białe figury)
do kolejki dodawana jest krotka z kolejnym "stanem" gry (rozłożeniem pionków + tura + poprzedni stan).
Poprzedni stan jest do odtworzenia ruchów od startu do mata"
"""

from collections import deque


KING_MOVES = [(-1, 0), (1, 0), (0, -1), (0, 1),
              (-1, -1), (-1, 1), (1, -1), (1, 1)]

convert = ['a', 'b', 'c', 'd', 'e', 'f', 'g','h'] # do zamiany na indeksy przy użyciu .index()

with open('zad1_input.txt', 'r') as file:
    input_lines = [line.strip() for line in file]
# chess - tura | wk | r | bk
chess = []
for line in input_lines:
    chess.append(line.split())
for i,s in enumerate(chess):
    chess[i][1] = (convert.index(s[1][0]), int(s[1][1]) - 1)
    chess[i][2] = (convert.index(s[2][0]), int(s[2][1]) - 1)
    chess[i][3] = (convert.index(s[3][0]), int(s[3][1]) - 1)

def get_rook_moves(rx, ry, wkx, wky, bkx, bky):
    moves = []
    # Sprawdzamy cztery kierunki (lewo, prawo, góra, dół)
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        x, y = rx, ry
        while 0 <= x + dx < 8 and 0 <= y + dy < 8:  # Dopóki jesteśmy na planszy
            x += dx
            y += dy
            if (x, y) in [(wkx, wky), (bkx, bky)]:  # Jeśli spotykamy króla, zatrzymujemy się
                break
            moves.append((x, y))
    return moves

def is_rook_protected(wkx, wky, rx, ry):
    # Sprawdzam czy obok wieży (czyli jakbym patrzył na ruchy króla) stoi król
    return any((rx + dx, ry + dy) == (wkx, wky) for dx, dy in KING_MOVES)

def get_bk_moves(wkx, wky, rx, ry, bkx, bky):
    moves = []
    rook_moves = get_rook_moves(rx, ry, wkx, wky, bkx, bky)
    for dx, dy in KING_MOVES:
        new_bkx, new_bky = bkx + dx, bky + dy
        if (0 <= new_bkx < 8 and 0 <= new_bky < 8  # czy na szachownicy
            and not (abs(new_bkx - wkx) <= 1 and abs(new_bky - wky) <= 1) # czy pozycji nie chroni biały król lub na niej stoi
            and (new_bkx, new_bky) not in rook_moves): # czy pozycja nie jest chroniona przez wieże

            # czy jak obok jest wieża to czy zbicie jej jest legalnym ruchem
            if new_bkx == rx and new_bky == ry:
                if not is_rook_protected(wkx, wky, rx, ry):
                    moves.append((new_bkx, new_bky))
            elif new_bkx != rx and new_bky != ry:
                moves.append((new_bkx, new_bky)) 
    return moves

def get_wk_moves( wkx, wky, rx, ry, bkx, bky):
    moves = []
    for dx, dy in KING_MOVES:
        new_kx, new_ky = wkx + dx, wky + dy
        # czy może być na szachownicy, czy na tej pozycji nie stoi wieża, czy pozycja nie jest chroniona przez czarnego króla lub sam na niej stoi
        if 0 <= new_kx < 8 and 0 <= new_ky < 8 and (new_kx, new_ky) != (rx, ry) and not (abs(new_kx - bkx) <= 1 and abs(new_ky - bky) <= 1):
            moves.append((new_kx, new_ky))
    return moves

def is_bk_checked(wkx, wky, rx, ry, bkx, bky):
    if bkx == rx or bky == ry:  # czy wieża szachuje króla
        # czy między nimi nie ma króla białego
        if not (wkx == bkx and min(bky, ry) < wky < max(bky, ry)) and not (wky == bky and min(bkx, rx) < wkx < max(bkx, rx)):
            return True
    return False

def is_mate(wkx, wky, rx, ry, bkx, bky):
    bk_moves = get_bk_moves(wkx, wky, rx, ry, bkx, bky)
    if bk_moves:
        return False
    return is_bk_checked(wkx, wky, rx, ry, bkx, bky)

# BFS do minimalnej liczby ruchów do mata
def min_moves_to_mate(wkx, wky, rx, ry, bkx, bky, turn):
    queue = deque([(wkx, wky, rx, ry, bkx, bky, turn, 0, [])])
    visited = set()
    
    while queue:
        wkx, wky, rx, ry, bkx, bky, turn, moves, path = queue.popleft()

        # czy to już mat
        if is_mate(wkx, wky, rx, ry, bkx, bky) and turn == "black":
            return  moves, path + [(wkx, wky, rx, ry, bkx, bky, "black")]

        # jeżeliśmy już byliśmy w takim "stanie" gry to pomijamy dalsze szukanie
        if (wkx, wky, rx, ry, bkx, bky, turn) in visited:
            continue
        visited.add((wkx, wky, rx, ry, bkx, bky, turn))

        if turn == "white":
            # Ruchy wieży
            for new_rx, new_ry in get_rook_moves(rx, ry, wkx, wky, bkx, bky):
                queue.append((wkx, wky, new_rx, new_ry, bkx, bky, "black", moves + 1, path + [(wkx, wky, rx, ry, bkx, bky, turn)]))
            
            # Ruchy białego króla
            for new_kx, new_ky in get_wk_moves(wkx, wky, rx, ry, bkx, bky):
                queue.append((new_kx, new_ky, rx, ry, bkx, bky, "black", moves + 1, path + [(wkx, wky, rx, ry, bkx, bky, turn)]))
        
        else: 
            # Ruchy czarnego króla
            bk_moves = get_bk_moves(wkx, wky, rx, ry, bkx, bky)
            if (rx, ry) in bk_moves:
                bk_moves.remove((rx, ry))
            for new_bkx, new_bky in bk_moves:
                queue.append((wkx, wky, rx, ry, new_bkx, new_bky, "white", moves + 1, path + [(wkx, wky, rx, ry, bkx, bky, turn)]))
    return "INF", None

#------------------------------------------------------------------------------------------
def draw(path):
    for state in path:
        print("TURA: " + state[6])
        for i in range(8):
            for j in range(8):
                if j == state[0] and 7-i == state[1]:
                    print("W", end = "")
                elif j == state[2] and 7-i == state[3]:
                    print("R", end = "")
                elif j == state[4] and 7-i == state[5]:
                    print("B", end = "")
                else:
                    print("*", end = "")
            print()

def main():
    f = open("zad1_output.txt", "w")
    for start in chess:
        wk = start[1]
        r = start[2]
        bk = start[3]
        result, path = min_moves_to_mate(wk[0], wk[1], r[0], r[1], bk[0], bk[1], start[0])
        f.write(str(result) + "\n")
        # print("\n-----------------\n")
        # draw(path)
    f.close()
    
main()
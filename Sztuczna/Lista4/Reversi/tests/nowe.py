import random
import copy

DIRECTIONS = [(-1, -1), (-1, 0), (-1, 1),
              (0, -1),         (0, 1),
              (1, -1), (1, 0), (1, 1)]

class Reversi:
    def __init__(self):
        self.M = 8
        self.board = [[None for _ in range(self.M)] for _ in range(self.M)]
        self.board[3][3] = self.board[4][4] = 1
        self.board[3][4] = self.board[4][3] = 0
        self.fields = set()
        self.move_list = []

        for y in range(8):
            for x in range(8):
                if self.board[y][x] is None:
                    self.fields.add((x, y))

    def is_on_board(self, x, y):
        return 0 <= x < 8 and 0 <= y < 8
    
    def moves(self, player):
        res = []
        for (x, y) in self.fields:
            if any(self.can_beat(x, y, direction, player)
                   for direction in DIRECTIONS):
                res.append((x, y))
        return res

    def can_beat(self, x, y, d, player):
        dx, dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x, y) == 1 - player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x, y) == player

    def get(self, x, y):
        if 0 <= x < self.M and 0 <= y < self.M:
            return self.board[y][x]
        return None

    def do_move(self, move, player):
        self.move_list.append(move)

        if move is None:
            return
        x, y = move
        x0, y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx, dy in DIRECTIONS:
            x, y = x0, y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x, y) == 1 - player:
                to_beat.append((x, y))
                x += dx
                y += dy
            if self.get(x, y) == player:
                for (nx, ny) in to_beat:
                    self.board[ny][nx] = player

    def result(self):
        res = 0
        for y in range(self.M):
            for x in range(self.M):
                b = self.board[y][x]
                if b == 0:
                    res += 1
                elif b == 1:
                    res -= 1
        return res

    def terminal(self):
        if not self.fields:
            return True
        if not any(self.moves(0)) and not any(self.moves(1)):
            return True
        return False
    
class RandomAgent:
    def __init__(self, player):
        self.player = player

    def move(self, game):
        moves = game.moves(self.player)
        if moves:
            return random.choice(moves)
        return None
    
# Cache dla funkcji ewaluacji
EVAL_CACHE = {}

# Wagi dla różnych pozycji na planszy
WEIGHTS = [
    [120, -20, 20, 5, 5, 20, -20, 120],
    [-20, -40, -5, -5, -5, -5, -40, -20],
    [20, -5, 15, 3, 3, 15, -5, 20],
    [5, -5, 3, 3, 3, 3, -5, 5],
    [5, -5, 3, 3, 3, 3, -5, 5],
    [20, -5, 15, 3, 3, 15, -5, 20],
    [-20, -40, -5, -5, -5, -5, -40, -20],
    [120, -20, 20, 5, 5, 20, -20, 120]
]

corners = [(0,0), (0,7), (7,0), (7,7)]

class MinimaxAgent:
    def __init__(self, player, depth):
        self.player = player
        self.depth = depth
        self.opponent = 1 - player
    
    # def evaluate(self, game):
    #     return game.result()

    def evaluate(self, game):
        # Klucz cache - krotka z krotkami reprezentującymi planszę i gracza
        board_tuple = tuple(tuple(row) for row in game.board)
        cache_key = (board_tuple, self.player)
        
        if cache_key in EVAL_CACHE:
            return EVAL_CACHE[cache_key]
        
        score = 0
        for y in range(game.M):
            for x in range(game.M):
                if game.board[y][x] == self.player:
                    score += WEIGHTS[y][x]
                elif game.board[y][x] == 1 - self.player:
                    score -= WEIGHTS[y][x]
        
        # Dodatkowe czynniki
        my_moves = len(game.moves(self.player))
        opp_moves = len(game.moves(1 - self.player))
        score += (my_moves - opp_moves) * 10
        
        # Premia za rogi
        for (x, y) in corners:
            if game.board[y][x] == self.player:
                score += 50
            elif game.board[y][x] == 1 - self.player:
                score -= 50
        
        EVAL_CACHE[cache_key] = score
        return score
    
    def minimax(self, game, alfa, beta, depth, maximizing_player):

        if depth == 0 or game.terminal():
            return self.evaluate(game), None
        
        moves = game.moves(self.player if maximizing_player else self.opponent)
        if not moves:
            return self.evaluate(game), None
        
        # Lepsze sortowanie ruchów - najpierw rogi, potem krawędzie
        def move_priority(move):
            x, y = move
            if (x, y) in [(0, 0), (0, 7), (7, 0), (7, 7)]:  # Rogi
                return 3
            elif x == 0 or x == 7 or y == 0 or y == 7:  # Krawędzie
                return 2
            elif (x in {1, 6} and y in {1, 6}):  # Niebezpieczne pola przy rogach
                return 0
            else:  # Pozostałe pola
                return 1

        moves.sort(key=move_priority, reverse=True)
        
        best_move = None
        if maximizing_player:
            max_eval = float('-inf')
            for move in game.moves(self.player):
                game_copy = copy.deepcopy(game)
                game_copy.do_move(move, self.player)
                eval, _ = self.minimax(game_copy, alfa, beta, depth - 1, False)
                if eval > max_eval:
                    max_eval = eval
                    best_move = move
                alfa = max(alfa, eval)
                if beta <= alfa:
                    break
            return max_eval, best_move
        else:
            min_eval = float('inf')
            for move in game.moves(self.opponent):
                game_copy = copy.deepcopy(game)
                game_copy.do_move(move, self.opponent)
                eval, _ = self.minimax(game_copy, alfa, beta, depth - 1, True)
                if eval < min_eval:
                    min_eval = eval
                    best_move = move
                beta = min(beta, eval)
                if beta <= alfa:
                    break
            return min_eval, best_move
        
    def move(self, game):
        _, best_move = self.minimax(game, float('-inf'), float('inf'), self.depth, True)
        return best_move
    
def play_game():
    game = Reversi()
    minimax = MinimaxAgent(0, 2)
    random_agent = RandomAgent(1)
    current_player = 0
    winner = None
    while winner is None:
        if current_player == 0:
            move = minimax.move(game)
        else:
            move = random_agent.move(game)

        if move:
            game.do_move(move, current_player)

        if game.terminal():
            if game.result() > 0:
                winner = 0
            elif game.result() < 0:
                winner = 1
            else:
                winner = -1
        current_player = 1 - current_player

    return winner

if __name__ == "__main__":
    wins = 0
    losses = 0
    draws = 0
    for i in range(1000):
        winner = play_game()
        if winner == 0:
            wins +=1
            print("Minimax wins!")
        elif winner == 1:
            losses += 1
            print("Random agent wins!")
        else:
            draws += 1
            print("It's a draw!")
    print("P0 wins:", wins, " draws:", draws, " losses:", losses)
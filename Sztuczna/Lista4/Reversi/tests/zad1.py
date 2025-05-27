#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
Losowy agent do Reversi.
'''
import sys


class Reversi:
    M = 8
    DIRS = [(0, 1), (1, 0), (-1, 0), (0, -1),
            (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def __init__(self):
        self.board = self.initial_board()
        self.fields = set()
        self.move_list = []
        self.history = []
        for i in range(self.M):
            for j in range(self.M):
                if self.board[i][j] is None:
                    self.fields.add((j, i))

    def initial_board(self):
        B = [[None] * self.M for _ in range(self.M)]
        B[3][3] = 1
        B[4][4] = 1
        B[3][4] = 0
        B[4][3] = 0
        return B

    def draw(self):
        for i in range(self.M):
            res = []
            for j in range(self.M):
                b = self.board[i][j]
                if b is None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res))
        print('')

    def moves(self, player):
        res = []
        for (x, y) in self.fields:
            if any(self.can_beat(x, y, direction, player)
                   for direction in self.DIRS):
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
        assert player == len(self.move_list) % 2
        self.history.append([x[:] for x in self.board])
        self.move_list.append(move)

        if move is None:
            return
        x, y = move
        x0, y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx, dy in self.DIRS:
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
                    res -= 1
                elif b == 1:
                    res += 1
        return res

    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] is None and self.move_list[-2] is None

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

def evaluate(game, player):
    # Klucz cache - krotka z krotkami reprezentującymi planszę i gracza
    board_tuple = tuple(tuple(row) for row in game.board)
    cache_key = (board_tuple, player)
    
    if cache_key in EVAL_CACHE:
        return EVAL_CACHE[cache_key]
    
    score = 0
    for y in range(game.M):
        for x in range(game.M):
            if game.board[y][x] == player:
                score += WEIGHTS[y][x]
            elif game.board[y][x] == 1 - player:
                score -= WEIGHTS[y][x]
    
    # Dodatkowe czynniki
    my_moves = len(game.moves(player))
    opp_moves = len(game.moves(1 - player))
    score += (my_moves - opp_moves) * 10
    
    # Premia za rogi
    for (x, y) in corners:
        if game.board[y][x] == player:
            score += 50
        elif game.board[y][x] == 1 - player:
            score -= 50
    
    EVAL_CACHE[cache_key] = score
    return score

# def evaluate(game, player):
#     score = 0
#     for y in range(game.M):
#         for x in range(game.M):
#             if game.board[y][x] == player:
#                 score += 1
#             elif game.board[y][x] == 1 - player:
#                 score -= 1
#     return score

def copy_game(game):
    new_game = Reversi()
    new_game.board = [row.copy() for row in game.board]
    new_game.fields = game.fields.copy()
    new_game.move_list = game.move_list.copy()
    new_game.history = []
    return new_game

# Tablica transpozycji
TRANSPOSITION_TABLE = {}

def minimax(game, depth, alpha, beta, maximizing_player, player):
    # Klucz transpozycji - hash planszy i gracza
    board_tuple = tuple(tuple(row) for row in game.board)
    transposition_key = (board_tuple, player, depth, maximizing_player)

    # Sprawdzenie, czy wynik dla tego stanu gry jest już w tablicy transpozycji
    if transposition_key in TRANSPOSITION_TABLE:
        return TRANSPOSITION_TABLE[transposition_key]

    if depth == 0 or game.terminal():
        eval_score = evaluate(game, player)
        TRANSPOSITION_TABLE[transposition_key] = (eval_score, None)
        return eval_score, None

    legal_moves = game.moves(player)
    if not legal_moves:
        game_copy = copy_game(game)
        game_copy.do_move(None, player)
        eval_score, _ = minimax(game_copy, depth - 1, alpha, beta, not maximizing_player, 1 - player)
        TRANSPOSITION_TABLE[transposition_key] = (eval_score, None)
        return eval_score, None

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

    legal_moves.sort(key=move_priority, reverse=True)

    best_move = None
    if maximizing_player:
        max_eval = -float('inf')
        for move in legal_moves:
            game_copy = copy_game(game)
            game_copy.do_move(move, player)
            eval_score, _ = minimax(game_copy, depth - 1, alpha, beta, False, 1 - player)
            if eval_score > max_eval:
                max_eval = eval_score
                best_move = move
            alpha = max(alpha, eval_score)
            if beta <= alpha:
                break  # Cięcie beta
        TRANSPOSITION_TABLE[transposition_key] = (max_eval, best_move)
        return max_eval, best_move
    else:
        min_eval = float('inf')
        for move in legal_moves:
            game_copy = copy_game(game)
            game_copy.do_move(move, player)
            eval_score, _ = minimax(game_copy, depth - 1, alpha, beta, True, 1 - player)
            if eval_score < min_eval:
                min_eval = eval_score
                best_move = move
            beta = min(beta, eval_score)
            if beta <= alpha:
                break  # Cięcie alfa
        TRANSPOSITION_TABLE[transposition_key] = (min_eval, best_move)
        return min_eval, best_move

class Player(object):
    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Reversi()
        self.my_player = 1
        self.say('RDY')

    def say(self, what):
        sys.stdout.write(what)
        sys.stdout.write('\n')
        sys.stdout.flush()

    def hear(self):
        line = sys.stdin.readline().split()
        return line[0], line[1:]
    
    def loop(self):
        #EVAL_CACHE.clear()  # Czyścimy cache przed nową grą
        while True:
            cmd, args = self.hear()
            if cmd == 'HEDID':
                unused_move_timeout, unused_game_timeout = args[:2]
                move = tuple((int(m) for m in args[2:]))
                if move == (-1, -1):
                    move = None
                self.game.do_move(move, 1 - self.my_player)
            elif cmd == 'ONEMORE':
                self.reset()
                #EVAL_CACHE.clear()  # Czyścimy cache przed nową grą
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                assert not self.game.move_list
                self.my_player = 0

            moves = self.game.moves(self.my_player)

            if moves:
                _, move = minimax(self.game, depth=2, alpha=-float('inf'), 
                                beta=float('inf'), maximizing_player=True, 
                                player=self.my_player)
                self.game.do_move(move, self.my_player)
            else:
                self.game.do_move(None, self.my_player)
                move = (-1, -1)
            self.say('IDO %d %d' % move)

    # def loop(self):
    #     while True:
    #         cmd, args = self.hear()
    #         if cmd == 'HEDID':
    #             unused_move_timeout, unused_game_timeout = args[:2]
    #             move = tuple((int(m) for m in args[2:]))
    #             if move == (-1, -1):
    #                 move = None
    #             self.game.do_move(move, 1 - self.my_player)
    #         elif cmd == 'ONEMORE':
    #             self.reset()
    #             continue
    #         elif cmd == 'BYE':
    #             break
    #         else:
    #             assert cmd == 'UGO'
    #             assert not self.game.move_list
    #             self.my_player = 0

    #         moves = self.game.moves(self.my_player)
                           
    #         if moves:
    #             _, move = minimax(self.game, depth=2, alpha=-float('inf'), beta=float('inf'), maximizing_player=True, player=self.my_player)
    #             self.game.do_move(move, self.my_player)
    #         else:
    #             self.game.do_move(None, self.my_player)
    #             move = (-1, -1)
    #         self.say('IDO %d %d' % move)

if __name__ == '__main__':
    player = Player()
    player.loop()
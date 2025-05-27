#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import random
import sys
import time

class Reversi:
    M = 8
    DIRS = [(0, 1), (1, 0), (-1, 0), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]
    
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
    
    def copy(self):
        new = Reversi()
        new.board = [row[:] for row in self.board]
        new.fields = set(self.fields)
        new.move_list = list(self.move_list)
        new.history = []
        return new

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
                continue
            elif cmd == 'BYE':
                break
            else:
                assert cmd == 'UGO'
                assert not self.game.move_list
                self.my_player = 0
            move = self.alpha_beta_search(self.game, 2, self.my_player)
            if move is not None:
                self.game.do_move(move, self.my_player)
            else:
                self.game.do_move(None, self.my_player)
                move = (-1, -1)
            self.say('IDO %d %d' % move)
        
    def alpha_beta_search(self, game, depth, player):
        start_time = time.time()
        time_limit = 0.5  # sekundy

        def alphabeta(game, depth, alpha, beta, maximizingPlayer):
            # Sprawdzenie limitu czasu
            if time.time() - start_time > time_limit:
                raise TimeoutError()

            if depth == 0 or game.terminal():
                return self.evaluate(game), None

            legal_moves = game.moves(player if maximizingPlayer else 1 - player)
            if not legal_moves:
                game_copy = game.copy()
                game_copy.do_move(None, player if maximizingPlayer else 1 - player)
                return alphabeta(game_copy, depth - 1, alpha, beta, not maximizingPlayer)[0], None

            def move_priority(move):
                x, y = move
                if (x, y) in [(0,0), (0,7), (7,0), (7,7)]: 
                    return 3
                elif x == 0 or x == 7 or y == 0 or y == 7:   
                    return 2
                elif (x in {1,6} and y in {1,6}):           
                    return 0
                else:                                   
                    return 1

            legal_moves.sort(key=move_priority, reverse=True)
            best_move = legal_moves[0]

            if maximizingPlayer:
                maxEval = -float('inf')
                for move in legal_moves:
                    child = game.copy()
                    child.do_move(move, player)
                    try:
                        eval, _ = alphabeta(child, depth - 1, alpha, beta, False)
                    except TimeoutError:
                        break
                    if eval > maxEval:
                        maxEval, best_move = eval, move
                    alpha = max(alpha, maxEval)
                    if beta <= alpha:
                        break
                return maxEval, best_move
            else:
                minEval = float('inf')
                for move in legal_moves:
                    child = game.copy()
                    child.do_move(move, 1 - player)
                    try:
                        eval, _ = alphabeta(child, depth - 1, alpha, beta, True)
                    except TimeoutError:
                        break
                    if eval < minEval:
                        minEval, best_move = eval, move
                    beta = min(beta, minEval)
                    if beta <= alpha:
                        break
                return minEval, best_move

        try:
            _, best_move = alphabeta(game, depth, -float('inf'), float('inf'), True)
        except TimeoutError:
            # fallback, jeśli limit czasu minął wcześniej
            moves = game.moves(player)
            best_move = random.choice(moves) if moves else None

        return best_move
    
    def evaluate(self, game):
        weights = [
            [100, -20, 10,  5,  5, 10, -20, 100],
            [-20, -50, -2, -2, -2, -2, -50, -20],
            [10, -2, -1, -1, -1, -1, -2, 10],
            [5, -2, -1, -1, -1, -1, -2, 5],
            [5, -2, -1, -1, -1, -1, -2, 5],
            [10, -2, -1, -1, -1, -1, -2, 10],
            [-20, -50, -2, -2, -2, -2, -50, -20],
            [100, -20, 10,  5,  5, 10, -20, 100]
        ]
        score = 0
        for y in range(8):
            for x in range(8):
                val = game.get(y, x)
                if val == self.my_player:
                    score += weights[y][x]
                elif val == 1 - self.my_player:
                    score -= weights[y][x]
        return score

if __name__ == '__main__':
    player = Player()
    player.loop()
#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys
import time
import math
import random

class Reversi:
    M = 8
    DIRS = [(0, 1), (1, 0), (-1, 0), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def __init__(self):
        self.board = self.initial_board()
        self.fields = set((j, i) for i in range(self.M) for j in range(self.M) if self.board[i][j] is None)
        self.move_list = []
        self.history = []

    def initial_board(self):
        B = [[None] * self.M for _ in range(self.M)]
        B[3][3] = 1
        B[4][4] = 1
        B[3][4] = 0
        B[4][3] = 0
        return B

    def moves(self, player):
        return [(x, y) for (x, y) in self.fields if any(self.can_beat(x, y, d, player) for d in self.DIRS)]

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
        self.history.append([row[:] for row in self.board])
        self.move_list.append(move)
        if move is None:
            return
        x, y = move
        self.board[y][x] = player
        self.fields.discard(move)
        for dx, dy in self.DIRS:
            nx, ny = x + dx, y + dy
            to_flip = []
            while self.get(nx, ny) == 1 - player:
                to_flip.append((nx, ny))
                nx += dx
                ny += dy
            if self.get(nx, ny) == player:
                for fx, fy in to_flip:
                    self.board[fy][fx] = player

    def result(self):
        return sum((1 if cell == 1 else -1 if cell == 0 else 0)
                   for row in self.board for cell in row)

    def terminal(self):
        return not self.fields or (
            len(self.move_list) >= 2 and self.move_list[-1] is None and self.move_list[-2] is None)

    def copy(self):
        new = Reversi()
        new.board = [row[:] for row in self.board]
        new.fields = set(self.fields)
        new.move_list = list(self.move_list)
        new.history = []
        return new

class MCTSNode:
    # co trzymamy w węźle MCTS
    def __init__(self, game, parent=None, move=None, player=None):
        self.game = game # stan gry
        self.parent = parent # poprzedni węzeł w drzewie
        self.move = move # jaki ruch nas doprowadził do stanu
        self.player = player # kto go wykonał
        self.children = [] # możliwe ruchy z tego stanu
        self.visits = 0 # ile razy węzeł został odwiedzony
        self.wins = 0 # ile uzyskał zwycięstw

    def expand(self, player):
        for move in self.game.moves(player):
            new_game = self.game.copy()
            new_game.do_move(move, player)
            child = MCTSNode(new_game, self, move, player)
            self.children.append(child)

    # wybiera najlepsze dziecko za pomocą UCB1
    def best_child(self, c=1.41):
        def ucb1(n):
            if n.visits == 0:
                return float('inf')
            exploit = n.wins / n.visits
            explore = c * math.sqrt(math.log(self.visits) / n.visits)
            return exploit + explore
        return max(self.children, key=ucb1)

    def simulate(self):
        sim_game = self.game.copy()
        current = len(sim_game.move_list) % 2
        while not sim_game.terminal():
            moves = sim_game.moves(current)
            if not moves:
                sim_game.do_move(None, current)
            else:
                sim_game.do_move(random.choice(moves), current)
            current = 1 - current
        return sim_game.result()

    def backpropagate(self, result):
        node = self
        while node:
            node.visits += 1
            if (result > 0 and node.player == 1) or (result < 0 and node.player == 0):
                node.wins += 1
            elif result == 0:
                node.wins += 0.5
            node = node.parent

def mcts_search(game, my_player, time_limit=0.5):
    start = time.time()
    root = MCTSNode(game.copy(), player=1 - my_player)
    root.expand(my_player)
    while time.time() - start < time_limit:
        node = root
        player = my_player
        # selection - wybór najlepszego węzła za pomocą funkcji
        while node.children:
            node = node.best_child()
            player = 1 - player
        # expansion - rozwinięcie drzewa
        if not node.game.terminal():
            node.expand(player)
            if node.children:
                node = random.choice(node.children)
                player = 1 - player
        # simulation - symulujemy losową rozgrywkę
        result = node.simulate()
        # backpropagation - wracamy, zwiększamy liczbę odwiedzin i liczbę zwycięstw
        node.backpropagate(result)
    # wybieramy najlepszy ruch
    best = max(root.children, key=lambda c: c.visits, default=None)
    return best.move if best else None

class Player:
    def __init__(self):
        self.reset()

    def reset(self):
        self.game = Reversi()
        self.my_player = 1
        self.say("RDY")

    def say(self, msg):
        sys.stdout.write(msg + "\n")
        sys.stdout.flush()

    def hear(self):
        return sys.stdin.readline().strip().split(maxsplit=1)

    def loop(self):
        while True:
            cmd, *rest = self.hear()
            args = rest[0].split() if rest else []
            if cmd == "HEDID":
                _, _, *move = args
                move = tuple(map(int, move))
                if move == (-1, -1):
                    move = None
                self.game.do_move(move, 1 - self.my_player)
            elif cmd == "ONEMORE":
                self.reset()
                continue
            elif cmd == "BYE":
                break
            else:
                assert cmd == "UGO"
                self.my_player = 0
            move = mcts_search(self.game, self.my_player, time_limit=0.5)
            if move is None:
                move = (-1, -1)
                self.game.do_move(None, self.my_player)
            else:
                self.game.do_move(move, self.my_player)
            self.say(f"IDO {move[0]} {move[1]}")

if __name__ == '__main__':
    player = Player()
    player.loop()
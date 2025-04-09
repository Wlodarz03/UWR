import heapq
from typing import Set, Tuple, Dict, FrozenSet
from collections import deque

Position = Tuple[int, int]
State = Tuple[str, Set[Position]] # (path, positions)

goals: Set[Position] = set()
walls: Set[Position] = set()
distance_map = {}

moves: Dict[str, Position] = {
    'U': (0, -1),
    'D': (0, 1),
    'L': (-1, 0),
    'R': (1, 0)
}

def move(state: State, direction: str) -> State:
    current_moves, commandos = state
    dx, dy = moves[direction]
    new_commandos = set()
    
    for (x, y) in commandos:
        new_pos = (x + dx, y + dy)
        if new_pos not in walls:
            new_commandos.add(new_pos)
        else:
            new_commandos.add((x, y))
    
    return (current_moves + direction, new_commandos)

def is_goal(commandos: Set[Position]) -> bool:
    return all(commando in goals for commando in commandos)

def move_positions(positions: Set[Position], direction: str) -> Set[Position]:
    dx, dy = moves[direction]
    new_positions = set()
    for (x, y) in positions:
        new_pos = (x+dx, y+dy)
        new_positions.add(new_pos if new_pos not in walls else (x, y))
    return new_positions

def reconstruct_path(came_from: Dict, current: FrozenSet) -> str:
    path = []
    while current in came_from:
        prev = came_from[current]
        for dir in list(moves.keys()):
            if move_positions(prev, dir) == current:
                path.append(dir)
                break
        current = prev
    return ''.join(reversed(path))

def a_star(starts: Set[Position], distance_map, stopien_n) -> str:
    open_set = []
    heapq.heappush(open_set, (heuristic(starts, distance_map, stopien_n), 0, frozenset(starts)))
    
    came_from: Dict[FrozenSet[Position], FrozenSet[Position]] = {}
    g_score: Dict[FrozenSet[Position], float] = {frozenset(starts): 0}
    
    while open_set:
        _, g, current = heapq.heappop(open_set)
        
        if all(pos in goals for pos in current):
            return reconstruct_path(came_from, current)
        
        for direction in list(moves.keys()):
            new_positions = move_positions(current, direction)
            new_g = g + 1 
            
            if frozenset(new_positions) not in g_score or new_g < g_score[frozenset(new_positions)]:
                came_from[frozenset(new_positions)] = current
                g_score[frozenset(new_positions)] = new_g
                f = new_g + heuristic(new_positions, distance_map, stopien_n)
                heapq.heappush(open_set, (f, new_g, frozenset(new_positions)))
    
    return ""


def heuristic(positions: Set[Position], distance_map, stopien_n) -> int:
    max_dist = 0
    for (x, y) in positions:
        #min_dist = min(abs(x - gx) + abs(y - gy) for (gx, gy) in goals)
        min_dist = distance_map.get((x, y))
        max_dist = max(max_dist, min_dist)
    return int(max_dist * stopien_n)

def pre_bfs():
    distance_map = {}
    queue = deque(goals)
    for goal in goals:
        distance_map[goal] = 0
    
    while queue:
        pos = queue.popleft()
        for dx, dy in moves.values():
            new_pos = (pos[0] + dx, pos[1] + dy)
            if new_pos not in walls and new_pos not in distance_map:
                distance_map[new_pos] = distance_map[pos] + 1
                queue.append(new_pos)
            elif new_pos not in walls and distance_map[new_pos] > distance_map[pos] + 1:
                distance_map[new_pos] = distance_map[pos] + 1
                queue.append(new_pos)
    return distance_map


def main():
    with open('zad_input.txt', 'r') as input_file:
        commandos = set()
        y = 0
        for line in input_file:
            line = line.strip()
            for x, char in enumerate(line):
                if char == 'G':
                    goals.add((x, y))
                elif char == '#':
                    walls.add((x, y))
                elif char == 'B':
                    commandos.add((x, y))
                    goals.add((x, y))
                elif char == 'S':
                    commandos.add((x, y))
            y += 1

    result = ""

    if len(commandos) < 3:
        best_state = ("", commandos)
        visited = set()
        queue = deque()
        queue.append(best_state)
        visited.add(frozenset(best_state[1]))
        
        while queue:
            current_moves, current_commandos = queue.popleft()
            
            if is_goal(current_commandos):
                best_state = (current_moves, current_commandos)
                break
            
            for direction in list(moves.keys()):
                new_state = move((current_moves, current_commandos), direction)
                new_key = frozenset(new_state[1])
                
                if new_key not in visited and len(new_state[0]) <= 150:
                    visited.add(new_key)
                    queue.append(new_state)
        result = best_state[0]
    else:
        distance_map = pre_bfs()
        stopien_n = 1.125

        result = a_star(commandos, distance_map, stopien_n)
    with open('zad_output.txt', 'w') as output_file:
        output_file.write(result)

main()
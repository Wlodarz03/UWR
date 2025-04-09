from collections import deque
import heapq
from typing import Set, Tuple, Dict

Position = Tuple[int, int]
State = Tuple[str, Set[Position]] # (path, positions)

goals: Set[Position] = set()
walls: Set[Position] = set()

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

    # Faza 1: Redukcja liczby stanów
    visited = set()
    start_state = ("", commandos)
    
    minimizing_heap = []
    heapq.heappush(minimizing_heap, (len(commandos), len(start_state[0]), start_state))
    
    best_state = start_state
    found = False
    
    while minimizing_heap and not found:
        _, _, current_state = heapq.heappop(minimizing_heap)
        current_moves, current_commandos = current_state
        current_key = frozenset(current_commandos)
        
        if current_key in visited:
            continue
        visited.add(current_key)
        
        if is_goal(current_commandos):
            best_state = current_state
            found = True
            break
        
        if len(current_commandos) < 3:
            best_state = current_state
            break
        
        for direction in list(moves.keys()):
            new_state = move(current_state, direction)
            new_commandos = new_state[1]
            heapq.heappush(minimizing_heap, (len(new_commandos), len(new_state[0]), new_state))
    
    # Faza 2: BFS dla znalezienia rozwiązania
    if not found:
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
    
    # Zapis rozwiązania
    with open('zad_output.txt', 'w') as output_file:
        output_file.write((best_state[0]))

main()
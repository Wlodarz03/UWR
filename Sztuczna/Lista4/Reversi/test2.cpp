#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <limits>
#include <optional>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <set>

using namespace std;

const int BOARD_SIZE = 8;
// const int WEIGHTS[8][8] = {
//     {120, -20, 20, 5, 5, 20, -20, 120},
//     {-20, -40, -5, -5, -5, -5, -40, -20},
//     {20, -5, 15, 3, 3, 15, -5, 20},
//     {5, -5, 3, 3, 3, 3, -5, 5},
//     {5, -5, 3, 3, 3, 3, -5, 5},
//     {20, -5, 15, 3, 3, 15, -5, 20},
//     {-20, -40, -5, -5, -5, -5, -40, -20},
//     {120, -20, 20, 5, 5, 20, -20, 120}
// };

const int WEIGHTS[8][8] = {
    {120, 100, 100, 100, 100, 100, 100, 120},
    {100, -40, -5, -5, -5, -5, -40, 100},
    {100, -5, 15, 3, 3, 15, -5, 100},
    {100, -5, 3, 3, 3, 3, -5, 100},
    {100, -5, 3, 3, 3, 3, -5, 100},
    {100, -5, 15, 3, 3, 15, -5, 100},
    {100, -40, -5, -5, -5, -5, -40, 100},
    {120, 100, 100, 100, 100, 100, 100, 120}
};

const vector<pair<int, int>> corners = {{0,0}, {0,7}, {7,0}, {7,7}};
const vector<pair<int, int>> dirs = {
    {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}
};

std::unordered_map<unsigned long, std::pair<int, std::optional<std::pair<int, int>>>> TRANSPOSITION_TABLE;

class Reversi {
public:
    vector<vector<int>> board;
    set<pair<int, int>> fields;
    vector<optional<pair<int, int>>> move_list;

    Reversi() {
        board = vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE, -1));
        board[3][3] = board[4][4] = 1;
        board[3][4] = board[4][3] = 0;
        for (int y = 0; y < BOARD_SIZE; ++y)
            for (int x = 0; x < BOARD_SIZE; ++x)
                if (board[y][x] == -1)
                    fields.insert({x, y});
    }

    int get(int x, int y) const {
        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
            return board[y][x];
        return -2;
    }

    bool can_play(int x, int y, int player) const {
        if (board[y][x] != -1) return false;
        
        const int opponent = 1 - player;
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (get(nx, ny) != opponent) continue;
            
            nx += dx;
            ny += dy;
            while (get(nx, ny) == opponent) {
                nx += dx;
                ny += dy;
            }
            if (get(nx, ny) == player) return true;
        }
        return false;
    }

    vector<pair<int, int>> moves(int player) const {
        vector<pair<int, int>> result;
        for (auto [x, y] : fields)
            if (can_play(x, y, player))
                result.emplace_back(x, y);
        return result;
    }

    void do_move(optional<pair<int, int>> move, int player) {
        move_list.push_back(move);
        if (!move) return;
        
        int x = move->first, y = move->second;
        board[y][x] = player;
        fields.erase({x, y});
        
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            vector<pair<int, int>> to_flip;
            while (get(nx, ny) == 1 - player) {
                to_flip.emplace_back(nx, ny);
                nx += dx;
                ny += dy;
            }
            if (get(nx, ny) == player) {
                for (auto [fx, fy] : to_flip)
                    board[fy][fx] = player;
            }
        }
    }

    bool terminal() const {
        if (fields.empty()) return true;
        if (move_list.size() < 2) return false;
        return !move_list.back().has_value() && !move_list[move_list.size()-2].has_value();
    }
};

int evaluate(const Reversi& game, int player) {
    size_t hash = 0;
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            hash ^= std::hash<int>{}(game.board[y][x] + 2) << (y * BOARD_SIZE + x);
        }
    }
    hash ^= std::hash<int>{}(player);
    
    auto it = TRANSPOSITION_TABLE.find(hash);
    if (it != TRANSPOSITION_TABLE.end()) {
        return it->second.first;
    }
    
    int score = 0;
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (game.board[y][x] == player) score += WEIGHTS[y][x];
            else if (game.board[y][x] == 1 - player) score -= WEIGHTS[y][x];
        }
    }
    
    // int my_moves = game.moves(player).size();
    // int opp_moves = game.moves(1 - player).size();
    // score += (my_moves - opp_moves) * 10;
    
    for (auto [x, y] : corners) {
        if (game.board[y][x] == player) score += 50;
        else if (game.board[y][x] == 1 - player) score -= 50;
    }
    
    TRANSPOSITION_TABLE[hash] = {score, nullopt};
    return score;
}

pair<int, optional<pair<int, int>>> minimax(Reversi& game, int depth, int alpha, int beta, bool maximizing, int original_player) {
    int current_player = maximizing ? original_player : 1 - original_player;
    auto legal_moves = game.moves(current_player);

    if (depth == 0 || (legal_moves.empty() && game.moves(1 - current_player).empty())) {
        return {evaluate(game, original_player), nullopt};
    }

    if (legal_moves.empty()) {
        // Pass move
        Reversi game_copy = game;
        game_copy.do_move(nullopt, current_player);
        return minimax(game_copy, depth - 1, alpha, beta, !maximizing, original_player);
    }

    // Sortowanie ruchów - ważne w każdym węźle
    auto move_priority = [](const pair<int,int>& m) {
        if (find(corners.begin(), corners.end(), m) != corners.end()) return 3;
        if (m.first == 0 || m.first == 7 || m.second == 0 || m.second == 7) return 2;
        if ((m.first == 1 || m.first == 6) && (m.second == 1 || m.second == 6)) return 0;
        return 1;
    };
    
    sort(legal_moves.begin(), legal_moves.end(), [&](auto a, auto b) {
        return move_priority(a) > move_priority(b);
    });

    optional<pair<int, int>> best_move;
    int best_eval = maximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (auto& move : legal_moves) {
        Reversi game_copy = game;
        game_copy.do_move(move, current_player);
        auto [eval, _] = minimax(game_copy, depth - 1, alpha, beta, !maximizing, original_player);

        if (maximizing) {
            if (eval > best_eval) {
                best_eval = eval;
                best_move = move;
            }
            alpha = max(alpha, eval);
        } else {
            if (eval < best_eval) {
                best_eval = eval;
                best_move = move;
            }
            beta = min(beta, eval);
        }

        if (beta <= alpha) break;
    }

    return {best_eval, best_move};
}


class Player {
    Reversi game;
    int my_player;
    
public:
    Player() : my_player(1) {}

    void reset() {
        game = Reversi();
        my_player = 1;
        TRANSPOSITION_TABLE.clear();
        cout << "RDY" << endl << flush;
    }

    pair<string, vector<string>> hear() {
        string line;
        if (!getline(cin, line)) {
            return {"BYE", {}};
        }
        istringstream iss(line);
        string cmd;
        iss >> cmd;
        vector<string> args;
        string token;
        while (iss >> token) args.push_back(token);
        return {cmd, args};
    }

    void loop() {
        reset();
        while (true) {
            auto [cmd, args] = hear();
    
            if (cmd == "UGO") {
                my_player = 0;
            } 
            else if (cmd == "HEDID") {
                optional<pair<int, int>> move = nullopt;
                if (args.size() >= 4) {
                    int x = stoi(args[2]);
                    int y = stoi(args[3]);
                    if (x != -1 && y != -1)
                        move = make_pair(x, y);
                }
                game.do_move(move, 1 - my_player);
            } 
            else if (cmd == "ONEMORE") {
                reset();
                continue;
            } 
            else if (cmd == "BYE") {
                break;
            }
    
            auto moves = game.moves(my_player);
            optional<pair<int, int>> move;
    
            if (!moves.empty()) {
                move = minimax(game, 4, numeric_limits<int>::min(), 
                               numeric_limits<int>::max(), true, my_player).second;
            }

            if (move) {
                game.do_move(move, my_player);
                cout << "IDO " << move->first << " " << move->second << endl << flush;
            } else {
                game.do_move(nullopt, my_player);
                cout << "IDO -1 -1" << endl << flush;
            }
        }
    }
    
};

int main() {
    Player player;
    player.loop();
    return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>

size_t answer = 0;
const size_t kThree = 3;
const size_t kInf = 1e9;
size_t num;
size_t new_num;
std::vector<size_t> amount_win;
std::vector<size_t> amount_game;
std::vector<std::vector<size_t>> games;
std::unordered_map<size_t, std::unordered_map<size_t, std::vector<size_t>>> graph;
size_t current;
std::unordered_map<size_t, bool> visited;





void InsertBase() {
    new_num = num - 1;
    for (size_t i = 1; i <= new_num; ++i) {
        graph[i][new_num + i] = {i, new_num + i, amount_win[i]};
    }
    for (size_t i = 1; i <= new_num; ++i) {
        graph[0][i] = {0, i, kInf};
        graph[i + new_num][new_num * 2 + 1] =
            {i + new_num, new_num * 2 + 1, amount_win[0] + amount_game[0]};
    }
    current = new_num * 2 + 2;
}

void Insert(size_t first, size_t second) {
    graph[first][current] = {first, current, kInf};
    graph[second][current] = {second, current, kInf};
    ++current;
    graph[current][first + new_num] = {current, first + new_num, kInf};
    graph[current][second + new_num] = {current, second + new_num, kInf};
    graph[current - 1][current] =
    {current - 1, current, games[first][second]};
    ++current;
}

size_t DFS(size_t vertex, size_t minimal) {
    if (vertex == new_num * 2 + 1) {
        return minimal;
    }
    visited[vertex] = true;
    for (auto& it : graph[vertex]) {
        if (it.second.empty()) {
            continue;
        }
        if (visited[it.second[1]]) {
            continue;
        }
        if (it.second[2] > 0) {
            size_t digit = DFS(it.second[1], std::min(minimal, it.second[2]));
            if (digit > 0) {
                InitializeEdge(it.second[1], vertex);
                it.second[2] -= digit;
                graph[it.second.at(1)][vertex][2] += digit;
                return digit;
            }
        }
    }
    return 0;
}

int64_t CinHelp() {
    size_t vertex;
    games.resize(num);
    for (size_t i = 0; i < num; ++i) {
        games[i].resize(num);
    }
    for (size_t i = 0; i < num; ++i) {
        for (size_t j = 0; j < num; ++j) {
            std::cin >> vertex;
            games[i][j] = vertex;
        }
    }
    size_t answer_end = 0;
    InsertBase();
    for (size_t i = 0; i < num; ++i) {
        for (size_t j = 0; j < num; ++j) {
            if (i == 0) {
                games[i][j] = 0;
                games[j][i] = 0;
            }
            if (games[i][j] != 0) {
                Insert(i, j);
                answer_end += games[i][j];
                games[j][i] = 0;
                games[i][j] = 0;
            }
        }
    }
    for (size_t i = 1; i < num; ++i) {
        answer_end += amount_win[i];
    }
    return answer_end;
}

void Cin() {
    std::cin >> num;
    amount_win.resize(num);
    amount_game.resize(num);
    size_t vertex;
    for (size_t i = 0; i < num; ++i) {
        std::cin >> vertex;
        amount_win[i] = vertex;
    }
    for (size_t i = 0; i < num; ++i) {
        std::cin >> vertex;
        amount_game[i] = vertex;
    }
}

bool Finish(size_t answer_end, size_t answer_prev) {
    if (answer == answer_prev) {
        if (answer_end == answer) {
            std::cout << "YES";
            return true;
        }
        std::cout << "NO";
        return true;
    }
    return false;
}


int main() {
    Cin();
    size_t answer_end = CinHelp();
    while (true) {
        size_t answer_prev = answer;
        answer += DFS(0, kInf);
        visited.clear();
        if (Finish(answer_end, answer_prev)) {
            break;
        }
    }
}
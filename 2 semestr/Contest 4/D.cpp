#include <iostream>
#include <vector>

struct Edge {
  int v_;
  int flow_;
  int capacity_ = 1;

  Edge(int v, int capacity) : v_(v), flow_(0), capacity_(capacity) {}

  int get_capacity() { return capacity_ - flow_; }
};

class flow {
  int M;
  int N;
  int point_s;
  int point_t;
  int timer;
  int weight_A;
  int weight_B;
  size_t count = 0;
  std::vector<std::vector<bool>> used_;
  std::vector<std::vector<int>> graph_;
  std::vector<Edge> edge_;
  std::vector<int> used_v_;

 public:
  flow(int n, int m) {
    M = m;
    N = n;
    point_t = n * m + 1;
    point_s = 0;
    graph_.resize(n * m + 2);
    used_v_.resize(n * m + 2, 0);
    used_.resize(m);
    for (int i = 0; i < m; ++i) {
      used_[i].resize(n);
    }
    timer = 1;
  }

  void add(int vertex1, int vertex2, int cap = 1) {
    if (vertex1 >= 0 && vertex2 >= 0) {
      graph_[vertex1].push_back(edge_.size());
      edge_.push_back({vertex2, cap});
      graph_[vertex2].push_back(edge_.size());
      edge_.push_back({vertex1, 0});
    }
  }

  int get_idx(int i, int j) {
    return (i < 0 || j < 0 || i >= M || j >= N || used_[i][j]) ? -1
                                                               : i * N + j + 1;
  }

  int Dfs(int vertex, int cap) {
    if (vertex == point_t) {
      return 1;
    }
    used_v_[vertex] = timer;
    for (auto& idx : graph_[vertex]) {
      if (edge_[idx].get_capacity() != 0 && used_v_[edge_[idx].v_] != timer) {
        int res_dfs =
            Dfs(edge_[idx].v_, std::min(cap, edge_[idx].get_capacity()));
        if (res_dfs != 0) {
          edge_[idx].flow_ += res_dfs;
          edge_[idx ^ 1].flow_ -= res_dfs;
          return res_dfs;
        }
      }
    }
    return 0;
  }

  void input() {
    char elem;
    std::cin >> weight_A >> weight_B;
    int i = 0, j = 0;
    while (i < M) {
      while (j < N) {
        std::cin >> elem;
        if (elem == '*') {
          ++count;
          ++j;
          continue;
        }
        used_[i][j] = true;
        ++j;
      }
      j = 0;
      ++i;
    }

    i = 0;
    j = 0;
    while (i < M) {
      while (j < N) {
        if (used_[i][j]) {
          ++j;
          continue;
        }
        if ((i + j) % 2 == 1) {
          add(point_s, get_idx(i, j));
          add(get_idx(i, j), get_idx(i, j + 1));
          add(get_idx(i, j), get_idx(i + 1, j));
          add(get_idx(i, j), get_idx(i - 1, j));
          add(get_idx(i, j), get_idx(i, j - 1));
        } else {
          add(get_idx(i, j), point_t);
        }
        ++j;
      }
      ++i;
      j = 0;
    }
  }

  void print() {
    int path_1 = weight_B * count;
    int res = 0;
    while (Dfs(point_s, INT32_MAX)) {
      ++timer;
    }

    for (auto& idx : graph_[point_s]) {
      res += edge_[idx].flow_;
    }

    count -= res * 2;
    int path_2 = res * weight_A + count * weight_B;
    std::cout << std::min(path_1, path_2);
  }
};

int main() {
  int m;
  int n;
  std::cin >> m >> n;
  flow flow_(n, m);
  flow_.input();
  flow_.print();
}
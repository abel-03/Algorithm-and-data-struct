#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

namespace sdt {
template <typename T>
using matrix = std::vector<std::vector<T>>;

struct bridge {
  int src = 0;
  int dst = 0;
  int comp1 = 0;
  int comp2 = 0;
  bridge(const std::pair<int, int>& pr) {
    src = pr.first;
    dst = pr.second;
  }
  bridge() = default;
};

};  // namespace sdt

class Graph {
 private:
  int64_t size_ = 0;
  int64_t sum_ = 0;
  int64_t maxcolor = 1;
  sdt::matrix<int64_t> adj_;
  int64_t timer_ = 0;
  std::vector<int64_t> colors_;
  std::vector<bool> used_;
  std::vector<int64_t> tout_;
  std::vector<int64_t> tin_;
  sdt::matrix<int64_t> up_;
  std::vector<int64_t> height_;
  int64_t len_ = 0;
  void DFS1(int64_t v, int64_t p = -1) {
    tin_[v] = tout_[v] = timer_++;
    used_[v] = true;
    for (const auto& elem : adj_[v]) {
      if (used_[elem] && elem != p) {
        tout_[v] = std::min(tout_[v], tin_[elem]);
      }
      if (!used_[elem]) {
        DFS1(elem, v);
        tout_[v] = std::min(tout_[v], tout_[elem]);
      }
    }
  }
  void paint(int64_t v, int64_t color = 0) {
    colors_[v] = color;
    for (auto u : adj_[v]) {
      if (colors_[u] == 0) {
        if (tout_[u] > tin_[v]) {
          maxcolor++;
          up_[maxcolor][0] = color;
          height_[maxcolor] = height_[color] + 1;
          for (int64_t i = 1; i <= len_; ++i) {
            up_[maxcolor][i] = up_[up_[maxcolor][i - 1]][i - 1];
          }
          paint(u, maxcolor);
        } else {
          paint(u, color);
        }
      }
    }
  }

 public:
  void solve() {
    // DFS(size_ - 1);
    maxcolor = 0;
    for (int i = 0; i < size_; ++i) {
      if (colors_[i] == 0) {
        maxcolor++;
        paint(i, maxcolor);
        // maxcolor++;
      }
    }
  }

 private:
  void DFS(int64_t v, int64_t p = 0) {
    tin_[v] = ++timer_;
    up_[v][0] = p;
    height_[v] = height_[p] + 1;
    for (int64_t i = 1; i <= len_; ++i) {
      up_[v][i] = up_[up_[v][i - 1]][i - 1];
    }
    for (auto u : adj_[v]) {
      if (u == p) {
        continue;
      }
      DFS(u, v);
    }
    tout_[v] = ++timer_;
  }
  bool ancestor(int64_t u, int64_t v) {
    return (tin_[u] <= tin_[v]) && (tout_[u] >= tout_[v]);
  }
  int Lca(int v, int u) {
    if (ancestor(v, u)) return v;
    if (ancestor(u, v)) return u;
    for (int l = len_; l >= 0; --l)
      if (!ancestor(up_[v][l], u)) v = up_[v][l];
    return up_[v][0];
  }
  int64_t lca(int64_t a, int64_t b) {
    if (height_[a] < height_[b]) std::swap(a, b);
    int diff = height_[a] - height_[b];
    for (int64_t i = len_ - 1; i >= 0; --i) {
      if ((1 << i) <= diff) {
        a = up_[a][i];
        diff -= (1 << i);
      }
    }
    if (a == b) {
      return a;
    }
    for (int64_t i = len_ - 1; i >= 0; --i) {
      if (up_[a][i] != up_[b][i]) {
        a = up_[a][i];
        b = up_[b][i];
      }
    }
    return up_[a][0];
  }

 public:
  int64_t member(int64_t x, int64_t y, int64_t z, int64_t a1, int64_t a2) {
    return (x * a1 + y * a2 + z) % size_;
  }
  void Compute() {
    paint(finish_, 1);
    int64_t q = 0;
    std::cin >> q;
    int f, k;
    for (int i = 0; i < q; ++i) {
      std::cin >> f >> k;
      f--, k--;
      std::cout << height_[lca(colors_[f], colors_[k])] << "\n";
    }
    // std::cout << sum_ << "\n";
  }
  void prepare() {
    tin_.resize(size_);
    tout_.resize(size_);
    height_.assign(size_ + 1, 0);
    used_.assign(size_, false);
    colors_.assign(size_, 0);
    timer_ = 0;
    len_ = 1;
    len_ = std::__lg(size_) + 1;
    up_.assign(size_ + 1, std::vector<int64_t>(len_ + 1, 1));
    DFS1(finish_);
  }
  Graph(int64_t size, const sdt::matrix<int64_t>& adj, int64_t edge,
        int64_t finish) {
    adj_ = adj;
    size_ = size;
    finish_ = finish;
    prepare();
    edge_count_ = edge;
  }
  int dist(int a, int b) {
    // Depth(a) + Depth(b) − 2*Depth(LCA(a, b))
    return height_[a] + height_[b] - 2 * height_[lca(a, b)];
  }

 private:
  int64_t finish_ = 0;
  int64_t edge_count_ = 0;
};


void Requests() {
  int64_t n = 0, m = 0;
  std::cin >> n >> m;
  int finish = 0;
  std::cin >> finish;
  sdt::matrix<int64_t> adj(n);
  for (int64_t i = 0; i < m; ++i) {
    int64_t k, m;
    std::cin >> k >> m;
    adj[k - 1].push_back(m - 1);
    adj[m - 1].push_back(k - 1);
  }
  Graph graph(n, adj, m, finish - 1);
  graph.Compute();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Requests();
  return 0;
}
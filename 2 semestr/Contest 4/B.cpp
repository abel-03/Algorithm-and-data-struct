#include <iostream>
#include <vector>

class Kuhn {
 private:
  std::vector<int> coincidence_;
  std::vector<bool> used_;
  std::vector<std::vector<int>> graph_;
  int num_L = 0;
  int num_R = 0;
  int ans_ = 0;

 public:
  Kuhn() = default;
  bool try_kuhn(int v) {
    if (!used_[v]) {
      used_[v] = true;
      for (size_t i = 0; i < graph_[v].size(); ++i) {
        int to = graph_[v][i];
        if (coincidence_[to] == -1 || try_kuhn(coincidence_[to])) {
          coincidence_[to] = v;
          return true;
        }
      }
    }
    return false;
  }

  void algo() {
    for (int i = 0; i < num_L; ++i) {
      used_.assign(num_L, false);
      if (try_kuhn(i)) {
        ++ans_;
      }
    }
  }

  void push() {
    std::cin >> num_L >> num_R;
    graph_.resize(num_L);
    coincidence_.resize(num_R, -1);
    int elem;
    for (int i = 0; i < num_L; ++i) {
      std::cin >> elem;
      while (elem != 0) {
        graph_[i].push_back(elem - 1);
        std::cin >> elem;
      }
    }
  }

  void print() {
    std::cout << ans_ << '\n';
    for (int i = 0; i < num_R; ++i) {
      if (coincidence_[i] != -1) {
        std::cout << coincidence_[i] + 1 << " " << i + 1 << '\n';
      }
    }
  }
};
int main() {
  Kuhn kuhn;
  kuhn.push();
  kuhn.algo();
  kuhn.print();

  return 0;
}
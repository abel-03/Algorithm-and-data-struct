#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

class Flow {
 private:
  std::vector<int> flow_;
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>> adj_;
  std::unordered_map<int, bool> used_;
  int num_vertex_ = 0;
  int path_last_ = 0;
  int path_begin_ = 0;
  int path_ = 0;
  int dfs_res_ = 0;

 public:
  Flow(size_t num_vert) {
    num_vertex_ = num_vert;
    flow_.resize(num_vert + 1);
  }

  ~Flow() = default;

  int Dfs(int vert, int weight = INT32_MAX) {
    if (vert == 2 * num_vertex_ + 1) {
      return weight;
    }
    used_[vert] = true;
    for (auto& vert_to : adj_[vert]) {
      if (!used_[vert_to.second[1]] && !vert_to.second.empty()) {
        if (vert_to.second[2] <= 0) {
          continue;
        }
        dfs_res_ = Dfs(vert_to.second[1],
                       weight < vert_to.second[2] ? weight : vert_to.second[2]);
        if (dfs_res_ <= 0) {
          continue;
        }
        if (adj_[vert_to.second[1]][vert].empty()) {
          adj_[vert_to.second[1]][vert] = {vert_to.second[1], vert, 0};
        }

        vert_to.second[2] -= dfs_res_;
        adj_[vert_to.second[1]][vert][2] += dfs_res_;
        return dfs_res_;
      }
    }
    return 0;
  }

  void Input1() {
    for (int i = 0; i < num_vertex_; ++i) {
      std::cin >> flow_[i + 1];
      flow_[i + 1] >= 0 ? adj_[0][i + 1] = {0, i + 1, flow_[i + 1]}
                        : adj_[i + 1][2 * num_vertex_ + 1] = {
                              i + 1, 2 * num_vertex_ + 1, -flow_[i + 1]};
    }
  }

  void Input2() {
    int req;
    for (int i = 0; i < num_vertex_; ++i) {
      std::cin >> req;
      for (int j = 0; j < req; ++j) {
        std::cin >> dfs_res_;
        adj_[i + 1][dfs_res_] = {i + 1, dfs_res_, INT32_MAX};
      }
    }
  }

  void Algo() {
    for (size_t i = 0; i < flow_.size(); ++i) {
      if (flow_[i] > 0) {
        path_last_ += flow_[i];
      }
    }

    for (;;) {
      path_begin_ = path_;
      path_ += Dfs(0);
      used_.clear();
      if (path_ != path_begin_) {
        continue;
      }
      Cout();
      return;
    }
  }

  void Cout() const { std::cout << path_last_ - path_ << '\n'; }
};

int main() {
  int num_vert;
  std::cin >> num_vert;
  Flow floow(num_vert);
  floow.Input1();
  floow.Input2();
  floow.Algo();
}
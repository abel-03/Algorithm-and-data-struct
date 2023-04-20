#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class DSU {
 public:
  DSU(size_t num_vertex) {
    for (int i = 0; i <= num_vertex; ++i) {
      parent_.push_back(i);
      size_.push_back(1);
    }
  }

  T FindSet(T vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  void add_edge(T vertex1, T vertex2, int weight) {
    int head_vertex1 = FindSet(vertex1);
    int head_vertex2 = FindSet(vertex2);

    ++size_[head_vertex1];
    ++size_[head_vertex2];

    if (head_vertex1 == head_vertex2) {
      return;
    }

    if (size_[head_vertex1] < size_[head_vertex2]) {
      std::swap(head_vertex1, head_vertex2);
    }

    parent_[head_vertex2] = head_vertex1;
    weight_ += weight;
  }

  void GraphPush(T vertex1, T vertex2, int weight) {
    graph_.push_back(std::make_pair(std::make_pair(vertex1, vertex2), weight));
  }

  void Kruskal() {
    std::sort(graph_.begin(), graph_.end(),
              [](const auto &edge1, const auto &edge2) {
                return edge1.second < edge2.second;
              });
    for (size_t i = 0; i < graph_.size(); ++i) {
      add_edge(graph_[i].first.first, graph_[i].first.second, graph_[i].second);
    }
  }

  int GetWeight() { return weight_; }

 private:
  std::vector<T> parent_;
  int weight_ = 0;
  std::vector<size_t> size_;
  std::vector<std::pair<std::pair<T, T>, int>> graph_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_vertex;
  int weight;

  std::cin >> num_vertex;
  DSU<int> set(num_vertex);

  for (int i = 1; i <= num_vertex; ++i) {
    for (int j = 1; j <= num_vertex; ++j) {
      std::cin >> weight;
      if (j > i) {
        set.GraphPush(i, j, weight);
      }
    }
  }

  for (int i = 1; i <= num_vertex; ++i) {
    std::cin >> weight;
    set.GraphPush(i, 0, weight);
  }

  set.Kruskal();
  std::cout << set.GetWeight();
}
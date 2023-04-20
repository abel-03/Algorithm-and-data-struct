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
      us_.push_back(false);
    }
    maxost_.resize(num_vertex + 1);
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

    if (head_vertex1 == head_vertex2) {
      return;
    }
    ++size_[head_vertex1];
    ++size_[head_vertex2];

    if (size_[head_vertex1] < size_[head_vertex2]) {
      std::swap(head_vertex1, head_vertex2);
    }

    parent_[head_vertex2] = head_vertex1;
    weight_ += weight;
  }

  void GraphPush(T vertex1, T vertex2, int weight) {
    graph_.push_back(std::make_pair(std::make_pair(vertex1, vertex2), weight));
  }

  void Kruskal(int num_request) {
    std::sort(graph_.begin(), graph_.end(),
              [](const auto &edge1, const auto &edge2) {
                return edge1.second > edge2.second;
              });
    for (size_t i = 0; i < graph_.size(); ++i) {
      if (FindSet(graph_[i].first.first) != FindSet(graph_[i].first.second)) {
        add_edge(graph_[i].first.first, graph_[i].first.second,
                 graph_[i].second);
        maxost_[graph_[i].first.first].push_back(
            std::make_pair(graph_[i].first.second, graph_[i].second));
        maxost_[graph_[i].first.second].push_back(
            std::make_pair(graph_[i].first.first, graph_[i].second));
      }
    }
  }

  int algo(T vertex1, T vertex2, int weight = INT32_MAX) {
    if (vertex1 == vertex2) {
      return weight;
    }
    us_[vertex1] = true;
    for (std::pair<T, T> &point : maxost_[vertex1]) {
      if (!us_[point.first]) {
        result_ = algo(point.first, vertex2, std::min(weight, point.second));
      }
    }
    return result_;
  }

  int GetWeight() { return weight_; }

  void assign_us() { us_.assign(us_.size(), false); }

 private:
  std::vector<T> parent_;
  int weight_ = 0;
  int result_ = 0;
  std::vector<bool> us_;
  std::vector<size_t> size_;
  std::vector<std::pair<std::pair<T, T>, int>> graph_;
  std::vector<std::vector<std::pair<T, T>>> maxost_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_vertex;
  int num_request;
  int k;
  int weight;
  int vertex1;
  int vertex2;

  std::cin >> num_vertex >> num_request >> k;
  DSU<int> set(num_vertex);

  for (int i = 1; i <= num_request; ++i) {
    std::cin >> vertex1 >> vertex2 >> weight;
    set.GraphPush(vertex1, vertex2, weight);
  }
  set.Kruskal(num_request);
  for (int i = 0; i < k; ++i) {
    std::cin >> vertex1 >> vertex2;
    std::cout << set.algo(vertex1, vertex2) << '\n';
    set.assign_us();
  }
}
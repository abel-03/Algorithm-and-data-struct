#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Graph {
 public:
  Graph(int num_vertex) {
    graph_.resize(num_vertex + 1);
    t_in.resize(num_vertex + 1);
    t_out.resize(num_vertex + 1);
    depth_.resize(num_vertex + 1);
    us_.resize(num_vertex + 1);
    color_type.resize(num_vertex + 1);
    parent_.resize(num_vertex + 1);
    max_depth_ = log2(num_vertex + 1);
    for (int i = 0; i < num_vertex + 1; ++i) {
      parent_[i].resize(max_depth_ + 2);
    }
  }

  T FindSet(T vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  int GetWeight() { return max_depth_; }

  void assign_us() { us_.assign(us_.size(), false); }

  void DFS(int vertex, int parent) {
    us_[vertex] = true;
    t_in[vertex] = timer_;
    t_out[vertex] = timer_;
    ++timer_;
    for (T& to : graph_[vertex]) {
      if (us_[to]) {
        if (to != parent) {
          t_out[vertex] = std::min(t_in[to], t_out[vertex]);
        }
      } else {
        DFS(to, vertex);
        t_out[vertex] = std::min(t_out[to], t_out[vertex]);
      }
    }
  }

  void road(T vertex, int color) {
    color_type[vertex] = color;
    for (T& to : graph_[vertex]) {
      if (color_type[to] == 0 && t_out[to] > t_in[vertex]) {
        ++iter;
        parent_[iter][0] = color;
        depth_[iter] = depth_[color] + 1;
        for (int i = 0; i < max_depth_ + 1; ++i) {
          parent_[iter][i + 1] = parent_[parent_[iter][i]][i];
        }
        road(to, iter);
      } else if (color_type[to] == 0) {
        road(to, color);
      }
    }
  }

  void add_edge(T vertex1, T vertex2) {
    graph_[vertex1].push_back(vertex2);
    graph_[vertex2].push_back(vertex1);
  }

  int LCA(T vertex1, T vertex2) {
    if (depth_[vertex1] < depth_[vertex2]) {
      std::swap(vertex1, vertex2);
    }

    for (int i = max_depth_; i >= 0; --i) {
      if (depth_[vertex1] - depth_[vertex2] & (1 << i)) {
        vertex1 = parent_[vertex1][i];
      }
    }

    if (vertex1 == vertex2) {
      return vertex1;
    }

    for (int i = max_depth_ ; i >= 0; --i) {
      if (parent_[vertex1][i] != parent_[vertex2][i]) {
        vertex2 = parent_[vertex2][i];
        vertex1 = parent_[vertex1][i];
      }
    }
    return parent_[vertex1][0];
  }

  int Get_answer(int vertex1, int vertex2) {
    return depth_[LCA(color_type[vertex1 - 1], color_type[vertex2 - 1])];
  }

  int64_t GetResult(T vertex1, T vertex2) {
    return depth_[vertex1] + depth_[vertex2] -
           2 * depth_[LCA(vertex1, vertex2)];
  }

 private:
  std::vector<std::vector<T>> graph_;
  std::vector<int> t_in;
  std::vector<int> t_out;
  std::vector<int> color_type;
  std::vector<int> depth_;
  std::vector<bool> us_;
  std::vector<std::vector<int>> parent_;
  int num_vertex_ = 0;
  int max_depth_ = 0;
  int iter = 1;
  int timer_ = 0;
};

int main() {
  int num_vertex;
  int num_edge;
  int end_vertex;
  int vertex1;
  int vertex2;
  int num_request;

  std::cin >> num_vertex >> num_edge >> end_vertex;

  Graph<int64_t> graph(num_vertex);

  for (int i = 0; i < num_edge; ++i) {
    std::cin >> vertex1 >> vertex2;
    graph.add_edge(vertex1 - 1, vertex2 - 1);
  }
  graph.DFS(end_vertex - 1, -1);
  graph.road(end_vertex - 1, 1);

  std::cin >> num_request;

  for (int i = 0; i < num_request; ++i) {
    std::cin >> vertex1 >> vertex2;
    std::cout << graph.Get_answer(vertex1, vertex2) << "\n";
  }
}
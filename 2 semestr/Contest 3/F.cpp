#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Tree {
 public:
  Tree(int num_vertex) {
    tree_.resize(num_vertex + 1);
    dp_.resize(num_vertex + 1);
    depth_.resize(num_vertex + 1);
    num_vertex_ = num_vertex;
    for (int i = 0; i <= num_vertex; ++i) {
      dp_[i].resize(log2(num_vertex) + 1);
    }
  }

  void add_edge(T vertex1, T vertex2) {
    tree_[vertex1].push_back(vertex2);
    tree_[vertex2].push_back(vertex1);
  }

  void DFS(T vertex, T parent, int depth) {
    dp_[vertex][0] = parent;
    depth_[vertex] = depth;

    for (int i = 1; i <= log2(num_vertex_); ++i) {
      dp_[vertex][i] = dp_[dp_[vertex][i - 1]][i - 1];
    }

    for (T& heir : tree_[vertex]) {
      if (heir != parent) {
        DFS(heir, vertex, depth + 1);
      }
    }
  }

  int LCA(int vertex1, int vertex2) {
    if (depth_[vertex1] < depth_[vertex2]) {
      std::swap(vertex1, vertex2);
    }

    for (int i = log2(num_vertex_); i >= 0; --i) {
      if (depth_[vertex1] - depth_[vertex2] & (1 << i)) {
        vertex1 = dp_[vertex1][i];
      }
    }

    if (vertex1 == vertex2) {
      return vertex1;
    }

    for (int i = log2(num_vertex_); i >= 0; --i) {
      if (dp_[vertex1][i] != dp_[vertex2][i]) {
        vertex2 = dp_[vertex2][i];
        vertex1 = dp_[vertex1][i];
      }
    }
    return dp_[vertex1][0];
  }

  int GetResult(T vertex1, T vertex2) {
    return depth_[vertex1] + depth_[vertex2] -
           2 * depth_[LCA(vertex1, vertex2)];
  }

 private:
  std::vector<std::vector<T>> tree_;
  std::vector<int> depth_;
  std::vector<std::vector<int>> dp_;
  int num_vertex_ = 0;
};

int main() {
  int num_vertex;
  int num_request;
  int vertex1;
  int vertex2;

  std::cin >> num_vertex;

  Tree<int> tree(num_vertex);

  for (int i = 0; i < num_vertex - 1; ++i) {
    std::cin >> vertex1 >> vertex2;
    tree.add_edge(vertex1, vertex2);
  }

  tree.DFS(1, 0, 0);

  std::cin >> num_request;

  for (int i = 0; i < num_request; ++i) {
    std::cin >> vertex1 >> vertex2;
    std::cout << tree.GetResult(vertex1, vertex2) << '\n';
  }

  return 0;
}
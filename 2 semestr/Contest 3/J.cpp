#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Tree {
 public:
  Tree(int num_vertex) {
    finish = log2(num_vertex) + 1;
    dp_.resize(num_vertex);
    depth_.resize(num_vertex);
    tree_.resize(num_vertex);
    num_vertex_ = num_vertex;
    for (int i = 0; i < num_vertex ; ++i) {
      dp_[i].resize(finish + 1, 1);
    }
    deleted_.resize(num_vertex);  
    parent.resize(1, -1);
  }

  int find(int v) {
    if (!deleted_[parent[v]]) {
      return parent[v];
    }
    return parent[v] = find(dp_[v][0]);
  }

  void DFS(T vertex, T parent, int depth) {
    dp_[vertex][0] = parent;
    depth_[vertex] = depth;

    for (int i = 1; i <=  finish; ++i) {
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

    for (int i = finish -1; i >= 0; --i) {
      if (depth_[vertex1] - depth_[vertex2] & (1 << i)) {
        vertex1 = dp_[vertex1][i];
      }
    }

    if (vertex1 == vertex2) {
      return vertex1;
    }

    for (int i = finish - 1; i >= 0; --i) {
      if (dp_[vertex1][i] != dp_[vertex2][i]) {
        vertex2 = dp_[vertex2][i];
        vertex1 = dp_[vertex1][i];
      }
    }
    return dp_[vertex2][0];
  }

  int GetResult(T vertex1, T vertex2) {
    return depth_[vertex1] + depth_[vertex2] -
           2 * depth_[LCA(vertex1, vertex2)];
  }
  std::vector<int> parent;
  std::vector<std::vector<T>> tree_;
  std::vector<bool> deleted_;
  std::vector<int> depth_;


  std::vector<std::vector<int>> dp_;
  int num_vertex_ = 0;
  int finish = 0;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  
  int num_request;
  char request;
  int iter_request = 0;
  int vertex;
  int vertex2;
  int iter = 0;
  std::cin >> num_request;

  Tree<int> tree(num_request);
  for (int i = 0; i < num_request; ++i) {
    std::cin >> request;
    switch (request) {
      case '+':
        iter_request = 0;
        std::cin >> vertex;
        --vertex;
        ++iter;
        tree.tree_[vertex].push_back(iter);
        tree.tree_[iter].push_back(vertex);
        tree.parent.push_back(vertex);
        tree.dp_[iter][0] = vertex;
        tree.depth_[iter] = tree.depth_[vertex] + 1;

    for (int i = 1; i <=  tree.finish ; ++i) {
      tree.dp_[iter][i] = tree.dp_[tree.dp_[iter][i - 1]][i - 1];
    }
        break;
      case '-':
        iter_request = 0;
        std::cin >> vertex;
        --vertex;
        tree.deleted_[vertex] = true;
        break;
      case '?':
        std::cin >> vertex >> vertex2;
        --vertex2;
        --vertex;
    //    tree.DFS(0, 0, 0);
        ++iter_request;
        int res = tree.LCA(vertex, vertex2);
        if (tree.deleted_[res]) {
          res = tree.find(res);
        }
        std::cout << res + 1 << '\n';
    }
  }

  return 0;
}
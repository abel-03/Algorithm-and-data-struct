// 83948770
#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace graph {
template <typename T>
struct DefaultEdge : std::pair<T, T> {
  DefaultEdge(const T& first, const T& second)
      : std::pair<T, T>(first, second) {}
  using BaseClass = std::pair<T, T>;
  const T& Start() const { return BaseClass::first; }
  const T& Finish() const { return BaseClass::second; }
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AbstractGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = Edge;

  explicit AbstractGraph(size_t vertices_num, size_t edges_num = 0)
      : vertices_number_(vertices_num), edges_number_(edges_num) {}
  size_t GetVerticesNumber() const { return vertices_number_; }
  size_t GetEdgesNumber() const { return edges_number_; }
  virtual std::vector<std::pair<Vertex, Vertex>>& GetEdge(int vertex) = 0;

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_num, size_t edges_num)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges_num) {
    list_.resize(vertices_num);
  }

  void Push(Vertex begin, Vertex end, Vertex weight) {
    list_[begin].push_back(std::make_pair(end, weight));
    list_[end].push_back(std::make_pair(begin, weight));
  }
  std::vector<std::pair<Vertex, Vertex>>& GetEdge(int vertex) {
    return list_[vertex];
  }

 private:
  std::vector<std::vector<std::pair<Vertex, Vertex>>> list_;
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyMatrixGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyMatrixGraph(size_t vertices_num, const std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges.size()) {
    martrix_graph_.resize[AbstractGraph<Vertex, Edge>::GetVerticesNumber() + 1];
    for (int i = 1; i <= AbstractGraph<Vertex, Edge>::GetVerticesNumber();
         ++i) {
      martrix_graph_.resize(
          AbstractGraph<Vertex, Edge>::GetVerticesNumber() + 1, 0);
    }

    for (const auto& edge : edges) {
      martrix_graph_[edge.first][edge.second] = 1;
      martrix_graph_[edge.second][edge.first] = 1;
    }
  }

 private:
  std::vector<std::vector<Vertex>> martrix_graph_;
};
}  // namespace graph

template <typename T>
class Tree {
 public:
  Tree(size_t num_vertex) { tree_.resize(num_vertex); }

  Tree() = default;
  void push(T vertex1, T vertex2, int weight) {
    tree_.resize(std::max(vertex1, vertex2) + 1);
    tree_[vertex1].push_back(std::make_pair(vertex2, weight));
    tree_[vertex2].push_back(std::make_pair(vertex1, weight));
  }

 private:
  std::vector<std::vector<std::pair<T, T>>> tree_;
};

template <typename T>
class DSU {
 public:
  DSU(size_t num_vertex) {
    for (int i = 0; i <= num_vertex; ++i) {
      parent_.push_back(i);
      size_.push_back(1);
      used_.push_back(false);
    }
    adjacency_list_.resize(num_vertex + 1);
  }

  T FindSet(T vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  void push_adjacency_list(T vertex1, T vertex2, int weight) {
    adjacency_list_[vertex1].push_back(std::make_pair(vertex2, weight));
    adjacency_list_[vertex2].push_back(std::make_pair(vertex1, weight));
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
              [](const auto& edge1, const auto& edge2) {
                return edge1.second < edge2.second;
              });
    for (size_t i = 0; i < graph_.size(); ++i) {
      add_edge(graph_[i].first.first, graph_[i].first.second, graph_[i].second);
    }
  }

  Tree<T> Prim() {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        q;
    Tree<int> tree;
    q.push(std::make_pair(0, 1));
    int vertex = q.top().second;
    int weight = q.top().first;

    while (!q.empty()) {
      q.pop();
      if (used_[vertex]) {
        continue;
      }
      weight_ += weight;
      used_[vertex] = true;
      for (auto to : adjacency_list_[vertex]) {
        if (!used_[to.first]) {
          q.push(std::make_pair(to.second, to.first));
        }
      }
      if (q.top().second != vertex) {
        tree.push(vertex - 1, q.top().second - 1, q.top().first);
      }
      vertex = q.top().second;
      weight = q.top().first;
    }
    return tree;
  }

  int GetWeight() { return weight_; }

 private:
  std::vector<T> parent_;
  int weight_ = 0;
  std::vector<size_t> size_;
  std::vector<bool> used_;
  std::vector<std::pair<std::pair<int, int>, int>> graph_;
  std::vector<std::vector<std::pair<T, T>>> adjacency_list_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_vertex;
  int num_edge;
  int vertex1;
  int vertex2;
  int weight;

  std::cin >> num_vertex >> num_edge;
  DSU<int> set(num_vertex);

  for (int i = 0; i < num_edge; ++i) {
    std::cin >> vertex1 >> vertex2 >> weight;
    set.GraphPush(vertex1, vertex2, weight);
    set.push_adjacency_list(vertex1, vertex2, weight);
  }

  set.Kruskal();
  std::cout << set.GetWeight();
}
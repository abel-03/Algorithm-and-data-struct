#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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

  virtual std::vector<std::pair<int, int>> GetNeighbours(
      const Vertex& vertex) = 0;

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};
}  // namespace graph

namespace graph {
template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  std::vector<int> t_in;
  std::vector<bool> used;
  std::vector<bool> used_print;
  std::vector<int> ret;
  std::vector<std::vector<bool>> position;
  std::vector<int> res;
  int timer = 0;

  AdjacencyListGraph(size_t vertices_num, const std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges.size()) {
    t_in.resize(vertices_num + 1);
    used.resize(vertices_num + 1);
    ret.resize(vertices_num + 1);
    used_print.resize(vertices_num + 1);
    list_.resize(vertices_num + 1);

    int iter_for_position = 1;

    for (const auto& edge : edges) {
      list_[edge.first].push_back(std::pair(edge.second, iter_for_position));
      list_[edge.second].push_back(std::pair(edge.first, iter_for_position++));
    }
  }

  std::vector<std::pair<int, int>> GetNeighbours(const Vertex& vertex) final {
    return list_[vertex];
  }

 private:
  std::vector<std::vector<std::pair<int, int>>> list_;
};
}  // namespace graph

namespace traverses {
template <class Vertex, class Graph, class Visitor>
void BreadthFirstSearch(Vertex origin_vertex, Graph& graph, Visitor visitor) {
  std::queue<Vertex> bfs_queue;
  std::unordered_set<Vertex> visited_vertices;

  bfs_queue.push(origin_vertex);
  visited_vertices.insert(origin_vertex);

  while (!bfs_queue.empty()) {
    auto cur_vertex = bfs_queue.front();
    bfs_queue.pop();
    for (auto& neighbour : graph.GetNeighbours(cur_vertex)) {
      if (visited_vertices.find(neighbour) == visited_vertices.end()) {
        visitor.TreeEdge({cur_vertex, neighbour});
        bfs_queue.push(neighbour);
        visited_vertices.insert(neighbour);
      }
    }
  }
}
}  // namespace traverses

namespace traverses {
template <class Graph, class Vertex, class Visitor>
void DFS(Graph& graph, Vertex point, Visitor parent = -1) {
  graph.t_in[point] = graph.timer++;
  graph.ret[point] = graph.t_in[point];
  graph.used[point] = true;
  for (auto& to : graph.GetNeighbours(point)) {
    if (to.second == parent) {
      continue;
    }
    if (graph.used[to.first]) {
      graph.ret[point] = std::min(graph.ret[point], graph.t_in[to.first]);
    } else {
      DFS(graph, to.first, to.second);
      graph.ret[point] = std::min(graph.ret[point], graph.ret[to.first]);
      if (graph.ret[to.first] == graph.t_in[to.first]) {
        graph.res.push_back(to.second);
      }
    }
  }
}
}  // namespace traverses

void Print(std::vector<int> res) {
  std::cout << res.size() << "\n";
  for (int to : res) {
    std::cout << to << "\n";
  }
}

namespace traverses::visitors {
template <class Vertex, class Edge>
class BfsVisitor {
 public:
  virtual void TreeEdge(const Edge&) = 0;
  virtual ~BfsVisitor() = default;
};
}  // namespace traverses::visitors

namespace traverses::visitors {
template <class Vertex, class Edge>
class AncestorBfsVisitor : BfsVisitor<Vertex, Edge> {
 public:
  virtual void TreeEdge(const Edge& edge) {
    ancestors_[edge.Finish()] = edge.Start();
  }

  std::unordered_map<Vertex, Vertex> GetMap() const { return ancestors_; }

  virtual ~AncestorBfsVisitor() = default;

 private:
  std::unordered_map<Vertex, Vertex> ancestors_;
};
}  // namespace traverses::visitors

int main() {
  int number_point, number_country;

  std::cin >> number_point >> number_country;

  std::vector<graph::DefaultEdge<int>> edges;

  for (int i = 0; i < number_country; ++i) {
    int parent, child;

    std::cin >> parent >> child;

    graph::DefaultEdge<int> edge(parent, child);
    edges.push_back(edge);
  }

  graph::AdjacencyListGraph<int, graph::DefaultEdge<int>> graph(number_point,
                                                                edges);
  for (int i = 1; i <= number_point; ++i) {
    if (!graph.used[i]) {
      traverses::DFS<graph::AdjacencyListGraph<int, graph::DefaultEdge<int>>,
                     int, int>(graph, i, 0);
    }
  }
  std::sort(graph.res.begin(), graph.res.end());
  Print(graph.res);
}
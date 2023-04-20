#include <algorithm>
#include <deque>
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

  virtual std::vector<int> GetNeighbours(const Vertex& vertex) = 0;

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};
}  // namespace graph

namespace graph {
template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_num, const std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges.size()) {
    for (const auto& edge : edges) {
      list_[edge.first].push_back(edge.second);
      list_[edge.second].push_back(edge.first);
    }
  }

  std::vector<Vertex> GetNeighbours(const Vertex& vertex) final {
    return list_[vertex];
  }

 private:
  std::unordered_map<Vertex, std::vector<Vertex>> list_;
};
}  // namespace graph

namespace graph {
template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyMatrixGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyMatrixGraph(size_t vertices_num, const std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges.size()) {
    for (const auto& edge : edges) {
      list_[edge.first].push_back(edge.second);
      list_[edge.second].push_back(edge.first);
    }
  }

  std::vector<Vertex> GetNeighbours(const Vertex& vertex) final {
    return list_[vertex];
  }

 private:
  std::unordered_map<Vertex, std::vector<Vertex>> list_;
};
}  // namespace graph

template <class Vertex>
void Print(std::vector<Vertex>& res, std::vector<int>& dist, Vertex& point_t) {
  std::cout << dist[point_t] << "\n";
  int to_vertex = res[point_t];
  std::vector<int> path;
  while (to_vertex != -1) {
    path.push_back(to_vertex);
    to_vertex = res[to_vertex];
  }
  for (int i = path.size() - 1; i >= 0; --i) {
    std::cout << path[i] << " ";
  }
  std::cout << point_t;
}

template <class Graph, class Vertex, class Visitor>
void Bfs(Graph& graph, Vertex point_s, Visitor point_t) {
  std::queue<Vertex> bfs_q;
  std::vector<Vertex> dist(graph.GetVerticesNumber() + 1, -1);
  dist[point_s] = 0;
  std::vector<Vertex> res(graph.GetVerticesNumber() + 1, -1);
  bfs_q.push(point_s);
  while (!bfs_q.empty()) {
    int cur = bfs_q.front();
    bfs_q.pop();
    for (auto& to_vertex : graph.GetNeighbours(cur)) {
      if (dist[to_vertex] == -1) {
        dist[to_vertex] = dist[cur] + 1;
        res[to_vertex] = cur;
        bfs_q.push(to_vertex);
      }
    }
  }
  if (dist[point_t] > -1) {
    Print<Vertex>(res, dist, point_t);
  } else {
    std::cout << -1;
  }
};

namespace traverses {
template <class Graph, class Vertex, class Visitor>
void DFS(Graph& graph, Vertex point, Visitor parent = Visitor(),size_t timer = 0) {
  std::vector<Vertex> t_in(graph.GetVerticesNumber() + 1);
  std::vector<bool> used(graph.GetVerticesNumber() + 1);
  std::vector<Vertex> ret(graph.GetVerticesNumber() + 1);
  std::vector<Vertex> res;
  t_in[point] = timer++;
  ret[point] = t_in[point];
  used[point] = true;
  for (auto& to_vertex : graph.GetNeighbours(point)) {
    if (to_vertex.second == parent) {
      continue;
    }
    if (used[to_vertex.first]) {
      ret[point] = std::min(ret[point], t_in[to_vertex.first]);
    } else {
      DFS(graph, to_vertex.first, to_vertex.second);
      ret[point] = std::min(ret[point], ret[to_vertex.first]);
      if (ret[to_vertex.first] == t_in[to_vertex.first]) {
        res.push_back(to_vertex.second);
      }
    }
  }
}
}  // namespace traverses

template <class Vertex>
void Print(std::vector<Vertex> res) {
  std::cout << res.size() << "\n";
  for (auto& to_vertex : res) {
    std::cout << to_vertex << "\n";
  }
}

namespace visitors {
template <class Vertex, class Edge>
class AbstractVisitor {
 public:
  void VisitVertex(Vertex vertex);
  void Visit(Edge graph) {
    for (Vertex vertex : graph.GetVertices()) {
      VisitVertex(vertex);
      for (Edge edge : graph.getEdges()) {
        VisitEdge(edge);
      }
    }
  }
};
}  // namespace visitors

namespace visitors {
template <class Vertex, class Edge>
class Visitor {
 public:
  virtual void Visit(Vertex& vertex) = 0;
  virtual void Visit(Edge& edge) = 0;
};
}  // namespace visitors

namespace visitors {
template <class Vertex, class Edge>
class Vert : public Visitor<Vertex, Edge> {
 public:
  void Visit(Vertex& visitor) { visitor.Visit(*this); }
  void Parent(Vertex* parent) { parent_ = parent; }
  Vertex* GetParent() const { return parent_; }

 private:
  Vertex* parent_ = nullptr;
};
}  // namespace visitors

namespace visitors {
template <class Vertex, class Edge>
class Edges : public Visitor<Vertex, Edge> {
 public:
  void Visit(Vertex& visitor) { visitor.Visit(*this); }
  Vertex* GetEdge() const { return edge_; }

 private:
  Vertex* edge_;
};
}  // namespace visitors

namespace visitors {
template <class Vertex, class Edge>
class ParentVisitor : public Visitor<Vertex, Edge> {
 public:
  void Visit(Vertex& vertex) { vertex.Parent(parent_); }
  void Visit(Edge&) {}
  void Parent(Vertex* parent) { parent_ = parent; }

 private:
  Vertex* parent_ = nullptr;
};
}  // namespace visitors

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
    parent_[edge.Finish()] = edge.Start();
  }
  std::unordered_map<Vertex, Vertex> GetMap() const { return parent_; }
  virtual ~AncestorBfsVisitor() = default;

 private:
  std::unordered_map<Vertex, Vertex> parent_;
};
}  // namespace traverses::visitors

int main() {
  int number_point;
  int number_country;
  int point_s;
  int point_t;

  std::cin >> number_point >> number_country >> point_s >> point_t;

  std::vector<graph::DefaultEdge<int>> edges;

  for (int i = 0; i < number_country; ++i) {
    int parent;
    int child;

    std::cin >> parent >> child;

    graph::DefaultEdge<int> edge(parent, child);
    edges.push_back(edge);
  }

  graph::AdjacencyListGraph<int, graph::DefaultEdge<int>> graph(number_point,
                                                                edges);

  Bfs<graph::AdjacencyListGraph<int, graph::DefaultEdge<int>>, int, int>(
      graph, point_s, point_t);
}
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

namespace traverses {
template <typename Vertex, typename Edge = graph::DefaultEdge<Vertex>>
class VisitorDijsktra {
 public:
  std::vector<int> dist;
  std::vector<int> parent;
  std::vector<bool> used;
  std::priority_queue<std::pair<size_t, Vertex>,
                      std::vector<std::pair<size_t, Vertex>>,
                      std::greater<std::pair<size_t, Vertex>>>
      queue_point;
};

template <typename Vertex, class Graph, typename Visitor>
class Dijsktra {
 public:
  Dijsktra(Vertex& begin, Graph& graph, Visitor& visitor) {
    visitor.dist.resize(graph.GetVerticesNumber(), 2009000999);
    visitor.used.resize(graph.GetVerticesNumber(), false);
    visitor.queue_point.push(std::make_pair(visitor.dist[begin], begin));
    visitor.dist[begin] = 0;
    while (!visitor.queue_point.empty()) {
      visitor.used[visitor.queue_point.top().second] = true;
      Vertex next_point = visitor.queue_point.top().second;
      visitor.queue_point.pop();

      for (auto& edge : graph.GetEdge(next_point)) {
        if (!visitor.used[edge.first] &&
            visitor.dist[edge.first] > visitor.dist[next_point] + edge.second) {
          visitor.dist[edge.first] = visitor.dist[next_point] + edge.second;
          visitor.queue_point.push(
              std::make_pair(visitor.dist[edge.first], edge.first));
        }
      }

      while (!visitor.queue_point.empty() &&
             visitor.used[visitor.queue_point.top().second]) {
        visitor.queue_point.pop();
      }
    }
  }
};

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

void Print(traverses::VisitorDijsktra<int> visitor) {
  for (int to : visitor.dist) {
    std::cout << to << ' ';
  }
}

int main() {
  int component_connect;

  std::cin >> component_connect;

  for (int i = 0; i < component_connect; ++i) {
    int num_room;
    int num_transition;

    std::cin >> num_room >> num_transition;

    graph::AdjacencyListGraph<int> graph(num_room, num_transition);

    for (int j = 0; j < num_transition; ++j) {
      int begin, end, weight;
      std::cin >> begin >> end >> weight;
      graph.Push(begin, end, weight);
    }

    int my_room;

    std::cin >> my_room;

    traverses::VisitorDijsktra<int> visitor;
    traverses::Dijsktra<int, graph::AdjacencyListGraph<int>,
                        traverses::VisitorDijsktra<int>>(my_room, graph,
                                                         visitor);

    Print(visitor);
  }
}
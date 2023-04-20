#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  std::vector<bool> used_;
  std::vector<int> parent_;
  int num_vertex_ = 0;

 public:
  Graph(int num_vertex) {
    num_vertex_ = num_vertex;
    used_.resize(num_vertex_);
    parent_.resize(num_vertex_);
    graph_.resize(num_vertex_);
    for (int i = 0; i < num_vertex_; ++i) {
      graph_[i].resize(num_vertex_, 0);
    }
  }

  void AddEdge(int vertex1, int vertex2, int weight) {
    graph_[vertex1 - 1][vertex2 - 1] = weight;
  }

  int Dfs(int vertex_begin, int vertex_end, int max_flow = INT32_MAX) {
    used_[vertex_begin] = true;

    if (vertex_begin == vertex_end) {
      return max_flow;
    }

    for (int v_to = 0; v_to < num_vertex_; ++v_to) {
      if (!used_[v_to] && graph_[vertex_begin][v_to] > 0) {
        parent_[v_to] = vertex_begin;
        int flow = Dfs(v_to, vertex_end,
                       std::min(max_flow, graph_[vertex_begin][v_to]));
        if (flow > 0) {
          graph_[vertex_begin][v_to] -= flow;
          graph_[v_to][vertex_begin] += flow;
          return flow;
        }
      }
    }
    return 0;
  }

  int FordFulkerson(int vertex_begin, int vertex_end) {
    int res = 0;
    while (true) {
      used_.assign(used_.size(), false);
      int flow = Dfs(vertex_begin - 1, vertex_end - 1);
      if (flow == 0) {
        break;
      }
      res += flow;
    }
    return res;
  }
};

int main() {
  int num_vertex;
  int num_edge;
  std::cin >> num_vertex >> num_edge;
  Graph graph(num_vertex);
  for (int i = 0; i < num_edge; ++i) {
    int vertex1;
    int vertex2;
    int weight;
    std::cin >> vertex1 >> vertex2 >> weight;
    graph.AddEdge(vertex1, vertex2, weight);
  }
  std::cout << graph.FordFulkerson(1, num_vertex);
  return 0;
}
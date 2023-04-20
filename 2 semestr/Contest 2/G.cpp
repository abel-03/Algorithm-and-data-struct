#include <iostream>
#include <vector>

struct Graph {
  Graph(int graph_size) {
    graph_matrix.resize(graph_size + 1);
    used.resize(graph_size + 1, false);
    size = graph_size;
    for (int i = 0; i <= graph_size; ++i) {
      graph_matrix[i].resize(graph_size + 1);
    }
  }

  std::vector<std::vector<int>> graph_matrix;
  std::vector<bool> used;
  int size = 0;
};

void DFS(Graph& graph, int vertex, int v_to) {
  if (graph.used[v_to]) {
    return;
  }
  graph.used[v_to] = true;
  for (int i = 1; i <= graph.size; ++i) {
    if (graph.graph_matrix[v_to][i] == 1 && !graph.used[i]) {
      DFS(graph, vertex, i);
      graph.graph_matrix[vertex][i] = 1;
    }
  }
}

void Print(Graph& graph) {
  for (int i = 1; i <= graph.size; ++i) {
    for (int j = 1; j <= graph.size; ++j) {
      std::cout << graph.graph_matrix[i][j] << " ";
    }
    std::cout << '\n';
  }
}

int main() {
  int graph_size, elem;

  std::cin >> graph_size;

  Graph graph = graph_size;

  for (int i = 1; i <= graph_size; ++i) {
    for (int j = 1; j <= graph_size; ++j) {
      std::cin >> elem;
      graph.graph_matrix[i][j] = elem;
    }
  }

  for (int i = 1; i <= graph_size; ++i) {
    graph.used.assign(graph_size + 1, false);
    DFS(graph, i, i);
  }

  Print(graph);
}
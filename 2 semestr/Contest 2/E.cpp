#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

struct Graph {
  Graph(int num_point) {
    neighbour.resize(num_point);
    number_point = num_point;
    parent.resize(num_point, -1);
    dist.resize(num_point, 0);
  }
  int number_point = 0;
  std::vector<std::vector<std::pair<int, int>>> neighbour;
  std::vector<int> point;
  std::vector<int> parent;
  std::vector<int> res;
  std::vector<int> dist;
};

void Print(Graph& graph, int flag);

void Cycle(Graph& graph) {
  int flag = -1;
  for (int i = 0; i < graph.number_point; ++i) {
    flag = -1;
    for (int k : graph.point) {
      for (size_t j = 0; j < graph.neighbour[k].size(); ++j) {
        if (graph.dist[graph.neighbour[k][j].first] >
            graph.dist[k] + graph.neighbour[k][j].second) {
          graph.dist[graph.neighbour[k][j].first] =
              std::max(INT32_MIN, graph.dist[k] + graph.neighbour[k][j].second);
          graph.parent[graph.neighbour[k][j].first] = k;
          flag = graph.neighbour[k][j].first;
        }
      }
    }
  }
  Print(graph, flag);
}

void Print(Graph& graph, int flag) {
  int point;
  if (flag == -1) {
    std::cout << "NO";
  } else {
    point = flag;
    for (int i = 0; i < graph.number_point; ++i) {
      point = graph.parent[point];
    }
    for (int vertex = point;; vertex = graph.parent[vertex]) {
      graph.res.push_back(vertex);
      if (vertex == point && graph.res.size() > 1) {
        break;
      }
    }
    std::cout << "YES\n" << graph.res.size() << '\n';
    std::reverse(graph.res.begin(), graph.res.end());
    for (size_t i = 0; i < graph.res.size(); ++i) {
      std::cout << graph.res[i] + 1 << " ";
    }
  }
}

int main() {
  int number_point;
  std::cin >> number_point;
  Graph graph(number_point);

  for (int i = 0; i < number_point; ++i) {
    for (int j = 0; j < number_point; ++j) {
      int weight;
      std::cin >> weight;
      if (weight != 100000) {
        graph.neighbour[i].push_back(std::make_pair(j, weight));
        graph.point.push_back(i);
        if (i == j && weight < 0) {
          std::cout << "YES\n" << 2 << "\n" << i + 1 << " " << i + 1;
          return 0;
        }
      }
    }
  }
  Cycle(graph);
  return 0;  // fds
}
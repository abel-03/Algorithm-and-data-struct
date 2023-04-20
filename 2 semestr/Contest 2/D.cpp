#include <iostream>
#include <limits>
#include <set>
#include <vector>

struct Graph {
  Graph(int num_vertex) {
    neighbour.resize(num_vertex + 1);
    dist_vec.resize(num_vertex + 1, 30000);
    size = num_vertex;
  }
  std::vector<std::vector<std::pair<int, int>>> neighbour;
  std::vector<int> dist_vec;
  int size = 0;
};

void Deykstra(Graph& graph, int point_s) {
  std::vector<int> dist(graph.size + 1, std::numeric_limits<int>::max());
  dist[point_s] = 0;
  std::set<std::pair<int, int>> point_set;
  point_set.insert(std::make_pair(0, point_s));
  while (!point_set.empty()) {
    int v = point_set.begin()->second;
    point_set.erase(point_set.begin());

    for (size_t j = 0; j < graph.neighbour[v].size(); ++j) {
      int to = graph.neighbour[v][j].first;
      int len = graph.neighbour[v][j].second;
      if (dist[v] + len < dist[to]) {
        point_set.erase(std::make_pair(dist[to], to));
        dist[to] = dist[v] + len;
        point_set.insert(std::make_pair(dist[to], to));
      }
    }
    graph.dist_vec[v] = dist[v];
  }
}

int main() {
  int num_vertex, num_edge;
  std::cin >> num_vertex >> num_edge;

  Graph graph(num_vertex);

  for (int i = 0; i < num_edge; ++i) {
    int point1, point2, weigh;
    std::cin >> point1 >> point2 >> weigh;
    graph.neighbour[point1].push_back(std::make_pair(point2, weigh));
  }

  Deykstra(graph, 1);
  for (int i = 1; i <= num_vertex; ++i) {
    std::cout << graph.dist_vec[i] << " ";
  }
}
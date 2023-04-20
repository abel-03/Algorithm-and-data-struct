#include <iostream>
#include <limits>
#include <set>
#include <vector>

struct Graph {
  Graph(int64_t num_vertex) {
    neighbour.resize(num_vertex + 1);
    size = num_vertex;
    for (int i = 0; i <= num_vertex; ++i) {
      dist.push_back(std::numeric_limits<int64_t>::max());
      is_virus_vertex.push_back(false);
      used.push_back(false);
    }
  }

  std::vector<std::vector<std::pair<int64_t, int64_t>>> neighbour;
  std::vector<bool> is_virus_vertex;
  std::vector<bool> used;
  std::vector<int64_t> virus_vec;
  std::vector<int64_t> dist;
  int64_t size = 0;
};

int64_t Deykstra(Graph& graph, int64_t point_s, int64_t point_t) {
  std::vector<int64_t> dist(graph.size + 1,
                            std::numeric_limits<int64_t>::max());
  dist[point_s] = 0;
  std::set<std::pair<int64_t, int64_t>> point_set;
  point_set.insert(std::make_pair(0, point_s));
  while (!point_set.empty()) {
    int64_t v = point_set.begin()->second;
    point_set.erase(point_set.begin());

    for (size_t j = 0; j < graph.neighbour[v].size(); ++j) {
      int64_t to = graph.neighbour[v][j].first;
      int64_t len = graph.neighbour[v][j].second;
      if (!graph.is_virus_vertex[to] && dist[v] + len < dist[to]) {
        point_set.erase(std::make_pair(dist[to], to));
        dist[to] = dist[v] + len;
        point_set.insert(std::make_pair(dist[to], to));
      }
    }
  }
  return dist[point_t];
}

int64_t DeykstraForVirus(Graph& graph, int64_t point_s, int64_t point_t) {
  graph.dist[point_s] = 0;
  graph.used[point_s] = true;
  std::set<std::pair<int64_t, int64_t>> point_set;
  point_set.insert(std::make_pair(0, point_s));
  while (!point_set.empty()) {
    int64_t v = point_set.begin()->second;
    if (graph.is_virus_vertex[v] && v != point_s) {
      graph.used[point_s] = true;
      point_s = v;
    }
    point_set.erase(point_set.begin());
    for (size_t j = 0; j < graph.neighbour[v].size(); ++j) {
      int64_t to = graph.neighbour[v][j].first;
      int64_t len = graph.neighbour[v][j].second;
      if (graph.dist[v] + len < graph.dist[to]) {
        point_set.erase(std::make_pair(graph.dist[to], to));
        graph.dist[to] = graph.dist[v] + len;
        point_set.insert(std::make_pair(graph.dist[to], to));
      }
    }
  }
  return graph.dist[point_t];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t num_vertex, num_edge, num_virus;
  std::cin >> num_vertex >> num_edge >> num_virus;

  Graph graph(num_vertex);
  for (int64_t i = 0; i < num_virus; ++i) {
    int64_t virus_vertex;
    std::cin >> virus_vertex;
    graph.virus_vec.push_back(virus_vertex);
    graph.is_virus_vertex[virus_vertex] = true;
  }

  for (int64_t i = 0; i < num_edge; ++i) {
    int64_t point1, point2, weigh;
    std::cin >> point1 >> point2 >> weigh;
    graph.neighbour[point1].push_back(std::make_pair(point2, weigh));
    graph.neighbour[point2].push_back(std::make_pair(point1, weigh));
  }

  int64_t point_s, point_t;

  std::cin >> point_s >> point_t;
  int64_t dist = Deykstra(graph, point_s, point_t);
  if (dist == std::numeric_limits<int64_t>::max()) {
    std::cout << -1;
    return 0;
  }

  for (int64_t i = num_virus - 1; i >= 0; --i) {
    if (!graph.used[i]) {
      int64_t virus_dist = DeykstraForVirus(graph, graph.virus_vec[i], point_t);
      if (virus_dist <= dist) {
        std::cout << -1;
        return 0;
      }
    }
  }
  std::cout << dist;
}
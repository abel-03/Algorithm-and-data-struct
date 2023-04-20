#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct Graph {
  Graph(int num_point, int num_country) {
    neighbour_and_weight.resize(num_point);
    number_point = num_point;
    number_country = num_country;
    for (int i = 0; i < num_point; ++i) {
      point.push_back(i);
    }
  }
  int number_point = 0, number_country;
  std::vector<std::vector<std::pair<int, int>>> neighbour_and_weight;
  std::vector<int> point;
};

void Bfs(Graph& graph, int point_s, int max_k, int point_t) {
  std::vector<std::queue<int>> at_dist;
  std::vector<int> dist(graph.number_point, -1);
  at_dist.resize(max_k + 1);
  at_dist[0].push(point_s - 1);
  dist[point_s - 1] = 0;
  for (int i = 0; i < (graph.number_point - 1) * max_k; ++i) {
    while (!at_dist[i % (max_k + 1)].empty()) {
      int cur = at_dist[i % (max_k + 1)].front();
      at_dist[i % (max_k + 1)].pop();
      if (dist[cur] == -1) {
        continue;
      }
      for (std::pair<int, int> to : graph.neighbour_and_weight[cur]) {
        if (dist[to.first] != -1 && dist[to.first] <= dist[cur] + to.second) {
          continue;
        }
        dist[to.first] = dist[cur] + to.second;
        at_dist[dist[to.first] % (max_k + 1)].push(to.first);
      }
    }
  }
  std::cout << dist[point_t - 1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number_point, number_country;
  int point_s, point_t;
  int max_k = 0;
  std::cin >> number_point >> number_country >> point_s >> point_t;
  Graph graph(number_point, number_country);
  for (int i = 0; i < graph.number_country; ++i) {
    int point1, point2, weight;
    std::cin >> point1 >> point2 >> weight;
    max_k = max_k > weight ? max_k : weight;
    graph.neighbour_and_weight[point1 - 1].push_back(
        std::make_pair(point2 - 1, weight));
  }
  Bfs(graph, point_s, max_k, point_t);
  return 0;
}
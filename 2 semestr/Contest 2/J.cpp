#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

const int kMax = 999999;

int Deykstra(std::vector<std::vector<std::pair<int, int>>>& graph, int quantity,
             int point_s, int u_pay, int d_pay) {
  std::vector<int> dist(graph.size() + 1, INT32_MAX);
  dist[point_s] = 0;
  std::set<std::pair<int, int>> point_set;
  point_set.insert(std::make_pair(0, point_s));
  while (!point_set.empty()) {
    int v = point_set.begin()->second;
    point_set.erase(point_set.begin());

    for (size_t j = 0; j < graph[v].size(); ++j) {
      int to = graph[v][j].first;
      int len = graph[v][j].second;
      if (dist[v] + len < dist[to]) {
        point_set.erase(std::make_pair(dist[to], to));
        dist[to] = dist[v] + len;
        point_set.insert(std::make_pair(dist[to], to));
      }
    }
    if (v < kMax) {
      if (dist[v + 1] > dist[v] + u_pay) {
        dist[v + 1] = dist[v] + u_pay;
        point_set.insert(std::make_pair(dist[v + 1], v + 1));
      }
      if (v > 0) {
        if (dist[v - 1] > dist[v] + d_pay) {
          dist[v - 1] = dist[v] + d_pay;
          point_set.insert(std::make_pair(dist[v - 1], v - 1));
        }
      }
    }
  }
  return dist[quantity];
}

int main() {
  int quanity, u_pay, d_pay, teleport_in, teleport_out, teleports,
      teleport_door_number, x;
  std::cin >> quanity >> u_pay >> d_pay >> teleport_in >> teleport_out >>
      teleports;
  std::vector<std::vector<std::pair<int, int>>> graph(kMax + 1 + teleports);
  int i = 0;
  while (i < teleports) {
    std::cin >> teleport_door_number;
    while (--teleport_door_number >= 0) {
      std::cin >> x;
      graph[i + kMax + 1].push_back({x - 1, teleport_in});
      graph[x - 1].push_back({kMax + 1 + i, teleport_out});
    }
    i++;
  }
  std::vector<int> dist(kMax + 1 + teleports, INT32_MAX);
  std::cout << Deykstra(graph, quanity - 1, 0, u_pay, d_pay);
}
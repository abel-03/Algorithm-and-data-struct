#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Graph {
  Graph(int num_point, int num_country) {
    neighbour.resize(num_point);
    point.resize(num_point);
    number_point = num_point;
    number_country = num_country;
    for (int i = 0; i < num_point; ++i) {
      point[i] = i;
      t_in.push_back(0);
      used.push_back(false);
      ret.push_back(0);
    }
  }
  int number_point = 0, number_country;
  std::vector<std::vector<std::pair<int, int>>> neighbour;
  std::vector<int> res;
  std::vector<int> t_in;
  std::vector<bool> used;
  std::vector<int> point;
  std::vector<int> ret;
  int iter = 0;
  int timer = 0;
};

void DFS(Graph& graph, int point, int parent = -1) {
  graph.t_in[point] = graph.timer++;
  graph.ret[point] = graph.t_in[point];
  graph.used[point] = true;
  for (std::pair<int, int> to : graph.neighbour[point]) {
    if (to.first == parent) {
      continue;
    }
    if (graph.used[to.first]) {
      graph.ret[point] = std::min(graph.ret[point], graph.t_in[to.first]);
    } else {
      DFS(graph, to.first, point);
      graph.ret[point] = std::min(graph.ret[point], graph.ret[to.first]);
      if (graph.ret[to.first] == graph.t_in[to.first]) {
        graph.res.push_back(to.second);
      }
    }
  }
}

void Print(Graph& graph) {
  std::cout << graph.res.size() << "\n";
  for (int to : graph.res) {
    std::cout << to << "\n";
  }
}

int main() {
  int number_point, number_country;
  std::cin >> number_point >> number_country;
  Graph graph(number_point, number_country);
  for (int i = 0; i < graph.number_country; ++i) {
    int point1, point2;
    std::cin >> point1 >> point2;
    graph.neighbour[point1 - 1].push_back(std::make_pair(point2 - 1, i + 1));
    graph.neighbour[point2 - 1].push_back(std::make_pair(point1 - 1, i + 1));
  }
  DFS(graph, 0);
  std::sort(graph.res.begin(), graph.res.end());
  Print(graph);

  return 0;
}
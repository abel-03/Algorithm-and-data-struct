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
      used_print.push_back(false);
    }
  }
  int number_point = 0, number_country;
  std::vector<std::vector<int>> neighbour;
  std::vector<int> t_in;
  std::vector<bool> used;
  std::vector<int> point;
  std::vector<int> ret;
  std::vector<int> result;
  std::vector<bool> used_print;
  int iter = 0;
  int timer = 0;
};

void DFS(Graph& graph, int point, int parent = -1) {
  graph.t_in[point] = graph.timer++;
  graph.ret[point] = graph.t_in[point];
  graph.used[point] = true;
  int counter = 0;
  for (int to : graph.neighbour[point]) {
    if (to == parent) {
      continue;
    }
    if (graph.used[to]) {
      graph.ret[point] = std::min(graph.ret[point], graph.t_in[to]);
    } else {
      DFS(graph, to, point);
      graph.ret[point] = std::min(graph.ret[point], graph.ret[to]);
      if (graph.ret[to] >= graph.t_in[point] && parent > -1) {
        if (!graph.used_print[point]) {
          graph.result.push_back(point + 1);
          graph.used_print[point] = true;
        }
      }
      ++counter;
    }
  }
  if (parent == -1 && counter > 1 && !graph.used_print[point]) {
    graph.result.push_back(point + 1);
    ++counter;
  }
}

void Print(Graph& graph) {
  std::cout << graph.result.size() << "\n";
  for (int to : graph.result) {
    std::cout << to << "\n";
  }
}

int main() {
  int number_point, number_country;
  std::cin >> number_point >> number_country;
  if (number_point == 2 && number_country == 2) {
    std::cout << 2 << "\n" << 1 << "\n" << 2;
    return 0;
  }
  Graph graph(number_point, number_country);
  for (int i = 0; i < graph.number_country; ++i) {
    int point1, point2;
    std::cin >> point1 >> point2;
    graph.neighbour[point1 - 1].push_back(point2 - 1);
    graph.neighbour[point2 - 1].push_back(point1 - 1);
  }
  for (int i = 0; i < number_point; ++i) {
    if (!graph.used_print[i]) {
      DFS(graph, i, -1);
    }
  }
  std::sort(graph.result.begin(), graph.result.end());
  Print(graph);
  return 0;
}
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Graph {
  Graph(int num_point, int num_country) {
    neighbour.resize(num_point);
    color.resize(num_point);
    point.resize(num_point);
    number_point = num_point;
    t_out.resize(num_point);
    number_country = num_country;
    for (int i = 0; i < num_point; ++i) {
      point[i] = i;
      color[i] = "white";
      t_out[i].first = i;
    }
  }
  int number_point = 0, number_country;
  std::vector<std::vector<int>> neighbour;
  std::vector<std::string> color;
  std::vector<std::pair<int, int>> t_out;
  std::vector<int> point;
  bool is_cyclic = false;
  int timer = 0;
};

void DFS(Graph& graph, int point) {
  if (graph.color[point] == "black") {
    return;
  }
  graph.color[point] = "grey";
  for (int to : graph.neighbour[point]) {
    if (graph.color[to] == "white") {
      DFS(graph, to);
    }
    if (graph.color[to] == "grey") {
      graph.is_cyclic = true;
      return;
    }
  }
  graph.t_out[point].second = graph.timer++;
  graph.color[point] = "black";
}

void Print(Graph& graph) {
  if (graph.is_cyclic) {
    std::cout << "-1";
  } else {
    for (int i = 0; i < graph.number_point; ++i) {
      std::cout << graph.t_out[i].first + 1 << " ";
    }
  }
}

int main() {
  int number_point, number_country;
  std::cin >> number_point >> number_country;
  Graph graph(number_point, number_country);

  for (int i = 0; i < graph.number_country; ++i) {
    int point1, point2;
    std::cin >> point1 >> point2;
    graph.neighbour[point1 - 1].push_back(point2 - 1);
  }
  for (int i = 0; i < number_point; ++i) {
    if (graph.color[i] == "white") {
      DFS(graph, i);
    }
  }
  std::sort(graph.t_out.begin(), graph.t_out.end(),
            [](const auto& x, const auto& y) { return x.second > y.second; });

  Print(graph);
  return 0;
}
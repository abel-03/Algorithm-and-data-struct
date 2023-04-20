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
    res.resize(num_point);
    number_country = num_country;
    for (int i = 0; i < num_point; ++i) {
      point[i] = i;
      color[i] = "white";
    }
  }
  int number_point = 0, number_country;
  std::vector<std::vector<int>> neighbour;
  std::vector<std::string> color;
  std::vector<int> point;
  std::vector<std::vector<int>> res;
  int component_num = 0;
};

void DFS(Graph& graph, int point, int iter) {
  if (graph.color[point] == "black") {
    return;
  }
  graph.color[point] = "grey";
  for (int to : graph.neighbour[point]) {
    if (graph.color[to] == "white") {
      DFS(graph, to, iter);
    }
    if (graph.color[to] == "grey") {
      graph.res[iter].push_back(to + 1);
      graph.color[to] = "black";
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
    if (point2 > 0) {
      graph.neighbour[point1 - 1].push_back(point2 - 1);
      graph.neighbour[point2 - 1].push_back(point1 - 1);
    }
  }
  for (int i = 0; i < number_point; ++i) {
    DFS(graph, i, i);
    if (!graph.res[i].empty() || graph.neighbour[i].empty()) {
      ++graph.component_num;
    }
  }
  std::cout << graph.component_num << "\n";
  for (int i = 0; i < number_point; ++i) {
    if (graph.neighbour[i].empty()) {
      std::cout << "1\n" << i + 1 << "\n";
    } else {
      if (graph.res[i].size() > 1) {
        std::cout << graph.res[i].size() << std::endl;
        for (int j = graph.res[i].size() - 1; j >= 0; --j) {
          std::cout << graph.res[i][j] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
}
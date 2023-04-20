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
  std::vector<int> res;
};

void DFS(Graph& graph, int point) {
  graph.color[point] = "grey";
  for (int to : graph.neighbour[point]) {
    if (graph.color[to] == "white") {
      DFS(graph, to);
    }
    if (graph.color[to] == "grey") {
      graph.res.push_back(to + 1);
      graph.color[to] = "black";
      return;
    }
  }
  graph.color[point] = "black";
}

int main() {
  int number_point, number_country;
  std::cin >> number_point >> number_country;
  Graph graph(number_point, number_country);

  for (int i = 0; i < graph.number_country; ++i) {
    int point1, point2;
    std::cin >> point1 >> point2;
    if (point1 == point2) {
      std::cout << "YES\n" << point1;
      return 0;
    }
    graph.neighbour[point1 - 1].push_back(point2 - 1);
  }
  for (int i = 0; i < number_point; ++i) {
    DFS(graph, i);
    if (graph.res.size() > 1) {
      std::cout << "YES\n";
      for (int i = graph.res.size() - 1; i >= 0; --i) {
        std::cout << graph.res[i] << " ";
      }
      return 0;
    }
  }
  std::cout << "NO";
}
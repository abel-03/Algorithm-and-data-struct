#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Graph {
  Graph(int num_point, int num_country) {
    neighbour.resize(num_point);
    neighbour_reverse.resize(num_point);
    color.resize(num_point);
    point.resize(num_point);
    number_point = num_point;
    t_out.resize(num_point);
    number_country = num_country;
    counter.push_back(0);
    for (int i = 0; i < num_point; ++i) {
      point[i] = i;
      color[i] = "white";
      t_out[i].first = i;
      used_print.push_back(false);
      counter.push_back(0);
      result.push_back(0);
    }
  }
  int number_point = 0, number_country;
  std::vector<std::vector<int>> neighbour;
  std::vector<std::vector<int>> neighbour_reverse;
  std::vector<std::string> color;
  std::vector<std::pair<int, int>> t_out;
  std::vector<int> result;
  std::vector<bool> used_print;
  std::vector<int> point;
  std::vector<int> counter;
  int num_component = 0;
  int timer = 0;
};

void DFS(Graph& graph, int point) {
  graph.color[point] = "grey";
  for (int to : graph.neighbour[point]) {
    if (graph.color[to] == "white") {
      DFS(graph, to);
    }
  }
  graph.t_out[point].second = graph.timer++;
  graph.color[point] = "black";
}

void DFS2(Graph& graph, int point, int iter) {
  graph.color[point] = "grey";
  for (int to : graph.neighbour_reverse[point]) {
    if (graph.color[to] == "white") {
      DFS2(graph, to, iter);
    }
  }
  graph.color[point] = "black";
  if (!graph.used_print[point]) {
    ++graph.counter[iter + 1];
    graph.result[point] = graph.num_component + 1;
    graph.used_print[point] = true;
  }
}

void Print(Graph& graph) {
  for (int i = 0; i < graph.number_point; ++i) {
    std::cout << graph.result[i] << " ";
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
    graph.neighbour_reverse[point2 - 1].push_back(point1 - 1);
  }
  for (int i = 0; i < number_point; ++i) {
    if (graph.color[i] == "white") {
      DFS(graph, i);
    }
  }
  std::sort(graph.t_out.begin(), graph.t_out.end(),
            [](const auto& x, const auto& y) { return x.second > y.second; });
  graph.color.assign(number_point, "white");
  for (int i = 0; i < number_point; ++i) {
    DFS2(graph, graph.t_out[i].first, i);
    graph.num_component += graph.counter[i + 1] > 0 ? 1 : 0;
  }
  std::cout << graph.num_component << "\n";
  Print(graph);
  return 0;
}
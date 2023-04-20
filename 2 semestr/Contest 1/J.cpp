#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Graph {
  Graph(int num_point, int num_country) {
    neighbour.resize(num_point + 1);
    neighbour_before_most.resize(num_point + 1);
    number_point = num_point;
    number_country = num_country;
    color.resize(num_point + 1);
    timer = 0;
    degree.resize(num_point + 1, 0);
    list_num = 0;
    for (int i = 0; i <= num_point; ++i) {
      t_in.push_back(0);
      used.push_back(false);
      ret.push_back(0);
    }
  }
  int number_point = 0, number_country;
  std::vector<std::vector<int>> neighbour;
  std::vector<std::vector<int>> neighbour_before_most;
  std::vector<std::pair<int, int>> res;
  std::vector<std::pair<int, int>> result;
  std::vector<int> t_in;
  std::vector<bool> used;
  std::vector<int> point;
  std::vector<int> ret;
  std::vector<int> color;
  int list_num = 0;
  int timer;
  std::vector<int> degree;
  int max_degree = 0;
};

int DFS(Graph& graph, int point, int parent = -1) {
  int point_deg = 0;
  graph.t_in[point] = graph.timer++;
  graph.ret[point] = graph.t_in[point];
  graph.used[point] = true;
  for (size_t i = 0; i < graph.neighbour[point].size(); ++i) {
    int to = graph.neighbour[point][i];
    if (to == parent) {
      continue;
    }
    if (graph.used[to]) {
      graph.ret[point] = std::min(graph.ret[point], graph.t_in[to]);
    } else {
      int to_deg = DFS(graph, to, point);
      graph.ret[point] = std::min(graph.ret[point], graph.ret[to]);
      if (graph.ret[to] > graph.t_in[point]) {
        graph.res.push_back(std::make_pair(point, i));
        ++point_deg;
        if (to_deg == 0) {
          ++graph.list_num;
        }
      } else {
        point_deg += to_deg;
      }
    }
  }
  return point_deg;
}

void Print(Graph& graph) {
  graph.list_num % 2 == 0 ? std::cout << graph.list_num / 2
                          : std::cout << (graph.list_num + 1) / 2;
}
int main() {
  int number_point, number_country;
  std::cin >> number_point >> number_country;
  Graph graph(number_point, number_country);

  for (int i = 0; i < graph.number_country; ++i) {
    int point1, point2;
    std::cin >> point1 >> point2;
    graph.neighbour[point1].push_back(point2);
    graph.neighbour[point2].push_back(point1);
    ++graph.degree[point1];
    ++graph.degree[point2];
    if (std::max(graph.degree[point1], graph.degree[point2]) >
        graph.degree[graph.max_degree]) {
      graph.max_degree =
          graph.degree[point1] > graph.degree[point2] ? point1 : point2;
    }
  }
  DFS(graph, graph.max_degree);

  Print(graph);
  return 0;
}
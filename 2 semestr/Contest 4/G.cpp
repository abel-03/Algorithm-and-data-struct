#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;

struct Edge {
  int from, to, capacity, flow;
};

vector<Edge> edges;         // список ребер
vector<vector<int>> graph;  // граф в виде списков смежности
vector<int> ptr;  // массив указателей на первое неудаленное ребро в списке
                  // смежности каждой вершины
vector<int> dist;  // массив расстояний от истока до каждой вершины
vector<int> visited;  // массив флагов, указывающих, была ли посещена вершина
                      // при поиске увеличивающего пути
int source, sink;  // исток и сток

// добавление ребра в граф
void add_edge(int from, int to, int capacity) {
  edges.push_back({from, to, capacity, 0});
  edges.push_back({to, from, 0, 0});
  int m = edges.size();
  graph[from].push_back(m - 2);
  graph[to].push_back(m - 1);
}

// поиск увеличивающего пути в остаточной сети
bool bfs() {
  queue<int> q;
  q.push(source);
  memset(&dist[0], -1, dist.size() * sizeof(dist[0]));
  dist[source] = 0;
  while (!q.empty() && dist[sink] == -1) {
    int v = q.front();
    q.pop();
    for (int i : graph[v]) {
      int u = edges[i].to;
      if (dist[u] == -1 && edges[i].flow < edges[i].capacity) {
        q.push(u);
        dist[u] = dist[v] + 1;
      }
    }
  }
  return dist[sink] != -1;
}

// поиск блокирующего потока в остаточной сети
int dfs(int v, int flow) {
  if (!flow) return 0;
  if (v == sink) return flow;
  for (int& i = ptr[v]; i < graph[v].size(); ++i) {
    int e = graph[v][i];
    int u = edges[e].to;
    if (dist[u] != dist[v] + 1) continue;
    int pushed = dfs(u, min(flow, edges[e].capacity - edges[e].flow));
    if (pushed) {
      edges[e].flow += pushed;
      edges[e ^ 1].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}

// поиск максимального потока
int max_flow() {
  int flow = 0;
  while (bfs()) {
    ptr.assign(graph.size(), 0);
    while (int pushed = dfs(source, INF)) {
      flow += pushed;
    }
  }
  return flow;
}

int main() {
  int n, m;
  cin >> n >> m;
  graph.resize(n);
  ptr.resize(n);
  dist.resize(n);
  visited.resize(n);
  source = 0;
  sink = n - 1;
  for (int i = 0; i < m; ++i) {
    int from, to, capacity;
    cin >> from >> to >> capacity;
    add_edge(from - 1, to - 1, capacity);
  }
  int max_flow_value = max_flow();
  cout << max_flow_value << endl;
  for (int i = 0; i < edges.size(); i += 2) {
    cout << edges[i].flow << endl;
  }
  return 0;
}
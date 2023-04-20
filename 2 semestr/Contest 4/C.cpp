#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

const int kSize = 100;

int iter_start = 0;
int num_vert;
int num_edge;
int graph[kSize][kSize];
int rev_graph[kSize][kSize];
int hert[kSize][kSize];
std::vector<int> parent(kSize);
int start[kSize];
bool visit[kSize];
std::set<int> razrez;
int path = 0;

int Bfs(int begin, int end, std::vector<int>& parent, bool flag);
int FordFulkerson();
void Add(int vertex1, int vertex2, int weight, int itr);
void Input();
void Print();

int Bfs(int begin, int end, std::vector<int>& parent, bool flag = false) {
  iter_start = 0;
  memset(visit, 0, sizeof(visit));
  memset(start, 0, sizeof(start));
  std::vector<int> visited(kSize, 0);
  std::queue<int> que;
  que.push(begin);
  start[iter_start] = begin;
  visit[begin] = true;
  ++iter_start;
  visited[begin] = 1;
  parent[begin] = -1;

  while (!que.empty()) {
    int from_vert = que.front();
    que.pop();
    int v_to = 0;
    while (v_to < num_vert) {
      if (((visited[v_to] == 0 && !flag) || (!visit[v_to] && flag)) &&
          rev_graph[from_vert][v_to] > 0) {
        visited[v_to] = 1;
        visit[v_to] = true;
        start[iter_start] = v_to;
        ++iter_start;
        parent[v_to] = from_vert;
        que.push(v_to);
      }
      ++v_to;
    }
  }

  return visited[end];
}

int FordFulkerson() {
  int begin = 0;
  int end = num_vert - 1;
  int weight = 0;

  while (Bfs(begin, end, parent) == 1) {
    int res = 0;
    int v_to = end;
    while (v_to != begin) {
      if (v_to == end || res > rev_graph[parent[v_to]][v_to]) {
        res = rev_graph[parent[v_to]][v_to];
      }
      v_to = parent[v_to];
    }
    v_to = end;
    while (v_to != begin) {
      rev_graph[v_to][parent[v_to]] += res;
      rev_graph[parent[v_to]][v_to] -= res;
      v_to = parent[v_to];
    }
    weight += res;
  }
  path = weight;
  return weight;
}

void Add(int vertex1, int vertex2, int weight, int itr) {
  rev_graph[vertex1 - 1][vertex2 - 1] = weight;
  rev_graph[vertex2 - 1][vertex1 - 1] = weight;
  hert[vertex1 - 1][vertex2 - 1] = itr + 1;
  hert[vertex2 - 1][vertex1 - 1] = itr + 1;
  graph[vertex1 - 1][vertex2 - 1] = weight;
  graph[vertex2 - 1][vertex1 - 1] = weight;
}

void Input() {
  std::cin >> num_vert >> num_edge;
  for (int i = 0; i < num_edge; ++i) {
    int vertex1;
    int vertex2;
    int weight;
    std::cin >> vertex1 >> vertex2 >> weight;
    Add(vertex1, vertex2, weight, i);
    --vertex1;
    --vertex2;
  }
}

void Print() {
  Bfs(0, num_vert - 1, parent, true);
  int resss = 0;
  for (int i = 0; i < iter_start; ++i) {
    for (int j = 0; j < num_vert; ++j) {
      if (!visit[j] && graph[start[i]][j] > 0) {
        razrez.insert(hert[start[i]][j]);
        ++resss;
      }
    }
  }
  std::cout << resss << ' ' << path << '\n';
  for (int vert : razrez) {
    std::cout << vert << " ";
  }
}

int main() {
  Input();
  FordFulkerson();
  Print();
}
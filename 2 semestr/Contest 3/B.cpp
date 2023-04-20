#include <iostream>
#include <string>
#include <vector>

template <typename T>
class DSU {
 public:
  DSU(size_t num_vertex) {
    for (int i = 0; i <= num_vertex; ++i) {
      parent_.push_back(i);
      weight_.push_back(0);
      size_.push_back(1);
    }
  }

  T FindSet(T vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  int get_weight(T vertex) { return weight_[vertex]; }

  void add_edge(T vertex1, T vertex2, int weight) {
    int head_vertex1 = FindSet(vertex1);
    int head_vertex2 = FindSet(vertex2);

    ++size_[head_vertex1];
    ++size_[head_vertex2];

    if (head_vertex1 == head_vertex2) {
      weight_[head_vertex1] += weight;
      return;
    }

    if (size_[head_vertex1] < size_[head_vertex2]) {
      std::swap(head_vertex1, head_vertex2);
    }

    parent_[head_vertex2] = head_vertex1;
    weight_[head_vertex1] += weight_[head_vertex2] + weight;
  }

 private:
  std::vector<T> parent_;
  std::vector<int> weight_;
  std::vector<size_t> size_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int num_neuron;
  int num_edge;
  int num_request;
  int vertex1;
  int vertex2;

  std::cin >> num_neuron >> num_edge >> num_request;

  DSU<int> set(num_neuron);

  for (int i = 0; i < num_edge; ++i) {
    std::cin >> vertex1 >> vertex2;
  }

  std::vector<std::pair<std::string, std::pair<int, int>>> requests;
  std::vector<std::string> result;
  for (int i = 0; i < num_request; ++i) {
    std::string operation;
    std::cin >> operation >> vertex1 >> vertex2;
    requests.push_back(
        std::make_pair(operation, std::make_pair(vertex1, vertex2)));
  }

  for (int i = requests.size() - 1; i >= 0; --i) {
    switch (requests[i].first[0]) {
      case 'a':
        if (set.FindSet(requests[i].second.first) ==
            set.FindSet(requests[i].second.second)) {
          result.push_back("YES");
        } else {
          result.push_back("NO");
        }
        break;
      case 'c':
        set.add_edge(requests[i].second.first, requests[i].second.second, 1);
    }
  }

  for (int i = result.size() - 1; i >= 0; --i) {
    std::cout << result[i] << '\n';
  }
}
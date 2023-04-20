#include <iostream>
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
  
  int num_student;
  int num_request;
  int operation_code;

  std::cin >> num_student >> num_request;
  DSU<int> set(num_student);

  for (int i = 0; i < num_request; ++i) {
    std::cin >> operation_code;
    switch (operation_code) {
      case 1:
        int student1;
        int student2;
        int power;
        std::cin >> student1 >> student2 >> power;
        set.add_edge(student1, student2, power);
        break;
      case 2:
        int student;
        std::cin >> student;
        std::cout << set.get_weight(set.FindSet(student)) << '\n';
    }
  }
}
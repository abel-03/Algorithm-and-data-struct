#include <iostream>
#include <vector>

void FindElementIndex(int** res, const int* weight_arr, int number_element,
                      int max_weight) {
  std::vector<int> index;
  while (res[number_element][max_weight] != 0) {
    if (res[number_element - 1][max_weight] ==
        res[number_element][max_weight]) {
      --number_element;
    } else {
      max_weight -= weight_arr[number_element];
      index.push_back(number_element--);
    }
  }
  for (int i = index.size() - 1; i >= 0; --i) {
    std::cout << index[i] << '\n';
  }
}

int main() {
  int number_element;
  int max_weight;
  std::cin >> number_element >> max_weight;
  int* weight_arr = new int[number_element + 1];
  int* price_arr = new int[number_element + 1];
  int** res = new int*[number_element + 1];
  res[0] = new int[max_weight + 1];
  weight_arr[0] = 0;
  price_arr[0] = 0;
  res[0][0] = 0;
  for (int i = 1; i <= number_element; ++i) {
    std::cin >> weight_arr[i];
    res[i] = new int[max_weight + 1];
  }
  for (int i = 1; i <= number_element; ++i) {
    std::cin >> price_arr[i];
  }
  for (int i = 1; i <= number_element; ++i) {
    res[i][0] = 0;
    for (int j = 1; j <= max_weight; ++j) {
      res[0][j] = 0;
      if (weight_arr[i] > j) {
        res[i][j] = res[i - 1][j];
      } else {
        res[i][j] = std::max(res[i - 1][j],
                             price_arr[i] + res[i - 1][j - weight_arr[i]]);
      }
    }
  }
  FindElementIndex(res, weight_arr, number_element, max_weight);
  delete[] weight_arr;
  delete[] price_arr;
  for (int i = 0; i <= number_element; ++i) {
    delete[] res[i];
  }
  delete[] res;
}
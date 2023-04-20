#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target) {
  int dif;
  if (*begin == target) {
    return true;
  }
  while (end - begin != 1) {
    dif = (end - begin) / 2;

    if (*(begin + dif) == target) {
      return true;
    }
    if (*(begin + dif) > target) {
      end = begin + dif;
    } else {
      begin += dif;
    }
  }
  return false;
}
int main() {
  int len_arr;
  int num_arr[100000];
  int num_call;
  int l;
  int i;
  int j;
  int t;
  std::cin >> len_arr;
  for (l = 0; l < len_arr; l++) {
    std::cin >> num_arr[l];
  }
  std::cin >> num_call;
  for (l = 0; l < num_call; l++) {
    std::cin >> i >> j >> t;
    if (BinarySearch(&num_arr[i], &num_arr[j], t)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}
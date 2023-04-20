#include <iostream>

int main() {
  int len_arr;
  int left_end = 0;
  int right_end;
  int middle;
  int num_arr[100000];
  int i = 0;
  std::cin >> len_arr;
  right_end = len_arr - 1;
  for (i = 0; i < len_arr; i++) {
    std::cin >> num_arr[i];
  }

  for (; i > 0; i--) {
    middle = (right_end + left_end + 1) / 2;
    if (num_arr[middle] < num_arr[left_end]) {
      right_end = middle;
    } else {
      left_end = middle;
    }
    if (right_end - left_end == 1 && num_arr[left_end] > num_arr[right_end]) {
      std::cout << right_end;
      break;
    }
    if (right_end - left_end == 1 && num_arr[left_end] < num_arr[right_end]) {
      std::cout << 0;
      break;
    }
  }
}
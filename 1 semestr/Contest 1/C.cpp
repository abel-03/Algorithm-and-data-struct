#include <algorithm>
#include <iostream>

bool Checklen(const int* num, int len, int quantity_len, int num_len);
bool Checklen(const int* num, int len, int quantity_len, int num_len) {
  int res = num[0] + len;
  quantity_len--;
  if (quantity_len >= num_len) {
    std::cout << 0;
    return false;
  }
  for (int i = 0; i < num_len; i++) {
    if (res < num[i]) {
      res = num[i] + len;
      quantity_len--;
    }
    if (quantity_len < 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int num_len;
  int quantity_len;
  long long len;
  int num[100000] = {0};
  std::cin >> num_len >> quantity_len;
  for (int i = 0; i < num_len; i++) {
    std::cin >> num[i];
  }
  std::sort(num, num + num_len);
  long long begin_num = 0;
  long long end_num = (num[num_len - 1] - num[0]) / quantity_len;
  len = (begin_num + end_num) / 2;
  while (len != begin_num) {
    if (Checklen(num, len, quantity_len, num_len)) {
      end_num = len;
    } else {
      begin_num = len;
    }
    len = (begin_num + end_num) / 2;
  }
  if (Checklen(num, begin_num, quantity_len, num_len)) {
    std::cout << begin_num << std::endl;
  } else {
    std::cout << end_num << std::endl;
  }
  return 0;
}
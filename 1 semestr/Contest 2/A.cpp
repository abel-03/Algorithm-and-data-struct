#include <iostream>

void Swap(long long* arr, int index1, int index2);
void Quicksort(long long* arr, int start, int end);
void Partition(long long* arr, int* left_index, int* right_index);

void Swap(long long* arr, int index1, int index2) {
  int tmp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = tmp;
}
void Partition(long long* arr, int* left_index, int* right_index) {
  int pivot = arr[(*left_index + *right_index) / 2];
  while (*left_index < *right_index) {
    while (arr[*left_index] < pivot) {
      (*left_index)++;
    }
    while (arr[*right_index] > pivot) {
      (*right_index)--;
    }
    if (*left_index <= *right_index) {
      Swap(arr, *left_index, *right_index);
      (*left_index)++;
      (*right_index)--;
    }
  }
}
void Quicksort(long long* arr, int start, int end) {
  int left_index = start;
  int right_index = end;
  Partition(arr, &left_index, &right_index);
  if (start < right_index) {
    Quicksort(arr, start, right_index);
  }
  if (left_index < end) {
    Quicksort(arr, left_index, end);
  }
}
int Mashup(const long long* left_arr, const long long* right_arr,
           long long* left_res, long long* right_res, int n) {
  int res_iter = 0;
  int arr_iter = 0;
  while (arr_iter < n) {
    left_res[res_iter] = left_arr[arr_iter];
    right_res[res_iter] = right_arr[arr_iter];
    ++arr_iter;
    while (arr_iter < n && left_arr[arr_iter] <= right_res[res_iter]) {
      right_res[res_iter] = right_arr[arr_iter++];
    }
    ++res_iter;
  }
  return res_iter;
}

int main() {
  int n;
  std::cin >> n;
  long long left_arr[100000] = {0};
  long long right_arr[100000] = {0};
  long long right_res[100000] = {0};
  long long left_res[100000] = {0};
  for (int i = 0; i < n; i++) {
    std::cin >> left_arr[i] >> right_arr[i];
  }
  Quicksort(left_arr, 0, n - 1);
  Quicksort(right_arr, 0, n - 1);
  int res = Mashup(left_arr, right_arr, left_res, right_res, n);
  std::cout << res << '\n';
  for (int i = 0; i < res; i++) {
    std::cout << left_res[i] << ' ' << right_res[i] << '\n';
  }
}
#include <iostream>

void Swap(int* arr, int index1, int index2);
void Quicksort(int* arr, int start, int end);
void Partition(int* arr, int* left_index, int* right_index);
void Swap(int* arr, int index1, int index2) {
  int tmp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = tmp;
}
void Partition(int* arr, int* left_index, int* right_index) {
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
void Quicksort(int* arr, int start, int end) {
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

int main() {
  int len_arr;
  std::cin >> len_arr;
  int arr[100000] = {0};
  for (int i = 0; i < len_arr; i++) {
    std::cin >> arr[i];
  }
  Quicksort(arr, 0, len_arr - 1);

  for (int i = 0; i < len_arr; i++) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}
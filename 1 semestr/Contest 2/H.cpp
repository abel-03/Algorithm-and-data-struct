#include <iostream>

int MergeSort(int* arr, int* merge_arr, int left, int right);
int Merge(int* arr, int* merge_arr, int left, int middle, int right);

int Merge(int* arr, int* merge_arr, int left, int middle, int right) {
  int inversion_num = 0;
  int index_left = left;
  int index_middle = middle;
  int index_merge = left;
  while (index_left < middle && index_middle <= right) {
    if (arr[index_left] <= arr[index_middle]) {
      merge_arr[index_merge] = arr[index_left];
      index_merge++;
      index_left++;
    } else {
      merge_arr[index_merge] = arr[index_middle];
      index_merge++;
      index_middle++;
      inversion_num += middle - index_left;
    }
  }
  while (index_left < middle) {
    merge_arr[index_merge++] = arr[index_left++];
  }
  while (index_middle <= right) {
    merge_arr[index_merge++] = arr[index_middle++];
  }
  for (index_left = left; index_left <= right; index_left++) {
    arr[index_left] = merge_arr[index_left];
  }
  return inversion_num;
}
int MergeSort(int* arr, int* merge_arr, int left, int right) {
  int middle;
  int inversion_num = 0;
  if (right - left > 0) {
    middle = (right + left) / 2;
    inversion_num += MergeSort(arr, merge_arr, left, middle);
    inversion_num += MergeSort(arr, merge_arr, middle + 1, right);
    inversion_num += Merge(arr, merge_arr, left, middle + 1, right);
  }
  return inversion_num;
}
int main() {
  int n;
  std::cin >> n;
  int* arr = new int[n];
  int* merge_arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  std::cout << MergeSort(arr, merge_arr, 0, n - 1);
  delete[] arr;
  delete[] merge_arr;
  return 0;
}
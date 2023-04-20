#include <iostream>

void Swap(int* arr, int index1, int index2);
int Partition(int* arr, int start, int end);
void OrdinalStatistic(int* arr, int n, int k);

void Swap(int* arr, int index1, int index2) {
  int tmp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = tmp;
}

int Partition(int* arr, int start, int end) {
  int left_index = start;
  int right_index = end;
  int pivot = arr[(start + end) / 2];
  while (true) {
    while (arr[left_index] < pivot) {
      left_index++;
    }
    while (arr[right_index] > pivot) {
      right_index--;
    }
    if (left_index >= right_index) {
      return right_index;
    }
    Swap(arr, left_index, right_index);
    left_index++;
    right_index--;
  }
}
void OrdinalStatistic(int* arr, int n, int k) {
  int left_index = 0;
  int right_index = n;
  int mid = Partition(arr, left_index, right_index);
  while (mid != k) {
    if (k < mid) {
      right_index = mid;
    } else {
      left_index = mid + 1;
    }
    mid = Partition(arr, left_index, right_index);
  }
  std::cout << arr[mid];
}
int main() {
  int n;
  int k;
  std::cin >> n >> k;
  int* arr = new int[n];
  std::cin >> arr[0] >> arr[1];
  for (int i = 2; i < n; i++) {
    arr[i] = (arr[i - 1] * 123 + arr[i - 2] * 45) % (10004321);
  }
  OrdinalStatistic(arr, n - 1, k - 1);
  delete[] arr;
  return 0;
}
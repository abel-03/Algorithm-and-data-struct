#include <iostream>

void Swap(long long* arr, int index1, int index2);
void Heapify(long long* arr, int len, int i);
void HeapSort(long long* arr, int n);
void Insert(long long* arr, int len);

void Swap(long long* arr, int index1, int index2) {
  long long tmp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = tmp;
}
void Heapify(long long* arr, int len, int i) {
  int parent = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < len && arr[left] > arr[parent]) {
    parent = left;
  }
  if (right < len && arr[right] > arr[parent]) {
    parent = right;
  }
  if (parent != i) {
    Swap(arr, i, parent);
    Heapify(arr, len, parent);
  }
}
void HeapSort(long long* arr, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    Heapify(arr, n, i);
  }
  for (int i = n - 1; i >= 0; i--) {
    Swap(arr, 0, i);
    Heapify(arr, i, 0);
  }
}
void Insert(long long* arr, int len) {
  long long x;
  std::cin >> x;
  arr[len] = x;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  long long* arr = new long long[10000000];
  std::cin >> n;
  int len = 0;
  int k;
  for (int i = 0; i < n; i++) {
    std::cin >> k;
    for (int j = 0; j < k; j++) {
      Insert(arr, len);
      len++;
    }
  }
  HeapSort(arr, len);
  for (int i = 0; i < len; ++i) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  return 0;
}
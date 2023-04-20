#include <cmath>
#include <iostream>

typedef struct {
  long long prev;
  long long next;
} SmallArr;
typedef struct {
  long long num;
  int index = 0;
} Max;

void Swap(long long* arr, int index1, int index2);
void Heapify(long long* arr, int len, int i);
void HeapSort(long long* arr, int n);
void Print(long long* arr, int n, int k);
void Command(long long* arr, int n, int k);

void Swap(long long* arr, int index1, int index2) {
  long long tmp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = tmp;
}
void Heapify(long long* arr, int len, int i) {
  long long parent = i;
  long long left = 2 * i + 1;
  long long right = 2 * i + 2;
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
void Print(long long* arr, int n, int k) {
  if (k <= n) {
    for (int i = 0; i < k; i++) {
      std::cout << arr[i] << ' ';
    }
  } else {
    for (int i = 0; i < n; i++) {
      std::cout << arr[i] << ' ';
    }
  }
}
void Command(long long* arr, int n, int k) {
  long long a;
  long long x;
  long long y;
  long long mod = (long long)(pow(2, 30));
  SmallArr element;
  Max max;
  std::cin >> a >> x >> y;
  arr[0] = (x * a + y) % mod;
  max.num = arr[0];
  element.prev = arr[0];
  for (int i = 1; i < n; i++) {
    element.next = (x * element.prev + y) % mod;
    if (i < k) {
      arr[i] = element.next;
      if (arr[i] > max.num) {
        max.num = arr[i];
        max.index = i;
      }
    } else if (i >= k && element.next < max.num) {
      arr[max.index] = element.next;
      HeapSort(arr, k);
      max.num = arr[k - 1];
      max.index = k - 1;
    }
    element.prev = element.next;
  }
}
int main() {
  int n;
  int k;
  std::cin >> n >> k;
  long long* arr = new long long[std::min(n, k)];
  Command(arr, n, k);
  HeapSort(arr, k);
  Print(arr, n, k);
  delete[] arr;
  return 0;
}
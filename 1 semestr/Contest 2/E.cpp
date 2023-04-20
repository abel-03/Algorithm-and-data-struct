#include <iostream>
#include <string>

typedef struct Stack {
  long long* min = new long long[200000];
  long long* max = new long long[200000];
  int size = 0;
} Stack;

void Swap(long long* arr, int index1, int index2);
void HeapifyMin(Stack* arr, int index);
void HeapifyMax(Stack* arr, int index);
void Insert(Stack* arr);
void ExtractMin(Stack* arr);
void GetMin(Stack* arr);
void ExtractMax(Stack* arr);
void GetMax(Stack* arr);
void Size(Stack* arr);
void Clear(Stack* arr);
void SwiftUpMin(Stack* arr, int index);
void SwiftUpMax(Stack* arr, int index);

void Swap(long long* arr, int index1, int index2) {
  long long tmp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = tmp;
}
void SwiftUpMin(Stack* arr, int index) {
  int parent = (index - 1) / 2;
  if (arr->min[index] < arr->min[parent]) {
    Swap(arr->min, index, parent);
    SwiftUpMin(arr, parent);
  }
}
void SwiftUpMax(Stack* arr, int index) {
  int parent = (index - 1) / 2;
  if (arr->max[index] > arr->max[parent]) {
    Swap(arr->max, index, parent);
    SwiftUpMax(arr, parent);
  }
}
void HeapifyMax(Stack* arr, int index) {
  int parent = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  if (left < arr->size && arr->max[left] > arr->max[parent]) {
    parent = left;
  }
  if (right < arr->size && arr->max[right] > arr->max[parent]) {
    parent = right;
  }
  if (parent != index) {
    Swap(arr->max, index, parent);
    HeapifyMax(arr, parent);
  }
}
void HeapifyMin(Stack* arr, int index) {
  int parent = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  if (left < arr->size && arr->min[left] < arr->min[parent]) {
    parent = left;
  }
  if (right < arr->size && arr->min[right] < arr->min[parent]) {
    parent = right;
  }
  if (parent != index) {
    Swap(arr->min, index, parent);
    HeapifyMin(arr, parent);
  }
}
void Insert(Stack* arr) {
  long long x;
  std::cin >> x;
  arr->min[arr->size] = x;
  SwiftUpMin(arr, arr->size);
  arr->max[arr->size] = x;
  SwiftUpMax(arr, arr->size);
  arr->size++;
  std::cout << "ok" << '\n';
}
void ExtractMin(Stack* arr) {
  if (arr->size < 1) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << arr->min[0] << '\n';
  Swap(arr->min, 0, arr->size - 1);
  arr->size--;
  HeapifyMin(arr, 0);
  for (int i = arr->size / 2; i <= arr->size; i++) {
    if (arr->max[i] == arr->min[arr->size]) {
      Swap(arr->max, i, arr->size);
      SwiftUpMax(arr, i);
      HeapifyMax(arr, arr->size - i);
      return;
    }
  }
}
void GetMin(Stack* arr) {
  if (arr->size < 1) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << arr->min[0] << '\n';
}
void ExtractMax(Stack* arr) {
  if (arr->size < 1) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << arr->max[0] << '\n';
  Swap(arr->max, 0, arr->size - 1);
  arr->size--;
  HeapifyMax(arr, 0);
  for (int i = arr->size / 2; i <= arr->size; i++) {
    if (arr->min[i] == arr->max[arr->size]) {
      Swap(arr->min, i, arr->size);
      SwiftUpMin(arr, i);
      HeapifyMin(arr, arr->size - i);
      return;
    }
  }
}
void GetMax(Stack* arr) {
  if (arr->size < 1) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << arr->max[0] << '\n';
}
void Size(Stack* arr) { std::cout << arr->size << '\n'; }
void Clear(Stack* arr) {
  arr->size = 0;
  std::cout << "ok" << '\n';
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Stack arr;
  int n;
  std::cin >> n;
  std::string comand;
  for (int i = 0; i < n; i++) {
    std::cin >> comand;
    if (comand == "insert") {
      Insert(&arr);
    } else if (comand == "extract_min") {
      ExtractMin(&arr);
    } else if (comand == "extract_max") {
      ExtractMax(&arr);
    } else if (comand == "get_min") {
      GetMin(&arr);
    } else if (comand == "get_max") {
      GetMax(&arr);
    } else if (comand == "size") {
      Size(&arr);
    } else {
      Clear(&arr);
    }
  }
  delete[] arr.max;
  delete[] arr.min;
  return 0;
}
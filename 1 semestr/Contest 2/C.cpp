#include <iostream>
#include <string>
#include <vector>

typedef struct Heap {
  long long* num = new long long[1000000];
  long long* iter = new long long[1000000];
  int size = 0;
} Heap;

void Swap(Heap* heap, int index1, int index2);
void Insert(Heap* heap, int iter_num);
void HeapifyKey(Heap* heap, int index, long long key);
void Heapify(Heap* heap, int index);
void GetMin(Heap* heap);
void ExtractMin(Heap* heap);
void DeacreaseKey(Heap* heap);

void Swap(Heap* heap, int index1, int index2) {
  long long tmp = heap->iter[index1];
  heap->iter[index1] = heap->iter[index2];
  heap->iter[index2] = tmp;
  tmp = heap->num[index1];
  heap->num[index1] = heap->num[index2];
  heap->num[index2] = tmp;
}
void Insert(Heap* heap, int iter_num) {
  long long x;
  std::cin >> x;
  heap->iter[heap->size] = iter_num;
  heap->size++;
  HeapifyKey(heap, heap->size - 1, x);
}
void HeapifyKey(Heap* heap, int index, long long key) {
  heap->num[index] = key;
  while (index > 0 && heap->num[(index - 1) / 2] > heap->num[index]) {
    Swap(heap, index, (index - 1) / 2);
    index = (index - 1) / 2;
  }
}
void Heapify(Heap* heap, int index) {
  int parent = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  if (left < heap->size && heap->num[left] < heap->num[parent]) {
    parent = left;
  }
  if (right < heap->size && heap->num[right] < heap->num[parent]) {
    parent = right;
  }
  if (index != parent) {
    Swap(heap, index, parent);
    Heapify(heap, parent);
  }
}
void GetMin(Heap* heap) { std::cout << heap->num[0] << '\n'; }
void ExtractMin(Heap* heap) {
  heap->num[0] = heap->num[heap->size - 1];
  heap->iter[0] = heap->iter[heap->size - 1];
  heap->size--;
  Heapify(heap, 0);
}
void DeacreaseKey(Heap* heap) {
  int iter;
  long long delta;
  std::cin >> iter >> delta;
  for (int i = 0; i < heap->size; i++) {
    if (heap->iter[i] == iter - 1) {
      HeapifyKey(heap, i, heap->num[i] - delta);
      break;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int num;
  Heap heap;
  std::string command;
  std::cin >> num;
  for (int i = 0; i < num; i++) {
    std::cin >> command;
    if (command == "insert") {
      Insert(&heap, i);
    } else if (command == "getMin") {
      GetMin(&heap);
    } else if (command == "extractMin") {
      ExtractMin(&heap);
    } else {
      DeacreaseKey(&heap);
    }
  }
  delete[] heap.num;
  delete[] heap.iter;
  return 0;
}
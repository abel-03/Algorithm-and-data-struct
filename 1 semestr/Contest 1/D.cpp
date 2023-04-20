#include <algorithm>
#include <iostream>

struct Stack {
  int arr[200000];
  int head = -1;
  int min[200000];
};
void Push(Stack* top) {
  int new_element;
  std::cin >> new_element;
  top->head++;
  if (top->head == 0) {
    top->min[0] = new_element;
  } else {
    top->min[top->head] = std::min(top->min[top->head - 1], new_element);
  }
  top->arr[top->head] = new_element;
  std::cout << "ok" << std::endl;
}
void Pop(Stack* top) {
  if (top->head == -1) {
    std::cout << "error" << std::endl;
  } else {
    top->head--;
    std::cout << top->arr[top->head + 1] << std::endl;
  }
}
void Back(Stack* top) {
  if (top->head == -1) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << top->arr[top->head] << std::endl;
  }
}
void Min(Stack* top) {
  if (top->head == -1) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << top->min[top->head] << std::endl;
  }
}
int Size(Stack* top) { return top->head + 1; }
void Clear(Stack* top) {
  top->head = -1;
  std::cout << "ok" << std::endl;
}
int main() {
  int num_command = 0;
  Stack top;
  std::string command;
  std::cin >> num_command;
  for (int i = 0; i < num_command; i++) {
    std::cin >> command;
    if (command == "push") {
      Push(&top);
    } else if (command == "pop") {
      Pop(&top);
    } else if (command == "back") {
      Back(&top);
    } else if (command == "min") {
      Min(&top);
    } else if (command == "size") {
      std::cout << Size(&top) << std::endl;
    } else {
      Clear(&top);
    }
  }
}
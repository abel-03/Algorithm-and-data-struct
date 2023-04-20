#include <algorithm>
#include <iostream>
#include <string>

struct Stack {
  int arr[200000];
  int head = -1;
  int min[200000];
};

void Enqueue(int new_element, Stack* stack1);
void Dequeue(Stack* stack1, Stack* stack2);
void Push(Stack* top, int new_element);
int Pop(Stack* top);
void Back(Stack* stack1, Stack* stack2);
void Min(Stack* stack1, Stack* stack2);
int Size(Stack* stack1, Stack* stack2);
void Clear(Stack* top);
void Cmmnd(std::string command, Stack* stack1, Stack* stack2);

void Enqueue(int new_element, Stack* stack1) { Push(stack1, new_element); }

void Dequeue(Stack* stack1, struct Stack* stack2) {
  if (stack1->head == -1 && stack2->head == -1) {
    std::cout << "error" << std::endl;
  } else if (stack2->head == -1) {
    while (stack1->head != -1) {
      Push(stack2, Pop(stack1));
    }
    std::cout << Pop(stack2) << std::endl;
  } else {
    std::cout << Pop(stack2) << std::endl;
  }
}

void Push(Stack* top, int new_element) {
  top->head++;
  if (top->head == 0) {
    top->min[0] = new_element;
  } else {
    top->min[top->head] = std::min(top->min[top->head - 1], new_element);
  }
  top->arr[top->head] = new_element;
}

int Pop(Stack* top) {
  top->head--;
  return top->arr[top->head + 1];
}
void Back(Stack* stack1, Stack* stack2) {
  if (stack1->head == -1 && stack2->head == -1) {
    std::cout << "error" << std::endl;
  } else if (stack2->head == -1) {
    while (stack1->head != -1) {
      Push(stack2, Pop(stack1));
    }
    std::cout << stack2->arr[stack2->head] << std::endl;
  } else {
    std::cout << stack2->arr[stack2->head] << std::endl;
  }
}
void Min(Stack* stack1, Stack* stack2) {
  if (stack1->head == -1 && stack2->head == -1) {
    std::cout << "error" << std::endl;
  } else if (stack1->head == -1) {
    std::cout << stack2->min[stack2->head] << std::endl;
  } else if (stack2->head == -1) {
    std::cout << stack1->min[stack1->head] << std::endl;
  } else {
    std::cout << std::min(stack1->min[stack1->head], stack2->min[stack2->head])
              << std::endl;
  }
}
int Size(Stack* stack1, Stack* stack2) {
  return stack1->head + stack2->head + 2;
}
void Clear(Stack* top) { top->head = -1; }
void Cmmnd(std::string command, Stack* stack1, Stack* stack2) {
  if (command == "enqueue") {
    int new_element;
    std::cin >> new_element;
    Enqueue(new_element, stack1);
    std::cout << "ok" << std::endl;
  } else if (command == "dequeue") {
    Dequeue(stack1, stack2);
  } else if (command == "front") {
    Back(stack1, stack2);
  } else if (command == "min") {
    Min(stack1, stack2);
  } else if (command == "size") {
    std::cout << Size(stack1, stack2) << std::endl;
  } else {
    Clear(stack1);
    Clear(stack2);
    std::cout << "ok" << std::endl;
  }
}
int main() {
  int num_command = 0;
  Stack stack1;
  Stack stack2;
  std::string command;
  std::cin >> num_command;
  for (int i = 0; i < num_command; i++) {
    std::cin >> command;
    Cmmnd(command, &stack1, &stack2);
  }
}
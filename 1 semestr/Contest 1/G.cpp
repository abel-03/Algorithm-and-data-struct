#include <iostream>

struct Stack {
  char staples[100000];
  int head = -1;
};
void Push(Stack* top, char symbol) {
  top->head++;
  top->staples[top->head] = symbol;
}
char Pop(Stack* top) {
  if (top->head > -1) {
    top->head--;
    return top->staples[top->head + 1];
  }
  return 0;
}
bool IsEmpty(Stack* top) { return top->head == -1; }

int main() {
  Stack top;
  char* symbol = new char[1000000];
  std::cin.getline(symbol, 1000000);
  int i = 0;
  while (symbol[i] != '\0') {
    if (symbol[i] == '(' || symbol[i] == '{' || symbol[i] == '[') {
      Push(&top, symbol[i]);
    } else if (symbol[i] == ')' || symbol[i] == '}' || symbol[i] == ']') {
      if (IsEmpty(&top) || ((symbol[i] == ')' && char(Pop(&top)) != '(') ||
                            (symbol[i] == '}' && char(Pop(&top)) != '{') ||
                            (symbol[i] == ']' && char(Pop(&top)) != '['))) {
        std::cout << "NO";
        delete[] symbol;
        return 0;
      }
    }
    i++;
  }
  if (IsEmpty(&top)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  delete[] symbol;
  return 0;
}
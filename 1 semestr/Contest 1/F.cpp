#include <cctype>
#include <iostream>

void Sum(int* num, int* index_num);
void Diff(int* num, int* index_num);
void Comp(int* num, int* index_num);
void Add(int* num, const char* symbol, int index_num, int index_symbol);

void Sum(int* num, int* index_num) {
  num[*index_num - 2] += num[*index_num - 1];
  *index_num -= 2;
  num[*index_num + 1] = 0;
}

void Diff(int* num, int* index_num) {
  num[*index_num - 2] -= num[*index_num - 1];
  *index_num -= 2;
  num[*index_num + 1] = 0;
}

void Comp(int* num, int* index_num) {
  num[*index_num - 2] *= num[*index_num - 1];
  *index_num -= 2;
  num[*index_num + 1] = 0;
}
void Add(int* num, const char* symbol, int index_num, int index_symbol) {
  num[index_num] += int(symbol[index_symbol]) - int('0');
  num[index_num] *= 10;
  if (symbol[index_symbol + 1] == ' ') {
    num[index_num] /= 10;
  }
}

int main() {
  char symbol[100000];
  int num[100000] = {0};
  int index_symbol = 0;
  int index_num = 0;
  std::cin.getline(symbol, sizeof symbol);
  while (symbol[index_symbol] != '\0') {
    if (symbol[index_symbol] == ' ') {
      index_symbol++;
      index_num++;
      continue;
    }
    if (std::isdigit(symbol[index_symbol]) != 0) {
      Add(num, symbol, index_num, index_symbol);
    } else if (symbol[index_symbol] == '+') {
      Sum(num, &index_num);
    } else if (symbol[index_symbol] == '-') {
      Diff(num, &index_num);
    } else if (symbol[index_symbol] == '*') {
      Comp(num, &index_num);
    }
    index_symbol++;
  }
  std::cout << num[0];
}
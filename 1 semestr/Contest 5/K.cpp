#include <iostream>

int main() {
  const int kMod = 1e9;
  int number_pokemon;
  std::cin >> number_pokemon;

  int* arr_pokemon = new int[number_pokemon];
  int** res_arr = new int*[number_pokemon];

  for (int i = 0; i < number_pokemon; ++i) {
    std::cin >> arr_pokemon[i];
    res_arr[i] = new int[number_pokemon];
    if (i > 0) {
      res_arr[i][i - 1] = 0;
    }
    res_arr[i][i] = 1;
  }
  for (int i = number_pokemon - 2; i >= 0; --i) {
    for (int j = i + 1; j < number_pokemon; ++j) {
      res_arr[i][j] =
          (res_arr[i + 1][j] + res_arr[i][j - 1] - res_arr[i + 1][j - 1] +
           static_cast<int>(arr_pokemon[i] == arr_pokemon[j]) *
               (res_arr[i + 1][j - 1] + 1)) %
          kMod;
      res_arr[i][j] = res_arr[i][j] >= 0 ? res_arr[i][j] : kMod + res_arr[i][j];
    }
  }

  std::cout << res_arr[0][number_pokemon - 1];
  delete[] arr_pokemon;
  for (int i = 0; i < number_pokemon; ++i) {
    delete[] res_arr[i];
  }
  delete[] res_arr;
}
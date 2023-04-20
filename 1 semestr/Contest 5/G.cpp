#include <algorithm>
#include <iostream>
#include <utility>

struct Comparison {
  bool operator()(const std::pair<int, int>& elem1,
                  const std::pair<int, int>& elem2) {
    return elem1.first == elem2.first ? elem1.second > elem2.second
                                      : elem1.first < elem2.first;
  }
};

void Completion(int* max, int idx, int end, int val) {
  for (int i = idx; i < end; ++i) {
    if (val <= max[i]) {
      break;
    }
    max[i] = val;
  }
}

int main() {
  int number_pokemon = 0;

  std::cin >> number_pokemon;
  std::pair<int, int>* pokemons_power = new std::pair<int, int>[number_pokemon];
  int* pokemons_power_len = new int[number_pokemon];
  int* max = new int[number_pokemon];
  int res = 0;

  for (int i = 0; i < number_pokemon; ++i) {
    max[i] = 0;
    std::cin >> pokemons_power[i].first;
    pokemons_power[i].second = i;
  }
  Comparison pair_cmp;
  std::sort(pokemons_power, pokemons_power + number_pokemon, pair_cmp);

  for (int i = 0; i < number_pokemon; ++i) {
    pokemons_power_len[pokemons_power[i].second] =
        1 + max[pokemons_power[i].second];
    Completion(max, pokemons_power[i].second, number_pokemon,
               1 + max[pokemons_power[i].second]);
    res = std::max(res, pokemons_power_len[pokemons_power[i].second]);
  }
  std::cout << res;

  delete[] max;
  delete[] pokemons_power;
  delete[] pokemons_power_len;
}
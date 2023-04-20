#include <algorithm>
#include <iostream>

int main() {
  int num_condidat;
  int num_request;
  int speed[100000] = {0};
  int min_speed[100000] = {0};
  int min_speed_end[100000] = {0};
  int left_end;
  int right_end;
  std::cin >> num_condidat;
  for (int i = 0; i < num_condidat; i++) {
    std::cin >> speed[i];
  }
  min_speed[0] = speed[0];
  min_speed_end[0] = speed[num_condidat - 1];
  for (int i = 1; i < num_condidat; i++) {
    min_speed[i] = std::min(min_speed[i - 1], speed[i]);
    min_speed_end[i] =
        std::min(min_speed_end[i - 1], speed[num_condidat - i - 1]);
  }
  std::cin >> num_request;
  for (int i = 0; i < num_request; i++) {
    std::cin >> left_end >> right_end;
    std::cout << std::min(min_speed[left_end - 1],
                          min_speed_end[num_condidat - right_end])
              << std::endl;
  }
}
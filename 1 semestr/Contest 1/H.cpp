#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int num_mandragor;
  long double volume[300000] = {0};
  long double mult_volume[300000] = {0};
  int request;
  int r_index;
  int l_index;
  long double extent;
  std::cin >> num_mandragor >> volume[0];
  mult_volume[0] = pow(volume[0], double(1) / double(10000));
  for (int i = 1; i < num_mandragor; i++) {
    std::cin >> volume[i];
    mult_volume[i] =
        mult_volume[i - 1] * pow(volume[i], double(1) / double(10000));
  }
  std::cin >> request;
  for (int i = 0; i < request; i++) {
    std::cin >> l_index >> r_index;
    extent = double(1) / double(r_index - l_index + 1);
    if (l_index > 0) {
      std::cout << std::fixed << std::setprecision(10)
                << pow(pow(mult_volume[r_index] / mult_volume[l_index - 1],
                           extent),
                       10000)
                << std::endl;
    } else {
      std::cout << std::fixed << std::setprecision(10)
                << pow(pow(mult_volume[r_index], extent), 10000) << std::endl;
    }
  }
}
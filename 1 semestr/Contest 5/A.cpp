#include <cmath>
#include <iostream>

struct Point {
  int x;
  int y;
};

struct Vector {
  int x;
  int y;
};

double Corner(Vector vector_1, Vector vector_2) {
  double scalar_product = vector_1.x * vector_2.x + vector_1.y * vector_2.y;
  double modul_vector1 =
      sqrt(vector_1.y * vector_1.y + vector_1.x * vector_1.x);
  double modul_vector2 =
      sqrt(vector_2.y * vector_2.y + vector_2.x * vector_2.x);
  double arccos = acos(scalar_product / (modul_vector1 * modul_vector2));
  return arccos;
}

bool VectorProductIsPositive(Vector vector_1, Vector vector_2) {
  return (vector_1.x * vector_2.y - vector_1.y * vector_2.x) > 0;
}

int main() {
  int number_point;
  Point point;
  double sum = 0;
  std::cin >> number_point;
  std::cin >> point.x >> point.y;

  Point* arr_points = new Point[number_point];

  for (int i = 0; i < number_point; ++i) {
    std::cin >> arr_points[i].x >> arr_points[i].y;
  }

  for (int i = 0; i < number_point; ++i) {
    Vector vector_1 = {arr_points[i].x - point.x, arr_points[i].y - point.y};
    Vector vector_2 = {arr_points[(i + 1) % number_point].x - point.x,
                       arr_points[(i + 1) % number_point].y - point.y};
    VectorProductIsPositive(vector_1, vector_2)
        ? sum += Corner(vector_1, vector_2)
        : sum -= Corner(vector_1, vector_2);
  }
  round(sum / 2) == 0 ? std::cout << "NO" : std::cout << "YES";

  delete[] arr_points;
}
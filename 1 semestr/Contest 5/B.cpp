#include <iostream>

struct Point {
  int64_t x;
  int64_t y;
};

int64_t ProductVectors(Point a, Point b) { return a.x * b.y - a.y * b.x; }

int64_t IsConvex(Point* point_arr, int number_point) {
  bool first_direct = false;
  int64_t product1;
  for (int i = 0; i < number_point; ++i) {
    Point a = {
        point_arr[(i + 1) % number_point].x - point_arr[i % number_point].x,
        point_arr[(i + 1) % number_point].y - point_arr[i % number_point].y};
    Point b = {point_arr[(i + 2) % number_point].x -
                   point_arr[(i + 1) % number_point].x,
               point_arr[(i + 2) % number_point].y -
                   point_arr[(i + 1) % number_point].y};
    product1 = ProductVectors(a, b);
    if (product1 != 0) {
      first_direct = product1 > 0 ? false : true;
      break;
    }
  }
  for (int i = 0; i < number_point; ++i) {
    Point a = {
        point_arr[(i + 1) % number_point].x - point_arr[i % number_point].x,
        point_arr[(i + 1) % number_point].y - point_arr[i % number_point].y};
    Point b = {point_arr[(i + 2) % number_point].x -
                   point_arr[(i + 1) % number_point].x,
               point_arr[(i + 2) % number_point].y -
                   point_arr[(i + 1) % number_point].y};
    Point c = {point_arr[(i + 3) % number_point].x -
                   point_arr[(i + 2) % number_point].x,
               point_arr[(i + 3) % number_point].y -
                   point_arr[(i + 2) % number_point].y};
    product1 = ProductVectors(a, b);
    int64_t product2 = ProductVectors(b, c);
    bool next_direct = product2 == 0 ? first_direct : product2 > 0 ? false : true;
    if ((product1 > 0 && product2 < 0) || (product1 < 0 && product2 > 0) ||
        (first_direct != next_direct)) {
      return false;
    }
  }
  return true;
}

int main() {
  int number_point;


  std::cin >> number_point;
  Point* point_arr = new Point[number_point];

  for (int i = 0; i < number_point; ++i) {
    std::cin >> point_arr[i].x >> point_arr[i].y;
  }
  IsConvex(point_arr, number_point) ? std::cout << "YES" : std::cout << "NO";
  delete[] point_arr;
} 
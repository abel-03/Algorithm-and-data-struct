#include <iostream>
#include <vector>

int main() {
  int arr_len;

  std::cin >> arr_len;

  int* arr_elem = new int[arr_len];
  int** res_matrix = new int*[arr_len];
  for (int i = 0; i < arr_len; ++i) {
    std::cin >> arr_elem[i];
    res_matrix[i] = new int[2];
    res_matrix[i][0] = 1;
    res_matrix[i][1] = 1;
  }
  
  for (int i = 1; i < arr_len; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr_elem[j] < arr_elem[i] && res_matrix[i][0] < res_matrix[j][1] + 1) {
        res_matrix[i][0] = res_matrix[j][1] + 1;
      }
      if (arr_elem[j] > arr_elem[i] && res_matrix[i][1] < res_matrix[j][0] + 1) {
        res_matrix[i][1] = res_matrix[j][0] + 1;
      }
    }
  }

  int res = (res_matrix[arr_len - 1][0] > res_matrix[arr_len - 1][1]) ? res_matrix[arr_len-1][0] : res_matrix[arr_len-1][1];
  std::cout << res << '\n';
  int* result = new int[res];
  for(int i = res; i > 0; --i) {
    for(int j = arr_len - 1; j >= 0; --j) {
      if((res_matrix[j][0] == i || res_matrix[j][1] == i) && res_matrix[j][0] < i + 1 && res_matrix[j][1] < i + 1 ) {
        result[i - 1] = arr_elem[j];
        break;
      } 
    }
  }
  for(int i = 0; i < res; ++i) {
    std::cout << result[i] << ' ';
  }

  delete[] arr_elem;
  delete[] result;
  for(int i = 0; i < arr_len; ++i) {
    delete[] res_matrix[i];
  }
  delete[] res_matrix;


  return 0;
}
#include <iostream>
#include <vector>

void FindLCS(const int* arr1,const int* arr2, int** res, int len_arr1, int len_arr2) {
    std::vector<int> res_sequence;
    while (len_arr1 >= 0 && len_arr2 >= 0) {
        if (arr1[len_arr1] == arr2[len_arr2]) {
            res_sequence.push_back(arr1[len_arr1]);
            --len_arr1;
            --len_arr2;
        } else if (len_arr1 > 0 && len_arr2 > 0) {
            res[len_arr1 + 1][len_arr2] > res[len_arr1][len_arr2 + 1]
                ? --len_arr2
                : --len_arr1;
        } else {
            if (arr1[len_arr1] == arr2[len_arr2]) {
                res_sequence.push_back(arr1[len_arr1]);
                break;
            }
            if (len_arr1 > 0) {
                --len_arr1;
            } else if (len_arr2 > 0) {
                --len_arr2;
            } else {
                break;
            }
        }
    }
    for (int i = res_sequence.size() - 1; i >= 0; --i) {
        std::cout << res_sequence[i] << ' ';
    }
}

int main() {
    int len_arr1 = 0;
    int len_arr2 = 0;
    std::cin >> len_arr1;
    int* arr1 = new int[len_arr1];
    int** res = new int*[len_arr1 + 1];
    for (int i = 0; i < len_arr1; ++i) {
        std::cin >> arr1[i];
    }
    std::cin >> len_arr2;
    int* arr2 = new int[len_arr2];
    for (int i = 0; i <= len_arr1; ++i) {
        res[i] = new int[len_arr2 + 1];
    }
    for (int i = 0; i < len_arr2; ++i) {
        std::cin >> arr2[i];
    }
    for (int i = 1; i <= len_arr1; ++i) {
        res[i][0] = 0;
        for (int j = 1; j <= len_arr2; ++j) {
            res[0][j] = 0;
            res[i][j] = std::max(res[i - 1][j], res[i][j - 1]);
            if (arr1[i - 1] == arr2[j - 1]) {
                res[i][j] = std::max(res[i][j], res[i - 1][j - 1] + 1);
            }
        }
    }
    FindLCS(arr1, arr2, res, len_arr1 - 1, len_arr2 - 1);
    delete[] arr1;
    delete[] arr2;
    for (int i = 0; i < len_arr1 + 1; ++i) {
        delete[] res[i];
    }
    delete[] res;
}
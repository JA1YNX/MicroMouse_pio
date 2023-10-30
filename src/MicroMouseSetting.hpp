#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> wall_setting() {
    return {{11, 2, 6, 7, 7, 7, 3, 10, 10, 10, 6, 3, 10, 2, 10, 6},
            {3, 12, 1, 0, 0, 0, 4, 11, 2, 10, 12, 5, 3, 8, 6, 5},
            {9, 6, 5, 13, 13, 13, 9, 6, 9, 2, 10, 12, 5, 3, 12, 5},
            {3, 12, 9, 10, 10, 10, 6, 9, 6, 13, 3, 6, 5, 9, 6, 5},
            {9, 6, 3, 10, 10, 10, 8, 14, 9, 10, 12, 9, 12, 3, 12, 5},
            {3, 8, 4, 11, 2, 10, 10, 10, 10, 10, 10, 10, 10, 8, 6, 5},
            {5, 7, 1, 6, 5, 3, 2, 2, 14, 11, 2, 10, 2, 14, 5, 5},
            {5, 1, 12, 5, 5, 5, 5, 1, 6, 3, 12, 3, 8, 6, 5, 5},
            {5, 5, 3, 12, 5, 5, 5, 9, 12, 9, 6, 9, 2, 12, 5, 5},
            {5, 5, 9, 6, 5, 5, 5, 11, 2, 6, 5, 3, 8, 6, 5, 5},
            {5, 5, 3, 8, 4, 5, 1, 6, 5, 1, 12, 9, 2, 12, 5, 5},
            {1, 0, 8, 2, 12, 1, 12, 9, 4, 5, 3, 6, 9, 6, 5, 5},
            {5, 5, 3, 12, 11, 8, 10, 10, 8, 4, 5, 9, 6, 9, 4, 5},
            {9, 8, 12, 3, 6, 3, 10, 10, 10, 12, 9, 6, 9, 6, 5, 5},
            {3, 10, 10, 12, 9, 8, 10, 10, 10, 10, 10, 8, 14, 9, 4, 5},
            {9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 12}};
}

int wall_code(int x, int y) {
    vector<vector<int>> w = wall_setting();
    return w[x][y];
}

vector<int> wall_x(int y) {
    vector<int> wall(16, 0);
    vector<vector<int>> w = wall_setting();
    for (int i = 0; i < 16; i++) {
        wall[i] = w[i][y] % 2;
    }
    return wall;
}

vector<int> wall_y(int x) {
    vector<int> wall(16, 0);
    vector<vector<int>> w = wall_setting();
    for (int i = 0; i < 16; i++) {
        wall[i] = (w[x][i] >> 1) % 2;
    }
    return wall;
}
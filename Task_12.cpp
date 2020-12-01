#include <iostream>
using namespace std;



// 回溯法：矩阵中的路径
int main(){

    return 0;
}

class Solution {
    vector<vector<bool>> flag;
    int direct[4][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}};    // 左、右、上、下
public:
    bool dfs(char * matrix, int i, int j, char * str, int pathLength){
        if(str[pathLength] == '\0') return true;
        int m = flag.size(), n = flag[0].size();
        if(str[pathLength] != matrix[i*n+j]) return false;
        flag[i][j] = true;
        for(int k = 0; k < 4; ++k){
            int row = direct[k][0] + i;
            int col = direct[k][1] + j;
            if(row >= m || col >= n|| row < 0 || col < 0|| flag[row][col]) continue;
            if(dfs(matrix, row, col, str, pathLength+1)) return true;
        }
        flag[i][j] = false;
        return false;
    }
    // matrix矩阵
    bool hasPath(char* matrix, int rows, int cols, char* str){
        if(matrix == NULL || rows < 1 || cols < 1 || str == NULL) return false;
        flag = vector<vector<bool>>(rows, vector<bool>(cols, false));
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                if(matrix[i*cols+j] == str[0]){
                    if(dfs(matrix, i, j, str, 0)) return true;
                }
                    return true;
            }
        }
        return false;
    }
};
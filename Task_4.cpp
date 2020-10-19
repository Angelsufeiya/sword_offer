#include <iostream>
#include <vector>
using namespace std;

bool Find(vector<vector<int> > vv, int n){
    int i = 0, j = vv[0].size()-1;
    while(i < vv.size() && j >= 0){
        if(vv[i][j] == n) return true;
        else if(vv[i][j] > n) --j;
        else if(vv[i][j] < n) ++i;
    }
    return false;
}

int main(){
    int arr[4][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    vector<vector<int> > vv(4, vector<int>(4));
    for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j) vv[i][j] = arr[i][j];
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(j == 0) cout << vv[i][j];
            else cout << ' ' << vv[i][j];
        }
        cout << endl;
    }
    cout << "这个二维数组中是否有：" ;
    
    int num;
    cin >> num;
    if(Find(vv, num)) cout << "数组中存在" << num << endl;
    else cout << "数组中不存在" << num << endl;

    return 0;
}
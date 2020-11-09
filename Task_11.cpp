#include <iostream>
#include <vector>
using namespace std;

int MinInOrder(vector<int> v, int i, int j){
    int res = v[i];
    for(int n = i+1; n <= j; n++){
        if(res > v[n]) res = v[n];
    }
    return res;
}

int Min(vector<int> v, int len){
    if(len <= 0) {
        cout << "Invaild parameters" << endl;
        return -1;
    }

    int i = 0, j = len-1, mid = 0;
    while(v[i] >= v[j]){
        if(j-i == 1){
            mid = j;
            break;
        }
        mid = i + (j - i)/2;
        if(v[i] == v[mid] && v[mid] == v[j]) return MinInOrder(v, i, j);

        if(v[i] <= v[mid]) i = mid;
        else if(v[j] >= v[mid]) j = mid;
    }
    return v[mid];
}

int main(){
    int arr[] = { 1, 1, 1, 0, 1};
    vector<int> v(arr, arr+5);
    int sz = v.size();
    cout << Min(v, sz) << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#if 0
// 快排
void quicksort(vector<int>& v, int left, int right){
    int i = left, j = right, temp = v[left];
    if(left > right) return;
    while(i!=j){
        while(v[j] >= temp && i < j) j--;
        while(v[i] <= temp && i < j) i++;
        if(i < j) swap(v[i],v[j]);
    }
    v[left] = v[i], v[i] = temp;
    quicksort(v, left, i-1);
    quicksort(v, i+1, right);
}

// 方法1
int repeatNum_1(vector<int> v){
    if(v.empty()) return -1;
    int len = v.size();
    //quicksort(v, 0, len-1);
    sort(v.begin(), v.end());
    for(int i = 1; i < len; i++){
        if(v[i] == v[i-1]){
            return v[i];
        }
    }
    return -1;
}

int repeatNum_2(vector<int>& v){
    if(v.empty()) return -1;
    map<int, int> m;
    for(int i = 0; i < v.size(); i++){
        if(m[v[i]]) return v[i];
        else m[v[i]]++;
    }
    return -1;
}

int repeatNum(vector<int>& v){
    int len = v.size();
    vector<int> v1(len);
    for(int i = 0; i < len; ++i){
        if(v1[v[i]]) return v1[v[i]];
        else v1[v[i]] = v[i];
    }
    return -1;
}

int duplicate(vector<int>& v){
    if(v.empty()) return -1;
    for(int i = 0; i < v.size(); ++i){
        if(v[i] < 0 || v[i] > v.size()-1) 
            return -1;
    }
    
    for(int i = 0; i < v.size(); ++i){
        while(v[i] != i){
            if(v[i] == v[v[i]]) return v[i];
            swap(v[i], v[v[i]]);
        }
    }
    return false;
}

bool duplicate(vector<int>& v, int **res){
    if(v.empty()) return false;
    for(int i = 0; i < v.size(); ++i){
        if(v[i] < 0 || v[i] > v.size()-1) 
            return false;
    }
    
    for(int i = 0; i < v.size(); ++i){
        while(v[i] != i){
            if(v[i] == v[v[i]]) {
                *res = &v[i];
                return true;
            }
            swap(v[i], v[v[i]]);
        }
    }
    return false;
}
#endif

int countRange(vector<int>& v, int sz, int start, int end){
    if(v.empty()) return 0;

    int count = 0;
    for(int i = 0; i < sz; ++i){
        if(v[i] >= start && v[i] <= end){
            ++count;
        }
    }
    return count;
}

int getrepeat(vector<int>& v){
    if(v.empty()) return -1;
    int sz = v.size();
    int start = 1, end = sz-1;
    while(end >= start){
        int mid = start + ((end-start)>>1);
        int count = countRange(v, sz, start, mid);
        if(end == start){
            if(count > 1) return start;
            else break;
        }
        if(count > (mid - start + 1)) end = mid;
        else start = mid + 1;
    }
    return -1;
}

int main(){
    int arr[] = {2, 3, 5, 4, 3, 2, 6, 7};
    vector<int> v(arr, arr+8);  // 这种赋值方式不会导致vector自动扩展内部大小
    cout << getrepeat(v) << endl;
    /*
    int* res = nullptr;
    if(duplicate(v, &res)) cout << *res << endl;
    else cout << '0' << endl;
    //cout << repeatNum(v) << endl;
    
    for(int i = 0; i < v.size(); i++){
        if(i == 0) cout << v[i];
        else cout << ' ' << v[i];
    }
    cout << endl;
    
    for(auto a : v){    // 有两个警告（auto是C++_11的扩展）
        cout << a << ' ';
    }
    */
    return 0;
}
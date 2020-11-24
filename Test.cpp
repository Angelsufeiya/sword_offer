#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int>& v, int l, int r){
    if(l > r) return;
    int i = l, j = r, tmp = v[l];
    while(i < j){
        while(v[j] >= tmp && i < j) j--;
        while(v[i] <= tmp && i < j) i++;
        if(i < j) swap(v[i], v[j]);
    }
    v[l] = v[i];
    v[i] = tmp;
    quickSort(v, l, i-1);
    quickSort(v, i+1, r);
}

int QuickSort(vector<int>& v, int left, int right, int k){
    if(left > right) return -1;
    int i = left, j = right, tmp = v[left];
    while(i < j){
        while(v[j] >= tmp && i < j) j--;
        while(v[i] <= tmp && i < j) i++;
        if(i < j) swap(v[i], v[j]);
    }
    v[left] = v[i];
    v[i] = tmp;

    if(i == k-1) return v[i];
    else if(i < k-1) return QuickSort(v, i+1, right, k);
    else return QuickSort(v, left, i-1, k);
}

int main(){
    int arr[] = { 6, 1, 2, 7, 9, 3, 4, 5, 10, 8 };
    vector<int> v(arr, arr+10);
    //quickSort(v, 0, 9);
    for(int i = 0; i < v.size(); ++i){
        cout << v[i] << ' ';
    }

    int k = 8;
    cout << endl <<  "查找第K个大小的数字：";
    cout << QuickSort(v, 0, 9, k) << endl;
    return 0;
}

#if 0
int main(){
    double d = 12.34;
    cout << d << endl;
    const int& a = d;
    cout << a << endl;
    const double &dr = d + 1;
    cout << dr << endl;
    return 0;
}
#endif
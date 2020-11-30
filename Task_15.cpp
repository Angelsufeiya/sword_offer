#include <iostream>
using namespace std;

// 面试15：二进制中1的个数
int Number(int n){
    int count = 0;
    unsigned int flag = 1;
    while(flag){
        if(flag & n) count++;
        flag <<= 1;
    }
    return count;
}

int Number_2(int n){
    int count = 0;
    while(n){
        n &= (n-1);
        ++count;
    }
    return count;
}

int main(){
    int num, count = 0;
    cin >> num;
    cout << Number(num) << endl;
}
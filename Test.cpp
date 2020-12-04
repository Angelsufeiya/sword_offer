#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    for(int i = 0; i < 10; ++i) v.push_back(i);
    v.resize(6);
    for(auto i : v) cout << i << ' ';
    cout << v.capacity() << endl;
    return 0;
}

#if 0
#include <iostream>
#include <vector>
using namespace std;
// Fib 数列
int main(){
    int N;
    cin >> N;
    if(N == 0 || N == 1) cout << 0 << endl;
    else{
        vector<int> v{0,1};
        int i = 1;
        do{
            v.push_back(v[i-1]+v[i]);
            i++;
        }while(v[i] < N);
        cout << min(v[i]-N, N-v[i-1]) << endl;
    }
    return 0;
}
#endif

#if 0
// 最小公倍数
#include<iostream>
using namespace std;

int gcd(int a, int b){
    while(a != b){
        if(a > b) a = a - b;
        else b = b - a;
    }
    return b;
}

int gcd(int a, int b)
{
	int res;
	while (res = a % b) {
		a = b;
		b = res;
	}
	return b;
}

int main()
{
	int a, b;
	while (cin >> a >> b) {
		cout << a * b / gcd(a, b) << endl;
	}
	return 0;
}
#endif

#if 0
// 特殊的数，只能是1，2，3，7乘积的倍数
#include <iostream>
#include <vector>
using namespace std;

bool fun(int n){
    while(n % 7 == 0){
        n /= 7;
    }
    while(n % 3 == 0){
        n /= 3;
    }
    while(n % 2 == 0){
        n /= 2;
    }
    if(n == 1) return true;
    return false;
}

int main(){
    int n = 9;
    while(n && n){
        int count = 0;
        for(int i = 1; i <2*n; ++i){
            if(fun(i)) ++count;
            if(count == n) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}
#endif
#if 0
char fun (char x, char y){
    if(x < y) return x;
    return y;
}
int main(){
    int a = '1', b = '1', c = '2';
    cout << fun (fun(a,b), fun(b,c));
    return 0;
}
#endif

#if 0
// 单例模式：懒汉模式
class Singleton
{
private:
	Singleton(){}
	static Singleton* instance;
public:
	static Singleton* GetSingleton()
	{
		return instance;
	}
};
Singleton* Singleton::instance = new Singleton();
#endif
#if 0
// 连续最大和
int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) cin >> v[i];
    int res = v[0], tmp = v[0];
    for(int i = 1; i < n; ++i){
        if(tmp >= 0) tmp += v[i];
        else{
            tmp = v[i];
        }
        if(tmp > res) res = tmp;
    }
    cout << res << endl;
    return 0;
}
#endif
#if 0
bool IsCircleText(string s){
    for(int i = 0, j = s.size()-1; i <= j; i++, j--){
        if (s[i] != s[j]) return false;
    }
    return true;
}

// 统计回文
int main(){
    string s1, s2;
    cin >> s1 >> s2;
    int count = 0;

    for(int i = 0; i <= s1.size(); ++i){
        string s = s1;
        s.insert(i, s2);
        if(IsCircleText(s)) count++;
    }
    cout << count << endl;

    return 0;
}
#endif
#if 0
// 字符串中找出连续最长的数字串
int main(){
    string s, res; 
    cin >> s;
    
    for(int i = 0; i < s.size(); i++){
        string st;
        while(s[i] >= '0' && s[i] <= '9') {
            st += s[i];
            i++;
        }
        if (st.size() > res.size()) {
            res = st;
        }
    }
    cout << res << endl;
    return 0;
}
#endif
#if 0
// 求数组中出现超过一半的数字
int MoreThanHalfNum_Solution(vector<int> numbers) {
    sort(numbers.begin(),numbers.end());
    int num = numbers[numbers.size()/2];

    if (numbers.size() / 2 < count(numbers.begin(), numbers.end(), num)) return num;
    return 0;
}

int main(){
    int arr[] = {1,2,3,2,2,2,5,4,2};
    vector<int> v(arr, arr+9);
    cout << MoreThanHalfNum_Solution(v) << endl;
    return 0;
}
#endif
#if 0
// 倒置字符串
int main(){
    string s;
    getline(cin, s);

    reverse(s.begin(), s.end());
    auto start = s.begin();
    while(start != s.end()){
        auto end = start;
        while (*end != ' ' && end != s.end()) end++;
        reverse(start, end);

        if(end != s.end()) start = end+1;
        else start = end;
    }
    cout << s << endl;

    return 0;
}
#endif
#if 0
// 倒置字符串
int main(){
    string s1, res;
    cin >> res;
    while(cin >> s1){
        res = s1 + ' ' + res;
    }
    cout << res << endl;

    return 0;
}
#endif
#if 0
// 排列子序列
int main(){
    int n;
    cin >> n;

    vector<int> v(n+1);
    for(int i = 0; i < n; ++i) cin >> v[i];

    int count;
    for(int i = 0; i < n; i++){
        if(v[i] < v[i+1]){
            i++;
            while(i < n && v[i] <= v[i+1]) i++;
            count++;
        }
        else if (v[i] == v[i+1]) i++;
        else {
            i++;
            while(i < n && v[i] >= v[i+1]) i++;
            count++;
        }
    }
    cout << count << endl;
    return 0;
}
#endif

#if 0
// 删除公共字符串
int main(){
    string s1, s2;

    getline(cin, s1);
    getline(cin, s2);

    int HashTable[256] = {0};
    for(auto i : s2) HashTable[i]++;

    string res;
    for(auto i : s1) {
        if(!HashTable[i]) res += i;
    }
    cout << res << endl;

    return 0;
}
#endif
#if 0
int main(){
    int year = 1009;
    int *p = &year;
    cout << *p++ << endl;
    return 0;
}
#endif
#if 0
bool binary_search(vector<int> v, int k, int left, int right){
    while(left <= right){
        int mid = left + (right-left)/2;
        if(v[mid] > k) right = mid-1;
        else if(v[mid] < k) left = mid+1;
        else return true;
    }
    return false;
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v(arr, arr+10);
    cout << binary_search(v, 1, 0, 9) << endl;
    return 0;
}
#endif
#if 0
//小顶堆结点调整
void adjustMinHeap(vector<int>& nums,int root,int len) {
    int l_ch=2*root+1;  //左子结点
    int r_ch=l_ch+1;   //右子结点
    int index=root;  //较大结点
 
    if(r_ch < len && nums[r_ch] < nums[index]) index=r_ch; 
    if(l_ch < len && nums[l_ch] < nums[index]) index=l_ch;
 
    if(index != root) //当前结点非最小结点
    {
        swap(nums[index],nums[root]);
        adjustMinHeap(nums,index,len);
    }
    return;
}
 
vector<int> TopKInHeap(vector<int>& nums,int k,int len){
    vector<int>res(nums.begin(),nums.begin()+k); //取出前k个数
 
    for(int i=k/2-1;i>=0;i--)  //根据前K个数建立一个小顶堆
    {
        adjustMinHeap(res,i,k);
    }
 
    //将剩下的数与堆顶做比较
    for(int i=k;i<len;i++){
        if(nums[i]>res[0])  //当前数比堆顶数大
        {
            res[0]=nums[i]; //将堆顶更新为该数
            adjustMinHeap(res,0,k); //重新调整堆
        }
    }
    return res;
}

int main(){
    int arr[] = { 6, 1, 2, 7, 9, 3, 4, 5, 10, 8 };
    vector<int> v(arr, arr+10);

    int k = 5;
    cout << endl <<  "查找前K个大小的数字：";
    vector<int> res = TopKInHeap(v, k, 10);
    for(int i = 0; i < k; ++i) {
        if(i == 0) cout << res[i];
        else cout << ' ' << res[i];
    }
    return 0;
}
#endif
#if 0

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

    if(i == k-1) return i;
    else if(i < k-1) return QuickSort(v, i+1, right, k);
    else return QuickSort(v, left, i-1, k);
}

int main(){
    int arr[] = { 6, -1, 12, 71, 29, 33, 41, 25, 110, 8 };
    vector<int> v(arr, arr+10);
    //quickSort(v, 0, 9);
    //for(int i = 0; i < v.size(); ++i)cout << v[i] << ' ';

    int k = 3;
    cout <<  "查找前K个大小的数字：";
    for(int i = QuickSort(v, 0, 9, 10-k+1); i < v.size(); ++i) cout << v[i] << ' ';
    return 0;
}
#endif
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
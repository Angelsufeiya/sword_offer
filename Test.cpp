#include <iostream>
#include <vector>
#include <string>
using namespace std;

#if 0
class Person
{
protected:
    string _name; // 姓名 
    string _sex; // 性别 
    int _age; // 年龄
};

class Student : public Person
{
public:
    int _No; // 学号 
};

int main() {
    Student sobj;

    // 1.子类对象可以赋值给父类对象/指针/引用 
    Person pobj = sobj;
    Person* pp = &sobj;
    Person& rp = sobj;

    // 2.基类对象不能赋值给派生类对象 
    //sobj = pobj;

    // 3.基类的指针可以通过强制类型转换赋值给派生类的指针
    Student* ps2 = (Student*)pp; // 这种情况转换时虽然可以，但是会存在越界访问的问题
    ps2->_No = 10;

    return 0;
}
#endif

#if 0
class A
{
public:
    void fun() {
        cout << "func()" << endl;
    }
};

class B : public A
{
public:
    void fun(int i)
    {
        A::fun();   // func()
        cout << "func(int i)->" << i << endl;   // func(int i)->10
    }
};

int main() {
    B b;
    b.fun(10);

    return 0;
}
#endif

#if 0
class Person
{
protected:
    string _name = "小李子"; // 姓名
    int _num = 111; // 身份证号 
};

class Student : public Person
{
public:
    void Print()
    {
        cout << " 姓名:" << _name << endl;
        cout << " 身份证号:" << Person::_num << endl;
        cout << " 学号:" << _num << endl;
    }
protected:
    int _num = 999; // 学号 
};

int main() {
    Student s1;
    s1.Print();

    return 0;
}
#endif

#if 0
int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    vector<int> v(arr, arr+5);
    auto it = v.begin();
    v.reserve(100);
    while(it != v.end()){
        cout << *it << ' ';
        ++it;
    }
    return 0;
}
#endif
#if 0
int main() {
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));

	// 实现删除v中的所有偶数
	// 下面的程序会崩溃掉，如果是偶数，erase导致it失效 
	// 对失效的迭代器进行++it，会导致程序崩溃 
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
			v.erase(it);
		++it;
	}

	// 以上程序要改成下面这样，erase会返回删除位置的下一个位置 
	/*vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
			it = v.erase(it);
		else
			++it;
	}*/
	return 0;
}
#endif
#if 0
int main() {
    vector<int> v;
    cout << v.size() << " " << v.capacity()<< endl; // 空vector

    for (int i = 0;i < 10; i++) v.push_back(i);
    cout << "first addr: " << &(*v.begin()) << endl;
    cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;    // size = 10 capacity = 16
    cout << "--------------------" << endl;

    // 第一种情况：insert一个元素（在容量足够的情况下并不会重新分配内存）【该失效仅仅是无法使用该迭代器遍历或所指向的元素改变了】
    vector<int>::iterator it_begin = v.begin(); // 插入前定义一个迭代器，指向第一个元素
    vector<int>::iterator it_end = v.end()-1;   // 插入前定义一个迭代器，指向最后一个元素
    v.insert(v.begin()+1, 1);   // 在第二个元素位置插入1
    cout << "插入一个元素后:" << endl;
    cout << "first addr: " << &(*v.begin()) << endl;    // 首元素地址未变
    cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;    // size = 11 capacity = 16
    cout << *it_begin << endl;  // 未失效，仍然打印出第一个元素0
    cout << *it_end << endl;    // 失效，打印出了9的前一个元素8（并未出现错误，但这仍是迭代器失效）
    cout << "--------------------" << endl;

    // 此时size=11 capacity=16，紧接着再插入五个元素
    cout << "再插入五个元素：" << endl;
    v.push_back(10);
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    v.push_back(14);
    cout << "first addr: " << &(*v.begin()) << endl;    // 首元素地址未变
    cout << "size = " << v.size() << " capacity = " << v.capacity() << endl;    // size = 16 capacity = 16
    cout << "vector 满了" << endl;
    cout << "--------------------" << endl;

    // 接下来再insert或push_back一个元素均会出现内存的重新分配。均会造成先前定义的迭代器失效【该失效会出错，访问野指针的内存】
    // 第二种情况：push_back一个即将重新分配内存的vector[insert()也会出现同样的问题]
    vector<int>::iterator iter = v.begin(); // 内存重新分配前定义一个迭代器
    v.push_back(12);
    cout << "再插入一个元素内存重新分配:" << endl;
    cout << "first addr: " << &(*v.begin()) << endl;    // 内存重新分配，首元素地址改变了，容量也多一倍
    cout << "size = " << v.size() << " capacity = "<< v.capacity() <<  endl;    // size = 17 capacity = 32
    cout << *iter << endl;  // 当重新分配内存后再调用重新分配内存前定义的迭代器，便会发生debug assertion failed错误
    cout << "--------------------" << endl;

    for (vector<int>::iterator it = v.begin();it != v.end(); ++it)
        cout << *it << " ";
    return 0;
}
#endif

#if 0
// insert/erase导致的迭代器失效 
int main() {
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));

	// 使用find查找3所在位置的iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);

	// 删除pos位置的数据，导致pos迭代器失效。 
	v.erase(pos);
	cout << *pos << endl; // 此处会导致非法访问

	// 在pos位置插入数据，导致pos迭代器失效。
	// insert会导致迭代器失效，是因为insert可能会导致增容，
	// 增容后pos还指向原来的空间，而原来的空间已经释放了。 
	pos = find(v.begin(), v.end(), 3);
	v.insert(pos, 30);
	cout << *pos << endl; // 此处会导致非法访问
	
	return 0;
}
#endif
#if 0
template<class T1, class T2>
class Data
{
public:
    Data() {cout<<"Data<T1, T2>" <<endl;}
private:
	T1 _d1;
	T2 _d2; 
};

// 将第二个参数特化为int 
template <class T1> 
class Data<T1, int>
{
public:
    Data() {cout<<"Data<T1, int>" <<endl;}
private:
    T1 _d1;
	int _d2; 
};

//两个参数偏特化为指针类型
template <typename T1, typename T2> 
class Data <T1*, T2*>
{
public:
    Data() {cout<<"Data<T1*, T2*>" <<endl;}
private:
    T1 _d1;
	T2 _d2; 
};

//两个参数偏特化为引用类型
template <typename T1, typename T2> 
class Data <T1&, T2&>
{
public:
    Data(const T1& d1, const T2& d2)
        : _d1(d1)
		, _d2(d2) 
	{
		cout<<"Data<T1&, T2&>" <<endl;
	}
private:
    const T1 & _d1;
    const T2 & _d2;
};

void test2 ()
{
	Data<double , int> d1;	// 调用特化的int版本
    Data<int , double> d2;	// 调用基础的模板
	Data<int *, int*> d3;	// 调用特化的指针版本
	Data<int&, int&> d4(1, 2); // 调用特化的引用版本 
}

int main(){
    test2();
    return 0;
}

#endif

#if 0
template<class T1, class T2>
class Data{
public:
    Data() {cout << "Data<T1, T2>" << endl;}
private:
	T1 _d1;
	T2 _d2; 
};

template<>
class Data<int, char>
{
public:
    Data() {cout<<"Data<int, char>" <<endl;}
private:
	int _d1;
	char _d2; 
};

void TestVector()
{
    Data<int, int> d1;  // 调用 Date
    Data<int, char> d2; // 调用 Date<int, char>
}

int main(){
    TestVector();
    return 0;
}
#endif
#if 0
class String
{
	char* _str;
public:
    String(const char* str = "")
    {
		// 构造string类对象时，如果传递nullptr指针，认为程序非法，此处断言下 
		if(nullptr == str)
		{
            assert(false);
			return; 
		}
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }

    String(const String& s)
        :_str(new char[strlen(s._str)+1])
    {
        strcpy(_str, s._str);    
    }

    // const 是因为对 s 不需要修改，安全性更高
    // 参数 & 是因为不需要传值拷贝、效率高
    // 返回值 & 是为了连续赋值（效率高）
    String& operator=(const String& s){
        if(this != &s)  // 检测是否自己给自己赋值
        {
            /*delete[] _str;
            _str = new char[strlen(s._str)+1];
            strcpy(_str, s._str);*/

            // 开辟空间如果失败，不会破坏原本对象
            char *temp = new char[strlen(s._str)+1];
            strcpy(temp, s._str);
            delete[] _str;
            _str = temp;
        }
        return *this;
    }

	~String() {
		if(_str)    // 判断当前空间是否已经释放、置空
        {
        	delete[] _str;
			_str = nullptr;
    	}
	}
};

// 测试
void TestString() {
    String s1("hello bit!!!");
    String s2(s1);
}

int main(){
    TestString();
    return 0;
}
#endif
#if 0

int main(){
    const int a = 10;
    const int b;
    return 0;
}

#endif

#if 0
#define MAX_SIZE 100
#define MAX(a, b) (a > b ? a : b)

int main(){
    int i = MAX_SIZE;
    cout << i << endl;
    int max = MAX(2, 1);
    cout << max << endl;
    cout << MAX(3,4) << endl;
    return 0;
}
#endif
#if 0
int& Add(int a, int b)
{
	int c = a + b;
	return c; 
}

int main() {
    int& ret = Add(1, 2);
    Add(3, 4);
    cout << ret << endl;    // 警告:返回与局部变量“c”关联的堆栈内存引用
    return 0;
}
#endif
#if 0
int main(){
    int a = 10;

    if(true){
        int& ra = a;
        ra = 20;
    }
    //ra = 30;    // 使用未声明的标识符
    a = 30;

    return 0;
}
#endif
#if 0
#ifdef __cplusplus  // 检测工程是否为C++工程

extern "C" 
{

#endif
	int Add(int left, int right);

	int main() {
		Add(1, 2);
		return 0;
	}

#ifdef __cplusplus 
}
#endif
#endif

#if 0
// KMP 算法
int KMP(int * next, string s1, string s2){
    int i = 0, j = 0;
    while(s1[i] != '\0' && s2[j]!='\0'){
        if(j == -1 || s1[i] == s2[j]){
            ++i;    // 继续对下一个字符比较 
            ++j;    // 模式串向右滑动
        }
        else{
            j = next[j];    // 极其反人类的语句
        }
    }
    if(s2[j] == '\0') return i-j;   // 匹配成功返回下标 
    else return -1;                	// 匹配失败返回-1 
}

void Getnext(int next[],string t){
    int j = 0, k = -1;
    next[0] = -1;
    while(j < t.length()-1) // 公共前后缀最长长度全部右移一位,最后一位不需要计算
    {
        if(k == -1 || t[j] == t[k]){
            j++, k++;
            next[j] = k;
        }
        else k = next[k];
    }
}



int main(){
    string s1 = "ababcabcacbab";
    string s2 = "cabca";
    int len = s2.size();
    int next[len];
    Getnext(next, s2);
    for(int i = 0; i < len; i++) cout << next[i] << ' ';
    cout << endl;
    cout << KMP(next, s1, s2) << endl;
    return 0;
}
#endif

#if 0
// test
void TestFunc(){}
void TestFunc(int a = 10){}

int main(){
    TestFunc(100);
    TestFunc();
    return 0;
}
#endif

#if 0
int singleNumber(vector<int>& nums) {
    int sum = 0, tmp = 0;
	for (auto i : nums){
		sum = (sum ^ i) & ~tmp;
		tmp = (tmp ^ i) & ~sum;
	}
    return sum;
}

int main(){
    int arr[] = {2, 2, 2, 3};
    vector<int> v(arr, arr+4);
    cout << singleNumber(v) << endl;
    return 0;
}

#endif
#if 0
int main(){
    int a = 10, b = 10;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << a << ' ' << b << endl;
    return 0;
}
#endif
#if 0
int main(){
    int a = 10;
    a <<= 2;
    cout << a << endl;
    return 0;
}
#endif
#if 0
int main(){
    const char *p  = "hello, world!";
    while(*p){
        cout << *p++ << ' ';
    }
    return 0;
}
#endif

#if 0
struct A
{ 
	char a; 
	short d;
    int c;
    double b; 
};

struct S1 {
    double d;
    char c;
    int i;
};

struct S2
{
    char c1;
    struct S1 s1;
    double d;
};

struct S3 {
    char c;
    int i;
    double d;
};

struct S4
{
    char c1;
    struct S3 s3;
    double d;
};

struct S5
{
    char c1;
    char c2;
    int i;
    double d1;
    double d2;
};

int main(){
    cout << sizeof(A) << endl;
    cout << offsetof(A, d) << endl;
    cout << sizeof(S1) << endl;
    cout << sizeof(S2) << endl;
    cout << sizeof(S3) << endl;
    cout << sizeof(S4) << endl;
    cout << sizeof(S5) << endl;
    return 0;
}
#endif

#if 0
int fact(int n, int r) { // <= 这里把 n, r 作为迭代变量提出来
    if (n <= 0) {
        return 1 * r; // <= 递归终止
    }
    else {
        return fact(n - 1, r * n); // <= 用迭代函数替代 fact。
    }
}

int fact_1(int _n, int _r) { // <= _n, _r 用作初始化变量
    int n = _n;
    int r = _r; // <= 将原来的 n, r 变量提出来编程迭代变量
    while (true) { // <= 生成一个迭代循环
        if (n <= 0) {
            return r;
        }
        else {
            // 更新迭代变量
            r = r * n;
            n = n - 1;
        }
    }
}

int main(){
    cout << fact(6, 1) << endl;
    return 0;
}
#endif
#if 0
int main(){
    int a[] = {1, 2, 3, 4, 5};
    cout << sizeof int << sizeof a << sizeof(int) << sizeof(a) << endl;
    return 0;
}
#endif

#if 0
// 参数解析
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    while(getline(cin, s)){
        int flag = 1, count = 1;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == ' ') ++count;
            else if(s[i] == '"'){
                do{
                    ++i;
                }while(s[i] != '"');
            }
        }
        cout << count << endl;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] != ' ' && s[i] != '"') cout << s[i];
            else if(s[i] == '"') flag ^= 1;
            else if(!flag && s[i] == ' ') cout << s[i];
            else if(flag && s[i] == ' ') cout << endl;
        }
    }
    return 0;
}
#endif
#if 0
class ObjA{
public:
    virtual void test1(){cout << "1";}
    void test2(){cout << "2";}
    void test3(){cout << "3";}
};

class ObjB : public ObjA{
public:
    void test1(){cout << "4";}
    virtual void test2(){cout << "5";}
    void test3(){cout << "6";}
};

int main(){
    ObjA * p = new ObjA;
    p->test1();
    p->test2();
    p->test3();
    delete p;
    p = new ObjB;
    p->test1();
    p->test2();
    p->test3();
    delete p;
    return 0;
}
#endif
#if 0
// 打印从1到最大的n位数
void CoutNum(vector<char>& v){
    bool flag = true;
    int len = v.size();
    for(int i = 0; i < len; ++i){
        if(flag && v[i] != '0') flag = false;
        if(!flag) cout << v[i];
    }
    cout << ' ';
}

void CoutDigitNum(vector<char> v, int len, int index){
    if(index == len-1){
        CoutNum(v);
        return;
    }
    for(int i = 0; i < 10; ++i){
        v[index+1] = i+'0';
        CoutDigitNum(v, len, index+1);
    }
}

int main(){
    int num;
    while(cin >> num){ 
        if(num <= 0){
            cout << "输入有问题，请重新输入" << endl;
            continue;
        }
        vector<char> v(num, '0');
        for(int i = 0; i < 10; ++i){
            v[0] = i+'0';
            CoutDigitNum(v, num, 0);
        }
    }
    return 0;
}
#endif
#if 0
// 方法一：基础思路
class Solution {
public:
    vector<int> printNumbers(int n) {
        int max = pow(10, n)-1;
        vector<int> v(max);
        for(int i = 0; i < max; i++) v[i] = i+1;
        return v;
    }
};

// 方法二：解决大数问题
bool increment(vector<char>& v){
    bool flag = false;
    int n = 0;
    int len = v.size();
    for(int i = len-1; i >= 0; --i){
        int sum = v[i]-'0'+n;
        if(i == len-1) sum++;
        if(sum >= 10){
            if(i == 0) flag = true;
            else{
                sum -= 10;
                n = 1;
                v[i] = '0'+sum;
            }
        }
        else{
            v[i] = '0'+sum;
            break;
        }
    }
    return flag;
}

void CoutNum(vector<char>& v){
    bool flag = true;
    int len = v.size();
    for(int i = 0; i < len; ++i){
        if(flag && v[i] != '0') flag = false;
        if(!flag) cout << v[i];
    }
    cout << ' ';
}

int main(){
    int num;
    while(cin >> num){ 
        if(num <= 0){
            cout << "输入有问题，请重新输入" << endl;
            continue;
        }
        vector<char> v(num, '0');
        while(!increment(v)){
            CoutNum(v);
        }
    }
    return 0;
}
#endif


#if 0
// 机器人的运动范围
class Solution {
    vector<vector<bool> > flag;
    int direct[4][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}};    // 左、右、上、下
public:
    int getDigitSum(int num){
        int tmp = 0;
        while(num){
            tmp += num %10;
            num /= 10;
        }
        return tmp;
    }
    
    bool check(int threshold, int rows, int cols, int row, int col){
        if(row >= 0 && col >= 0 && row < rows && col < cols && getDigitSum(row)+getDigitSum(col) <= threshold && !flag[row][col]) return true;
        return false;
    }
    int movingCountCore(int threshold, int rows, int cols, int row, int col){
        int count = 0;
        if(check(threshold, rows, cols, row, col)){
            flag[row][col] = true;
            count = 1 + movingCountCore(threshold, rows, cols, row+1, col)
                      + movingCountCore(threshold, rows, cols, row, col+1)
                      + movingCountCore(threshold, rows, cols, row-1, col)
                      + movingCountCore(threshold, rows, cols, row, col-1);
        }
        return count;
    }
    
    int movingCount(int threshold, int rows, int cols)
    {
        if(threshold < 0 || rows < 0 || cols < 0) return 0;
        
        flag = vector<vector<bool>>(rows, vector<bool>(cols, false));
        int count = movingCountCore(threshold, rows, cols, 0, 0);
        return count;
    }
};
#endif
#if 0
// 查找组成一个偶数最接近的两个素数
#include <iostream>
#include <algorithm>
using namespace std;

bool isPrime(int n){
    for(int i = 2; i <= sqrt(n); ++i){
        if(n % i == 0) return false;
    }
    return true;
}

int main(){
    int n;
    while(cin >> n){
        int half = n/2;
        while(half > 0){
            if(isPrime(half) && isPrime(n-half)) break;
            --half;
        }
        cout << half << endl << n-half << endl;
    }
    return 0;
}
#endif

#if 0
// 二进制插入
class BinInsert {
public:
    int binInsert(int n, int m, int j, int i) {
        m <<= j;
        return n ^ m;
    }
};
#endif
#if 0
// 最大连续bit数
#include <iostream>
using namespace std;

int main(){
    int n;
    while(cin >> n){
        int count, res = 0;
        while(n){
            count = 0;
            while(n & 1){
                ++count;
                n = n >> 1;
            }
            if(count > res) res = count;
            n = n >> 1;
        }
        cout << res << endl;
    }
    return 0;
}
#endif

#if 0
// 最小公共祖先
class LCA {
public:
    int getLCA(int a, int b) {
        while(a != b){
            while(a > b){
                a /= 2;
            }
            while(a < b){
                b /= 2;
            }
        }
        return a;
    }
};
#endif
#if 0
int main(){
    int **a[3][4], (**b)[3][4],  *(*c)[3][4], *(*d[3])[4];
    cout << sizeof(a) << ' ' << sizeof(b) << ' '  << sizeof(c) << ' '  << sizeof(d) << endl;
}
#endif

#if 0
// 走方格
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, m;
    while(cin >> n >> m){
        vector<vector<int>> vv(n+1, vector<int>(m+1,1));
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= m; ++j){
                vv[i][j] = vv[i-1][j]+vv[i][j-1];
            }
        }
        cout << vv[n][m] << endl;
    }
    return 0;
}
#endif


#if 0
// 合并两个有序数组
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> tmp;
        int i = 0, j = 0;
        while(i < m && j < n){
            if(nums1[i] <= nums2[j]){
                tmp.push_back(nums1[i]);
                ++i;
            }
            else{
                tmp.push_back(nums2[j]);
                ++j;
            }
        }
        while(i == m && j < n){
            tmp.push_back(nums2[j]);
            ++j;
        }
        while(i < m && j == n){
            tmp.push_back(nums1[i]);
            ++i;
        }
        nums1 = tmp;
    }
};

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m+n;
        nums1.resize(i);
        --m,--n;
        while(n >= 0){
            while(m >= 0 && nums1[m] > nums2[n]) swap(nums1[m--], nums1[--i]);
            swap(nums2[n--], nums1[--i]);
        } 
    }
};
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        nums1.resize(m+n);
        for(int i = 0; i < n; i++) nums1[m+i]=nums2[i];
        sort(nums1.begin(), nums1.end());
    }
};
#endif

#if 0
// 矩阵中的路径(回溯算法)
class Solution {
    vector<vector<bool>> flag;
    int direct[4][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}};    // 左、右、上、下
public:
    // dfs(初始矩阵，索引行坐标i，索引纵坐标j，待判断的字符串，字符串索引初始为0即先判断字符串的第一位)
    bool dfs(char * matrix, int i, int j, char * str, int pathLength){
        // 矩阵行数，矩阵列数
        int m = flag.size(), n = flag[0].size();
        // 递归终止条件
        if(str[pathLength] != matrix[i*n+j]) return false;
        // 若已经到达str末尾了，说明之前的都已经匹配成功了，直接返回true即可
        if(str[pathLength+1] == '\0') return true;
        // 要走的第一个位置置为true，表示已经走过了
        flag[i][j] = true;
        
        // 回溯，递归寻找，每次找到了就给k加一，找不到，还原
        for(int k = 0; k < 4; ++k){
            int row = direct[k][0] + i;
            int col = direct[k][1] + j;
            if(row >= m || col >= n|| row < 0 || col < 0|| flag[row][col]) continue;
            if(dfs(matrix, row, col, str, pathLength+1)) return true;
        }
        // 走到这，说明这一条路不通，还原，再试其他的路径
        flag[i][j] = false;
        return false;
    }
    
    bool hasPath(char* matrix, int rows, int cols, char* str){
        // matrix是一维数组存放二维的值
        if(matrix == NULL || rows < 1 || cols < 1 || str == NULL) return false;
        // 标志位，初始化为false
        flag = vector<vector<bool>>(rows, vector<bool>(cols, false));
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                // 循环遍历二维数组，找到起点等于str第一个元素的值
                // 再递归判断四周是否有符合条件的----回溯法
                if(matrix[i*cols+j] == str[0]){
                    if(dfs(matrix, i, j, str, 0)) return true;
                }
            }
        }
        return false;
    }
};
#endif
#if 0
int main(){
    vector<int> v;
    for(int i = 0; i < 10; ++i) v.push_back(i);
    v.resize(6);
    for(auto i : v) cout << i << ' ';
    cout << v.capacity() << endl;
    return 0;
}
#endif
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
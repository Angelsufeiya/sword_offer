#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <set>
using namespace std;

// 扑克牌中的顺子
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        if(nums.size() < 5) return false;

        sort(nums.begin(), nums.end()); 
        int countZero = 0;  // 0 的个数

        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] == 0){
                ++countZero;
                continue;
            } 

            int j = i + 1;

            if(j < nums.size()){
                // 如果相邻两个元素相等，就不是顺子
                if(nums[i] == nums[j]) return false;

                int tmp = nums[j] - nums[i];
                while(tmp > 1){
                    if(countZero == 0) return false;

                    --countZero;    // 相邻两个数的差距用 0 来弥补
                    --tmp;  // 差距减小 1
                }
            }
        }
        return true;
    }
};



// n个骰子的点数
class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<double> res(n * 6 - n + 1);
        vector<vector<int>> dp(n + 1, vector<int>(6 * n + 1, 0));   // 将全部值初始化为 0

        int row = dp.size(), col = dp[0].size();
        for(int n = 1; n <= 6; ++n){
            dp[1][n] = 1;   // 初始化 dp 数组
        }

        for (int n = 2; n < row; ++n) {
            for (int s = n; s < col; ++s) {
                // 注意 s 从 n 开始，因为 s 的最小值为 n
                // 比如掷 3 个骰子，s 最小为 3
                for (int k = 1; k <= 6; ++k) {
                    if (s - k > 0) {
                        dp[n][s] += dp[n - 1][s - k];
                    }
                    else {
                        break;
                    }
                }
            }
        }

        double deno = pow(6.0, n); // 分母

        for (int s = n; s <= 6 * n; ++s) {
            // s 的最小值为 n，在 res 里是第 s - n 位
            res[s - n] = dp[n][s] / deno;
        }

        return res;
    }
};



// 队列的最大值
class MaxQueue {
    queue<int> q;
    deque<int> d;
public:
    MaxQueue() {}
    
    int max_value() {
        if(d.empty()) return -1;
        return d.front();
    }
    
    void push_back(int value) {
        while(!d.empty() && d.back() < value){
            d.pop_back();
        }
        d.push_back(value);
        q.push(value);
    }
    
    int pop_front() {
        if(q.empty()) return -1;
        int res = q.front();
        if(res == d.front()) d.pop_front();
        q.pop();
        return res;
    }
};

#endif

#if 0
// 滑动窗口的最大值
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.size() < k || k <= 0 || nums.empty()) return {};

        vector<int> res;
        int start = 0, end = k - 1;
        while(end < nums.size()){
            int temp = nums[start];
            for(int i = start+1; i <= end; ++i){
                temp = max(temp, nums[i]);
            }
            res.push_back(temp);
            ++start;
            ++end;
        }
        return res;
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.size() < k || k <= 0 || nums.empty()) return {};

        vector<int> res;
        deque<int> findMax;

        for (int i = 0; i < nums.size(); ++i) {
            // i 每加一次，代表滑动窗口向右移一个单位。
            // i 指向的是每个滑动窗口的尾部元素（从 i = k - 1 开始）。

            if (i >= k && !findMax.empty()) {
                // i >= k 是为了确保 findMax.front() 至少为第一个完整的滑动窗口的最大值索引。
                // 即至少形成了一个完整的滑动窗口。
                res.push_back(nums[findMax.front()]);
            }

            while (!findMax.empty() && nums[i] >= nums[findMax.back()]) {
                // 如果新进来的 nums[i] 大于等于滑动窗口的尾部元素，
                // 说明该尾部元素肯定不会是任何滑动窗口的最大元素。
                // 就想象公司新来了一个既比你年轻又比你能干（大于等于你）的人，那你就只能被淘汰了，
                // 而且是循环淘汰掉所有不如新员工的老员工。
                findMax.pop_back();
            }

            if (!findMax.empty() && i - findMax.front() >= k) {
                // 虽然 findMax 的头部是最大的元素的索引，但是如果当前滑动窗口已不包括该索引，
                // 那么需要弹出该索引。
                // 就想象即使是公司的骨干成员，但是过了35岁也要被淘汰。
                findMax.pop_front();
            }

            findMax.push_back(i);
        }

        res.push_back(nums[findMax.front()]); // 最后一个滑动窗口还没计算就退出了 for 循环，需补上。

        return res;
    }
};

#endif

#if 0
// 左旋转字符串

class Solution {
public:
    string reverseLeftWords(string s, int n) {
        if(n >= s.length() || s.length() < 2 || n == 0) return s;
        
        int count = 0;
        while(count < n){
            s += s[0];
            s.erase(0, 1);
            count++;
        }
        return s;
    }
};

class Solution {
public:
    string reverseLeftWords(string s, int n) {
        if (n >= s.length() || s.length() < 2 || n == 0) {
            return s;
        }

        reverse(s, 0, n - 1);   // 翻转 s1 部分
        reverse(s, n, s.length() - 1);  // 翻转 s2 部分
        reverse(s, 0, s.length() - 1);  // 翻转整个字符串 s

        return s;
    }

    void reverse(string& s, int start, int end) {
        if (end >= s.length() || end - start < 1) {
            return;
        }

        while (start < end) {
            char temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++; end--;
        }
    }
};
#endif

#if 0
// 翻转单词顺序
class Solution {
public:
    string reverseWords(string s) {
        int len = s.length();

        if (len == 0) {
            return "";
        }

        int j = len - 1;
        string res = "";

        while (j >= 0) {
            if (s[j] == ' ') {
                // 当 s[j] 是空格时，j 不断左移
                j--;
                continue;
            }

            while (j >= 0 && s[j] != ' ') {
                // 注意 while 里必须用 && 短路求值，且 j >= 0 要放前面
                // 不然如果 j 变成 -1，那么计算 s[j] 会发生溢出错误！
                j--;
            }
            
            int pos = j; // 用 pos 保存 j 当前的位置
            j++; // j 现在指向的是一个空格，需要右移一位才能指向一个单词的开头

            while (s[j] != ' ' && j < len) {
                // 向 res 中添加单词
                res += s[j];
                j++;
            }

            j = pos; // j 回到新添加的单词的最左端再往左一个空格处
            res += ' '; // 单词添加完毕后需要加上一个空格
        }
        if(res.length() > 0){
            res.erase(res.length() - 1, 1);
        }

        return res;
    }
};

class Solution {
public:
    string reverseWords(string s) {
        int k = 0;
        for (int i = 0; i < s.size(); ++i){
            while (i < s.size() && s[i] == ' ') {
                ++i;    // 找到第一个非空格字符
            }
            if (i == s.size()) break;
            int j = i;
            while (j < s.size() && s[j] != ' ') ++j;    //遍历1个非空单词
            reverse(s.begin() + i, s.begin() + j);      //反转1个单词
            if (k) s[k++] = ' ';
            while (i < j) s[k++] = s[i++];      //反转后的1个单词赋给s[k]
        }
        s.erase(s.begin() + k, s.end());   //删除 k后面空格
        reverse(s.begin(), s.end());
        return s;
    }
};

#endif


#if 0 
// 和为s的连续正数序列
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        if (target == 1 || target == 2) return {};

        vector<vector<int>> res;
        vector<int> v;
        int sum = 0, limit = target / 2;
        for(int i = 1; i <= limit; ++i){
            for(int j = i; ; ++j){
                v.push_back(j);
                sum += j;
                if(sum == target){
                    res.push_back(v);
                    v.clear();
                }
                else if(sum > target){
                    sum = 0;
                    v.clear();
                    break;
                }
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        if (target == 1 || target == 2) return {};

        vector<vector<int>> res;
        vector<int> v;
        for (int l = 1, r = 2; l < r;){
            int sum = (l + r) * (r - l + 1) / 2;
            if (sum == target) {
                v.clear();
                for (int i = l; i <= r; ++i) {
                    v.emplace_back(i);
                }
                res.emplace_back(v);
                l++;
            } else if (sum < target) {
                r++;
            } else {
                l++;
            }
        }
        return res;
    }
};



// 和为s的两个数字
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if (nums.size() == 1) {
            return {};
        }

        int i = 0, j = nums.size()-1;
        while(i < j){
            if(nums[i] + nums[j] == target) {
                return {nums[i], nums[j]};
            }
            else if(nums[i] + nums[j] > target) 
                --j;
            else 
                ++i;
        }
        return {};
    }
};

#endif

#if 0
// 平衡二叉树
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;

        return (abs(maxDepth(root->left) - maxDepth(root->right)) <= 1) && isBalanced(root->left) && isBalanced(root->right);
    }
private:
    int maxDepth(TreeNode* root){
        if(!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int depth = 0;
        return isBalanced(root, depth);
    }
private:
    bool isBalanced(TreeNode* root, int& depth){
        if(root == nullptr){
            depth = 0;
            return true;
        }
        int l = 0, r = 0;
        if(isBalanced(root->left, l) && isBalanced(root->right, r)){
            int dif = abs(l - r);
            if(dif <= 1){
                depth = (l > r ? l : r) + 1;
                return true;
            }
        }
        return false;
    }
};

#endif


#if 0
// 二叉树的深度
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;

        int l = maxDepth(root->left);
        int r = maxDepth(root->right);
        
        return max(l, r) + 1;
    }
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;

        queue<TreeNode*> bfs;
        bfs.push(root);
        int res = 0;

        while (!bfs.empty()) {
            // 第一层循环确保当前层还有元素
            queue<TreeNode*> temp;  // temp 用于储存当前层的下一层的所有元素
            while (!bfs.empty()) {
                // 第二层循环则是遍历当前层的所有元素
                if (bfs.front()->left) {temp.push(bfs.front()->left);}
                if (bfs.front()->right) {temp.push(bfs.front()->right);}
                bfs.pop();
            }
            ++ res; // 层数 +1
            bfs = temp; // bfs 更新到当前层的下一层
        }

        return res;
    }
};

#endif


#if 0
// 数组中数字出现的次数
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int ret = 0, sz = nums.size();
        for(int n : nums){
            ret ^= n;
        }
        int div = 1;
        while((div & ret) == 0){
            div <<= 1;
        }
        int a = 0, b = 0;
        for(int n : nums){
            if(div & n){
                a ^= n;
            }
            else{
                b ^= n;
            }
        }
        return vector<int>{a, b};
    }
};

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        for(auto i = 0; i < nums.size()-3; i += 3)  //每三个数检查一次
        {
            if(nums[i] != nums[i+2])    //很好理解，比如0，0，0，1，3，3，3
                return nums[i];         //第一次检查，nums[0] == nums[2];i+2，检查下一组
        }                               //第二次检查，nums[3] != nums[5]，返回nums[3]。
        return nums.back();
    }
};

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> m;
        for(int n : nums){
            m[n]++;
        }
        int res = 0;
        for(auto i : m){
            if (i.second == 1) {
                res = i.first;
                break;
            }
        }
        return res;
    }
};

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int i = 0; i < 32; ++i){
            int cnt = 0;
            for(int n : nums){
                // n & 1 << i 的值大于0即为真
                if(n & (1 << i)) cnt++;
            }
            // 构造只出现一次的那个数字，采用异或的方法生成二进制中的每一位
            if(cnt % 3 == 1) res ^= (1 << i);
        }
        return res;
    }
};

#endif

#if 0
// 两个链表的第一个公共节点
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr || headB == nullptr) return nullptr;
        ListNode* p = headA;
        ListNode* q = headB;
        while(p != q)
        {
            if(p == nullptr)  p = headB;	// p指向另一个链表头
            else p = p->next;
            if(q == nullptr) q = headA;		// q指向另一个链表头
            else q = q->next;
           
        }
        return p;
    }
};



// 在排序数组中查找数字
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int count = 0;

        for (int i : nums) {
            if (target == i) {
                ++count;
            }
        }

        return count;
    }
};

class Solution {
public:
    int search(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for(int i : nums){
            m[i]++;
        }
        return m[target];
    }
};

class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto l=lower_bound(nums.begin(),nums.end(),target);
        auto r=upper_bound(nums.begin(),nums.end(),target);
        return r-l;
    }
};

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0) return 0;

        int count = 0, l = 0, r = nums.size();
        while(l < r){
            int mid = l + (r - l) / 2;

            if(nums[mid] >= target) r = mid;
            else l = mid +1;
        }
        
        for(int i = l; i < nums.size(); ++i){
            if(nums[i] == target) ++count;
            else break;
        }
        return count;
    }
};



// 0～n-1中缺失的数字
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        if(nums.size() == 0) return -1;

        for(int i = 0; i < nums.size(); ++i){
            if(i != nums[i]) return i;
        }
        return nums.size();
    }
};

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        if(nums.size() == 0) return -1;

        int l = 0, r = nums.size()-1;
        while(l <= r){
            int mid = l + (r - l) / 2;
            if(nums[mid] == mid) l = mid + 1;
            else r = mid - 1;
        }
        return l;
    }
};



// 二叉搜索树的第k大节点
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthLargest(TreeNode* root, int k) {
        int res = 0;
        dfs(root, res, k);
        return res;
    }
private:
    void dfs(TreeNode* root, int& res, int& k){
        if(root == nullptr) return;
        dfs(root->right, res, k);
        if(k == 1) res = root->val;
        dfs(root->left, res, --k);
    }
};

class Solution {
public:
    int kthLargest(TreeNode* root, int &k) {
        stack<TreeNode*> st;
        while(root || st.size()){
            while(root){
                st.push(root);  // 根入栈
                root = root->right; // 访问右子树，向下探
            }
            root = st.top(), st.pop();    // 出栈
            if(!--k) return root->val;
            root = root->left;  // 访问左子树
        }
        return 0;
    }
};

#endif

#if 0
// 数组中的逆序对
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int count = 0;
        for(int i = 0; i < nums.size(); ++i){
            for(int j = i+1; j < nums.size(); ++j){
                if(nums[i] > nums[j]) ++ count;
            }
        }
        return count;
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums){
        int sz = nums.size();
        // 若不存在数对，直接 return 0
        if (sz < 2) return 0;

        vector<int> tmp(sz);
        return mergeSort(nums, tmp, 0, sz-1);
    }
private:
    int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r){
        if (l >= r) return 0;   // 递归终止条件是只剩一个元素了（即不存在数对了）

        int mid = l + (r - l) / 2;  // 此算式等同于 (l + r) / 2，是为了避免溢出
        int leftPairs = mergeSort(nums, tmp, l, mid);    // 计算左半部分的逆序对
        int rightPairs = mergeSort(nums, tmp, mid+1, r); // 计算右半部分的逆序对
        
        if(nums[mid] <= nums[mid+1]){
            // 即如果左右都已排好序，而且左边的最大值 <= 右边的最小值，那么就不存在跨越左边和右边的逆序对了
            return leftPairs + rightPairs;
        }
        int crossPairs = mergeAndCount(nums, tmp, l, mid, r);   // 计算跨越左边和右边的逆序对

        return leftPairs + rightPairs + crossPairs;
    }
    
    // 本函数的前提条件是：左半部分和右半部分都是已经按升序排好序了的
    int mergeAndCount(vector<int>& nums, vector<int>& tmp, int l, int mid, int r){
        // 因为本函数是从左右部分都只有一个元素的情况开始运行的（自底向上），所以是可以保证前提条件的
        for(int i = l; i <= r; ++i){
            tmp[i] = nums[i];   // 先填充 tmp 辅助数组
        }
        int i = l, j = mid+1;   // i 和 j 分别是左半部分和右半部分的起点
        int count = 0;  // count 用来统计逆序对数量

        for(int k = l; k <= r; ++k){
            if(i == mid + 1){
                // 假如 i 已经越过左边的边界，直接填充右半部分进 nums;
                nums[k] = tmp[j];
                ++j;
            }
            else if(j == r + 1){
                // 假如 j 已经越过右边的边界，直接填充左半部分进 nums
                nums[k] = tmp[i];
                ++i;
            }
            else if(tmp[i] <= tmp[j]){
                // 假如左边小于等于右边，那就不是逆序对，不用修改 count
                nums[k] = tmp[i];
                ++i;
            }
            else if(tmp[i] > tmp[j]) {
                // 假如左边大于右边，是逆序对，count += 当前左边 [i, mid] 的所有元素
                // 因为假如左边是 [7,8]，右边是[5,6]，然后 i 指向 7，j 指向 5
                // 那么 5 和 7、8 都构成了逆序对，也就是此时有两对新的逆序对
                // 所以可以总结出规律：count += mid - i + 1
                nums[k] = nums[j];
                count += mid - i + 1;
                ++j;
            }
        }
        return count;
    }
};

class BIT {
private:
    vector<int> tree;
    int n;

public:
    BIT(int _n): n(_n), tree(_n + 1) {}

    static int lowbit(int x) {
        return x & (-x);
    }

    int query(int x) {
        int ret = 0;
        while (x) {
            ret += tree[x];
            x -= lowbit(x);
        }
        return ret;
    }

    void update(int x) {
        while (x <= n) {
            ++tree[x];
            x += lowbit(x);
        }
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> tmp = nums;
        // 离散化
        sort(tmp.begin(), tmp.end());
        for (int& num: nums) {
            num = lower_bound(tmp.begin(), tmp.end(), num) - tmp.begin() + 1;
        }
        // 树状数组统计逆序对
        BIT bit(n);
        int ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            ans += bit.query(nums[i] - 1);
            bit.update(nums[i]);
        }
        return ans;
    }
};

#endif

#if 0
// 礼物的最大价值
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0) return 0;

        int row = grid.size(), col = grid[0].size();
        vector<vector<int> > dp(row, vector<int>(col, 0));

        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                int left = 0, up = 0;

                if(i > 0) up = dp[i - 1][j];
                if(j > 0) left = dp[i][j - 1];

                dp[i][j] = max(up, left) + grid[i][j]; // 状态转移方程
            }
        }   
        return dp[row - 1][col - 1];
    }
};

class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0) return 0;

        int row = grid.size(), col = grid[0].size();
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                if(i == 0 && j == 0){
                    continue;
                }
                else if(i == 0){
                    grid[i][j] += grid[i][j-1];
                }
                else if(j == 0){
                    grid[i][j] += grid[i-1][j];
                }
                else{
                    grid[i][j] += max(grid[i-1][j], grid[i][j-1]);
                }
            }
        }   
        return grid[row - 1][col - 1];
    }
};

class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0) return 0;

        int row = grid.size(), col = grid[0].size();
        for(int i = 1; i < col; ++i) {  // 初始化第一行
            grid[0][i] += grid[0][i-1];
        }
        for(int i = 1; i < row; ++i){   // 初始化第一列
            grid[i][0] += grid[i-1][0];
        }
        for(int i = 1; i < row; ++i) {
            for(int j = 1; j < col; ++j) {
                grid[i][j] += max(grid[i-1][j], grid[i][j-1]);
            }
        }   
        return grid[row - 1][col - 1];
    }
};

#endif
#if 0
// 丑数
class Solution {
public:
    bool determine(int num){
        if(num > 0 && num <= 6) return true;
        else if(num < 0) return false;
        
        while(num % 5 == 0) num /= 5;
        while(num % 3 == 0) num /= 3;
        while(num % 2 == 0) num /= 2;
        return num == 1;
    }
    int nthUglyNumber(int n) {
        int count = 0;
        int i = 0;
        while(count != n){
            if(determine(++i)) ++count;
        }
        return i;
    }
};

class Solution {
public:
    int nthUglyNumber(int n) {
        int p2 = 0, p3 = 0, p5 = 0;
        vector<int> dp(n);
        dp[0] = 1;
        for(int i = 1; i < n; ++i){
            dp[i] = min(min(dp[p2]*2, dp[p3]*3), dp[p5]*5);
            if(dp[i] == dp[p2]*2) ++p2;
            if(dp[i] == dp[p3]*3) ++p3;
            if(dp[i] == dp[p5]*5) ++p5;
        }
        return dp[n-1];
    }
};

#endif

#if 0
// 最长不含重复字符的子字符串
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int n = s.size();
        int res = 0;
        vector<int> v(128, -1);
        for(int i = 0; i < n; ++i){
            if(v[s[i]] >= left){
                left = v[s[i]]+1;
            }
            v[s[i]] = i;
            res = max(res, i-left+1);
        }
        return res;
    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char, int> m;
        int res = 0, l = 0, r = 0;
        while (r < s.size()) {
            if (m.find(s[r]) != m.end()) {
                l = max(l, m[s[r]] + 1);
            }
            m[s[r++]] = r;
            res = max(r - l, res);
        }
        return res;
    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        if(len < 2) return len;

        int res = -1, right = 0;
        unordered_set<char> store;
        for(int left = 0; left < len; ++left) {
            while(right < len && !store.count(s[right])) {
                store.insert(s[right]);
                ++right;
            }
            res = max(res, right - left);
            store.erase(s[left]);
            if(right >= len) break;
        }

        return res;
    }
};


#endif


#if 0
// 把数字翻译成字符串
class Solution {
public:
    int backtrack(string& s, int i){
        int n = s.size();
        if(i == n) return 1;
        if(i == n-1 || s[i] == '0' || s.substr(i, 2) > "25") 
            return backtrack(s, i+1);
        return backtrack(s, i+1) + backtrack(s, i+2);
    }
    int translateNum(int num) {
        string s = to_string(num);
        return backtrack(s, 0);
    }
};

class Solution {
public:
    int translateNum(int num) {
        if(num < 10) return 1;

        string s = to_string(num);
        int len = s.length();
        vector<int> dp(len + 1);
        dp[1] = 1; // 显而易见 dp[1] = 1
        dp[0] = 1; // 比如 num = 12，有两种方法，即 dp[2] = dp[1] + dp[0]，可得 dp[0] = 1

        for(int i = 2; i <= len; ++i) {
            if(s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '5')) {
                dp[i] = dp[i - 2] + dp[i - 1];
            }
            else {
                dp[i] = dp[i - 1];
            }
        }

        return dp[len];
    }
};

#endif

#if 0

class Solution {
public:
    string minNumber(vector<int>& nums) {
        if(nums.size() == 1) return to_string(nums[0]);

        vector<string> v;
        string res;
        for(auto i : nums) v.push_back(to_string(i));
        sort(v.begin(), v.end(), strCompare);   // 自定义 strCompare 函数
        for(auto i : v) res += i;
        return res;
    }

    static bool strCompare(const string& s1, const string& s2){ // 注意 static
        string add1 = s1 + s2;
        string add2 = s2 + s1;
        return add1 < add2;
    }
};

#endif

class Solution {
public:
    string minNumber(vector<int>& nums) {
        if(nums.size() == 1) return to_string(nums[0]);

        vector<string> v;
        string res;
        for(auto i : nums) v.push_back(to_string(i));
        sort(v.begin(), v.end(), strCompare);   // 自定义 strCompare 函数
        for(auto i : v) res += i;
        return res;
    }

    static bool strCompare(const string& s1, const string& s2){ // 注意 static
        string add1 = s1 + s2;
        string add2 = s2 + s1;
        return add1 < add2;
    }
};

#if 0
// 数字序列中某一位的数字
int findNthDigit(int n) {
    if(n < 0) return -1;
    if(n == 0) return 0;

    int digit = 1;  // 数位（各位/十位/百位... 对应 1/2/3...）
    long start = 1; // 属于该数位的所有数的起点数（个位是1，十位是10，百位是100）
    long index_count = digit * 9 * start;   // 该数位的数一共的索引个数

    while(n > index_count){
        // 找出 n 属于哪个数位里的索引
        n -= index_count;
        ++digit;
        start *= 10;
        index_count = digit * 9 * start;
    }
    // 上面的循坏结束后
    // digit 等于原始的 n 所属的数位；start 等于原始 n 所属数位的数的起点
    // index_count 等于原始的 n 所属数位的索引总个数（不重要了，下面不用）
    // n 等于在当前数位里的第 n-1 个索引（索引从 0 算起）
    long num = start + (n-1)/digit; // 得到原始的 n 对应哪个数字
    int remainder = (n-1) % digit;  // 余数就是原始的 n 是这个数字中的第几位

    string s_num = to_string(num);
    return int(s_num[remainder] - '0'); // n 对应着第 remainder 位，再转成 int
}

int main(){
    cout << findNthDigit(10) << endl;
}
#endif

#if 0
// 连续子数组的最大和

class Solution {
public:
    int maxSubArray(vector<int>& array) {
        assert(!array.empty());

        int sum = array[0], res = array[0];
        
        for(int i = 1; i < array.size(); i++){
            sum >= 0 ? sum += array[i] : sum = array[i];
            if(sum > res) res = sum;
        }
        return res;
    }
};

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        assert(!nums.empty());

        int sz = nums.size();
        int Max = nums[0];
        // 如果当前值小于0，重新开始（全局最大值更新）
        for(int i = 1; i < sz; ++i){
            // 更新当前最大值
            if(nums[i-1] > 0) nums[i] += nums[i-1];
            // 更新全局最大值
            Max = max(nums[i], Max);
        }
        return Max;
    }
};

#endif

#if 0
// 数据流中的中位数
class MedianFinder {
    priority_queue<int, vector<int>, less<int>> maxheap;
    priority_queue<int, vector<int>, greater<int>> minheap;
public:
    /** initialize your data structure here. */
    MedianFinder() {}
    
    void addNum(int num) {
        if(maxheap.size() == minheap.size()){
            maxheap.push(num);
            minheap.push(maxheap.top());
            maxheap.pop();
        }
        else{
            minheap.push(num);
            maxheap.push(minheap.top());
            minheap.pop();
        }
    }
    
    double findMedian() {
        int maxSz = maxheap.size(), minSz = minheap.size();
        double mid1 = maxheap.top(), mid2 = minheap.top();
        return maxSz == minSz ? ((mid1+mid2)/2) : mid2;
    }
};

#endif


#if 0
// 最小的K个数

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res;
        sort(arr.begin(), arr.end());
        for(int i = 0; i < k; ++i){
            res.push_back(arr[i]);
        }
        return res;
    }
};

class Solution {
public:
    void QuickSort(vector<int>& v, int left, int right, int k){
        if(left > right) return;
        int i = left, j = right, tmp = v[left];
        while(i < j){
            while(v[j] >= tmp && i < j) j--;
            while(v[i] <= tmp && i < j) i++;
            if(i < j) swap(v[i], v[j]);
        }
        v[left] = v[i];
        v[i] = tmp;

        if(i == k-1) return;
        else if(i < k-1) return QuickSort(v, i+1, right, k);
        else return QuickSort(v, left, i-1, k);
    }

    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        QuickSort(arr, 0, arr.size()-1, k);
        vector<int> res;
        for(int i = 0; i < k; i++) res.push_back(arr[i]);
        return res;
    }
};

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> vec;
        if (k == 0) return vec; // 排除 0 的情况
        
        priority_queue<int> Q;
        for (int i = 0; i < k; ++i) {
            Q.push(arr[i]);
        }
        for (int i = k; i < arr.size(); ++i) {
            if (Q.top() > arr[i]) {
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i) {
            vec.push_back(Q.top());
            Q.pop();
        }
        return vec;
    }
};

#endif

#if 0
// 求数组中出现超过一半的数字
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int num = nums[nums.size()/2];
        if(nums.size()/2 < count(nums.begin(), nums.end(), num)){
            return num;
        }
        return 0;
    }
};

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> mp;
        for (auto x : nums) mp[x]++;
        for (auto [k, v] : mp) {
            if (v > n/2) return k;
        }
        return 0;
    }
};

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> v) {
        int num = v[0], count_i = 1;
        for(int i = 1; i < v.size(); i++){
            if(v[i] == v[i-1]) count_i++;
            else {
                if(count_i <= 1) num = v[i];
                else count_i--;
            }
        }
        if (v.size() / 2 < count(v.begin(), v.end(), num)) return num;
        return 0;
    }
};

#endif


#if 0
// 字符串的排列

class Solution {
public:
    vector<string> permutation(string s) {
        vector<string> res;
        dfs(s, res, 0); // 从 s 的第一位开始排列起，所以传了 0
        return res;
    }
    void dfs(string &s, vector<string> &res, int depth)
    {
        if(depth >= s.size()-1)
        {
            res.push_back(s);   // 某条路从头排列到尾了，把这条路的结果输入 res
            return ;
        }
        unordered_set<char> used;  // 用于剪枝，不能定义为全局，因为每次递归需要创建一个新的 hashset
        for(int i = depth; i < s.size(); ++i)
        {
            if(used.count(s[i])) continue;  // 如果是重复的元素，不要再排一次
            
            used.insert(s[i]);
            swap(s[depth],s[i]);
            dfs(s, res, depth+1);   // 开始往下一层递进
            swap(s[depth],s[i]);    // 回溯撤销操作
        }
    }
};

#endif


#if 0
// 序列化二叉树

class Codec {
public:
    // Encodes a tree to a single string.
    // 队列层序遍历
    string serialize(TreeNode* root) {
        string res = "";
        if(!root) return res;

        queue<TreeNode*> qu;
        qu.push(root);
        TreeNode* cur = new TreeNode(0);
        while(!qu.empty()){
            // 记录队列里的元素长度
            int len = qu.size();
            while(len--){
                cur = qu.front();
                qu.pop();
                if(!cur) res += "null";
                else res += to_string(cur->val);
                res += ',';
                if(cur){
                    qu.push(cur->left);
                    qu.push(cur->right);
                }
            }
        }
        res.pop_back();
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.size() == 0) return nullptr;
        int len = data.size();
        int i = 0;
        vector<TreeNode*> v;
        while(i < len){
            //遇到逗号停下来。
            string str = "";
            while(i<len && data[i]!=','){
                str += data[i];
                i++;
            }
            if(str == "null"){
                TreeNode* tmp = nullptr;
                v.push_back(tmp);
            }
            else{
                int temp = stoi(str);
                TreeNode* cur = new TreeNode(temp);
                v.push_back(cur);
            }
            i++;
        }
        // 遍历v，构建二叉树
        for(int i = 0, j = 1; j < v.size(); ++i){
            if(!v[i]) continue;
            if(j < v.size()) v[i]->left = v[j++];
            if(j < v.size()) v[i]->right = v[j++];
        }
        return v[0];
    }
};

class Solution {
public:
    char* Serialize(TreeNode *root) {    
        if (!root) return "#";
     
        string res = to_string(root->val);
        res.push_back(',');
     
        char* left = Serialize(root->left);
        char* right = Serialize(root->right);
        char* ret = new char[strlen(left)+strlen(right)+res.size()];
        // 如果是string类型，直接用operator += ,这里char* 需要用函数
        strcpy(ret, res.c_str());
        strcat(ret, left);
        strcat(ret, right);
     
        return ret;
    }
    TreeNode* deseri(char *&s) {
        if (*s == '#') {
            ++s;
            return nullptr;
        }
     
        // 构造根节点值
        int num = 0;
        while (*s != ',') {
            num = num * 10 + (*s - '0');
            ++s;
        }
        ++s;
        // 递归构造树
        TreeNode *root = new TreeNode(num);
        root->left = deseri(s);
        root->right = deseri(s);
     
        return root;
    }
    TreeNode* Deserialize(char *str) {
        return deseri(str);
    }
};

#endif

#if 0
// 二叉搜索树与双向链表
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return nullptr;
        Node* head = nullptr, *pre =nullptr;    // head保存头结点，pre保存中序遍历过程中的上一个节点
        inOrder(root, head, pre);
        head->left = pre;
        pre->right = head;
        return head;
    }
    
    void inOrder(Node* cur, Node* &head, Node* &pre){
        if(!cur) return;
        inOrder(cur->left, head, pre);

        if(!pre) head = cur;    // 说明当前是第一个节点，作为头结点
        else{
            cur->left = pre;
            pre->right = cur;
        }
        pre = cur;

        inOrder(cur->right, head, pre);
    }
};

#endif

#if 0
// 复杂链表的复制

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        Node* cur = head;
        unordered_map<Node*, Node*> map;
        // 复制节点，建立 “原节点 -> 新节点” 的 map 映射
        while(cur){
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        // 构建新链表的 next 和 random 指向
        while(cur){
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        // 返回新链表的头节点
        return map[head];
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        Node* cur = head;
        // 1.复制各节点，构建拼接链表
        while(cur){
            Node* tmp = new Node(cur->val);
            tmp->next = cur->next;
            cur->next = tmp;
            cur = tmp->next;
        }
        // 2.构建各新节点的 random 指向
        cur = head;
        while(cur){
            if(cur->random) cur->next->random = cur->random->next;
            cur = cur->next->next;
        }
        // 3.拆分两链表
        cur = head->next;
        Node* pre = head, *res = head->next;
        while(cur->next){
            pre->next = pre->next->next;
            cur->next = cur->next->next;
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = nullptr; // 单独处理原链表尾节点
        return res;
    }
};

#endif



#if 0
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 二叉树是否有和为某值的路径
bool hasPathSum(TreeNode* root, int sum) {
    if (nullptr == root) return false;
    else if (root->val == sum && root->left == nullptr && root->right == nullptr) {
        return true;
    }
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

// 找出和为某值的所有路径
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> cur;
        dfs(root, sum, res, cur);
        return res;
    }

    void dfs(TreeNode* root, int sum, vector<vector<int>>& res, vector<int>& cur){
        if(!root) return;
        cur.push_back(root->val);
        sum -= root->val;
        if(sum == 0 && !root->left && !root->right) res.push_back(cur); // 满足路径条件

        dfs(root->left,  sum, res, cur);
        dfs(root->right, sum, res, cur);
        cur.pop_back(); // 关键点：回溯
    }
};

#endif


#if 0
// 二叉搜索树的后序遍历
class Solution {
public:
    bool isBST(vector<int>& post, int l, int r){    // [l, r]表示当前区间，左闭右闭
        if(l >= r) return true;
        int root = post[r];
        // 在二叉搜索树中左子树节点的值小于跟节点的值
        int i = l;
        while(i < r){
            if(post[i] > root) break;
            ++i;
        }
        // 在二叉搜索树中右子树节点的值大于跟节点的值
        int j = i;
        while(j < r){
            if(post[j] < root) return false;
            ++j;
        }
        //[l, i - 1]表示左子树， [i, r - 1]表示右子树
        return isBST(post, l, i - 1) && isBST(post, i, r - 1);//递归判断左子树及右子树
    }

    bool verifyPostorder(vector<int>& postorder) {
        int sz = postorder.size();
        if(sz <= 2) return true;
        return isBST(postorder, 0, sz-1);
    }
};

#endif

#if 0
// 层序遍历

// 一维数组
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;

        if(!root){
            return vv;
        }

        vector<int> temp;
        queue<TreeNode*> qu;
        TreeNode* cur;

        int len = 1;
        qu.push(root);

        while(!qu.empty()){
            for(int i = 0; i < len; i++){
                cur = qu.front();
                temp.push_back(cur->val);
                qu.pop();

                if(cur->left){
                    qu.push(cur->left);
                }
                if(cur->right){
                    qu.push(cur->right);
                }
            }
            vv.push_back(temp);
            temp.clear();
            len = qu.size();
        }

        return vv;
    }
};

// 二维数组
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > vv;
        if(!root) return vv;

        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty()){
            vector<int> v;	// 每层需要重新开辟（可在循环外开辟，在循环结束时，对v进行清理）
            int len = qu.size();	// 每次需要重新定义变量（可在循环外，在循环结束时，重新计算len）
            for(int i = 0; i < len; ++i){
                TreeNode* tmp = qu.front();
                qu.pop();
                v.push_back(tmp->val);
                if(tmp->left) qu.push(tmp->left);
                if(tmp->right) qu.push(tmp->right);
            }
            vv.push_back(v);
        }
        return vv;
    }
};

// 之字形
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > vv;
        if(!root) return vv;

        queue<TreeNode*> qu;
        qu.push(root);
        int flag = 0;
        while(!qu.empty()){
            vector<int> v;
            int len = qu.size();
            for(int i = 0; i < len; ++i){
                TreeNode* tmp = qu.front();
                qu.pop();
                v.push_back(tmp->val);
                if(tmp->left) qu.push(tmp->left);
                if(tmp->right) qu.push(tmp->right);
            }
            if(flag) reverse(v.begin(), v.end());
            vv.push_back(v);
            flag ^= 1;
        }
        return vv;
    }
};

// 从下到上
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int> > vv;
        if(!root) return vv;

        vector<int> temp;
        queue<TreeNode*> qu;
        TreeNode* cur;
        int len = 1;
        qu.push(root);
        while(!qu.empty()){
            for(int i = 0; i < len; i++){
                cur = qu.front();
                temp.push_back(cur->val);
                qu.pop();
                if(cur->left) qu.push(cur->left);
                if(cur->right) qu.push(cur->right);
            }
            vv.push_back(temp);
            temp.clear();
            len = qu.size();
        }

        reverse(vv.begin(),vv.end());
        //vector<vector<int>> res;
        //for(int i = 1; i <= vv.size();i++){
        //    res.push_back(vv[vv.size() - i]);
        //}

        return vv;
    }
};
#endif

#if 0
// 栈的插入与输出
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> tmp;
        int i = 0;
        
        for(auto & vi : pushV){
            tmp.push(vi);
            
            for(; !tmp.empty() && tmp.top() == popV[i]; ++i){
                tmp.pop();
            }
        }
        return tmp.empty();
    }
};

#endif
#if 0
class MinStack {
    stack<int> m_data;
    stack<int> m_min;
public:
    /** initialize your data structure here. */
    MinStack() 
    {}
    
    void push(int x) {
        m_data.push(x);

        if(m_min.empty() || m_min.top() >= x){
            m_min.push(x);
        }
    }
    
    void pop() {
        if(m_data.top() == m_min.top()){
            m_min.pop();
        }

        m_data.pop();
    }
    
    int top() {
        return m_data.top();
    }
    
    int getMin() {
        return m_min.top();
    }
};

#endif
#if 0
bool isNumber(string s) {
    if(s.size() == 0) return false;
    int i = 0;
    if(s[i] == '+' || s[i] == '-') ++i;
    
    int num = 0, dot = 0, e = 0;
    for(int i = 0; i < s.size(); ){
        if(s[i] >= '0' && s[i] <= '9') {
            ++i;
            num = 1;
        }
        else if(s[i] == '.'){
            if(dot != 0 || e != 0) return false;
            ++i;
            ++dot;
            if(s[i] == '\0') return false;
        }
        else if(s[i] == 'e' || s[i] == 'E'){
            if(num != 0 || e != 0) return false;
            ++i;
            ++e;
            if(s[i] == '+' || s[i] == '-') ++i;
            if(s[i] == '\0') return false;
        }
        else return false;
    }
    return true;
}

int main(){
    string s = "e9";
    cout << isNumber(s) << endl;
    return 0;
}
    
#endif

#if 0
// 顺时针打印矩阵
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> res;
        if(matrix.size() == 0 || matrix[0].size() == 0) return res;
        
        int top = 0, bottom = matrix.size()-1, left = 0, right = matrix[0].size()-1;
        while(bottom >= top && right >= left){
            // 向右
            for(int i = left; i <= right; ++i){
                res.push_back(matrix[top][i]);
            }
            // 向下
            for(int i = top+1; i <= bottom; ++i){
                res.push_back(matrix[i][right]);
            }
            // 向左
            for(int i = right-1; i >= left && bottom > top; --i){
                res.push_back(matrix[bottom][i]);
            }
            // 向上
            for(int i = bottom-1; i > top && left < right; --i){
                res.push_back(matrix[i][left]);
            }
            ++top, --bottom, ++left, --right;
        }
        return res;
    }
};

#endif

#if 0

/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    bool dfs(TreeNode* r1, TreeNode* r2){
        if(!r2) return true;
        if(!r1) return false;
        return r1->val==r2->val && dfs(r1->left,r2->left) && dfs(r1->right,r2->right);
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
        if(!pRoot1 || !pRoot2) return false;
        
        return dfs(pRoot1,pRoot2) || HasSubtree(pRoot1->left,pRoot2) || HasSubtree(pRoot1->right,pRoot2);
    }
};

#endif

#if 0
// 对称的二叉树
/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot){
        if(!pRoot) return true;
        return isSym(pRoot->left, pRoot->right);
    }
    bool isSym(TreeNode* A, TreeNode* B){
        if(!A && !B) return true;
        if(!A || !B) return false;
        if(A->val != B->val) return false;
        return isSym(A->left, B->right) && isSym(A->right, B->left);
    }
};
#endif
#if 0
// 从尾到头打印链表
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> v;
        if(!head) return v;
        while(head){
            int tmp = head->val;
            v.push_back(tmp);
            head = head->next;
        }
        reverse(v.begin(), v.end());
        return v;
    }
};

#endif

#if 0
// 镜像二叉树
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(!pRoot) return;
        if(!pRoot->left && !pRoot->right) return;
        //交换左右子树
        TreeNode* tmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tmp;
        //递归左右子树镜像
        if(pRoot->left) Mirror(pRoot->left);
        if(pRoot->right) Mirror(pRoot->right);
    }
};

#endif
#if 0
// 判断链表是否有环
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
//判断链表是否有循环（有返回1；没有返回0）
int SListHasCycle(SList* plist)
{
	SListNode *fast = plist->_head;
	SListNode *slow = plist->_head;

	while (slow && fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
		if (slow == fast){
			return 1;
		}
	}
	return 0;
}

// 得到链表中环的第一个节点
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead){
        if(!pHead) return nullptr;
        
        ListNode* fast = pHead;
        ListNode* low = pHead;
        while(fast && fast->next && fast->next->next){
            fast = fast->next->next;
            low = low->next;
            if(fast == low) break;
        }
        if(!fast || !fast->next || !fast->next->next) return nullptr;
        low = pHead;
        while(low != fast){
            low = low->next;
            fast = fast->next;
        }
        return low;
    }
};

#endif


#if 0
// 反转链表
ListNode* reverseList(ListNode* head) {
	if(head == NULL || head -> next == NULL) return head;
	
    ListNode* cur = NULL, *pre = head;
    while(pre != NULL){
        ListNode* t = pre->next;
        pre->next = cur;
        cur = pre;
        pre = t;
    }
    return cur;
}

ListNode* reverseList(ListNode* head) {
    if(head == NULL || head->next == NULL) return head;

    // 递归调用反转的每一个节点
    ListNode *node = reverseList(head->next);
    // 每一个节点是怎么反转的
    head->next->next = head;
    // 防止链表循环
    head->next = NULL;
    // 每层节点都返回node，也就是最后一个节点
    return node;
}

#endif

#if 0
// 合并两个排序的链表
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1 == nullptr) return pHead2;
        else if(pHead2 == nullptr) return pHead1;
        
        if(pHead1->val <= pHead2->val){
            pHead1->next = Merge(pHead1->next, pHead2);
            return pHead1;
        }
        else{
            pHead2->next = Merge(pHead1, pHead2->next);
            return pHead2;
        }
    }
};

class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        ListNode* tHead = new ListNode(1);
        ListNode* cur = tHead;
        while(pHead1 && pHead2){
            if(pHead1->val <= pHead2->val){
                cur->next = pHead1;
                pHead1 = pHead1->next;
            }
            else{
                cur->next = pHead2;
                pHead2 = pHead2->next;
            }
            cur = cur->next;
        }
        cur->next = pHead1 ? pHead1 : pHead2;
        return tHead->next;
    }
};

#endif

#if 0

// 树的子结构
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    bool dfs(TreeNode* r1, TreeNode* r2){
        if(!r2) return true;
        if(!r1) return false;
        return r1->val==r2->val && dfs(r1->left,r2->left) && dfs(r1->right,r2->right);
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
        if(!pRoot1 || !pRoot2) return false;
        
        return dfs(pRoot1,pRoot2) || HasSubtree(pRoot1->left,pRoot2) || HasSubtree(pRoot1->right,pRoot2);
    }
};

#endif

#if 0
// 链表中倒数第K个节点

/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(pListHead == nullptr || k == 0) return nullptr;
        
        ListNode* cur = pListHead;
        int i = k-1;
        while(cur->next != nullptr && i > 0){
            cur = cur->next;
            --i;
        }
        if(i > 0) return nullptr;
        
        ListNode* res = pListHead;
        while(cur->next != nullptr){
            cur = cur->next;
            res = res->next;
        }
        return res;
    }
};
#endif

#if 0
// [剑指Offer]21：调整数组顺序使奇数位于偶数前面

class Solution {
public:
    vector<int> exchange(vector<int>& array) {
        for(int i = 0, j = array.size()-1; i < j; ++i, --j){
            while(i < j && array[i]%2 == 1) ++i;
            while(i < j && array[j]%2 == 0) --j;
            if(i < j) swap(array[i], array[j]);
        }
        return array;
    }
};

class Solution {
public:
    void reOrderArray(vector<int> &array) {
        vector<int> res;
        vector<int> tmp;
        for(int i = 0; i < array.size(); ++i){
            if(array[i]%2 == 1) res.push_back(array[i]);
            else tmp.push_back(array[i]);
        }
        for(int i = 0; i < tmp.size(); ++i){
            res.push_back(tmp[i]);
        }
        array = res;
    }
};

#endif


#if 0
// [剑指Offer]20：表示数值的字符串

class Solution {
public:
    bool isNumeric(char* str)
    {
        if(str == nullptr) return false;
        
        if(*str == '+' || *str == '-') ++str;
        if(*str == '\0') return false;
        
        int dot = 0, e = 0;
        while(*str != '\0'){
            if(*str >= '0' && *str <= '9'){
                ++str;
            }
            else if(*str == '.'){
                if(dot != 0 || e != 0) return false;
                ++str;
                dot = 1;
            }
            else if(*str == 'e' || *str == 'E'){
                if(e != 0) return false;
                ++str;
                e = 1;
                if(*str == '+' || *str == '-') str++;
                if(*str == '\0') return false;
            }
            else return false;
        }
        return true;
    }
};

#endif

#if 0
int main() {
    int arr[] = {1,2,3,4,5,6,7,8};
    vector<int> s(arr, arr+8);
    
    for (auto i = s.begin(); i != s.end(); ++i) {
        cout << *i << " ";
        if (*i == 3) {
            i = s.insert(i, 30);
            ++i;
        }
        
    }
    for (auto i : s) cout << i << " ";

    return 0;
}
#endif


#if 0
class A{
    
public:
    int a;
};

class B : virtual public A{

public:
    int b;
};

int main(){
    B a;
    a.a = 1;
    a.b = 2;    
    cout << sizeof(B) << endl;

    return 0;
}
#endif
/*
#if 1
class A{
    
public:
    int a;
};

class B : public A{

public:
    int b;
};

class C : public A{

public:
    int c;
};

class D : public B, public C{

public:
    int d;
};

int main(){
    cout << sizeof(D) << endl;

    return 0;
}
#else
class A{
    
public:
    int a;
};

class B : virtual public A{

public:
    int b;
};

class C : virtual public A{

public:
    int c;
};

class D : public B, public C{

public:
    int d;
};

int main(){
    cout << sizeof(D) << endl;

    return 0;
}
#endif
*/

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
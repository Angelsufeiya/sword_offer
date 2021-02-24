#include <iostream>
#include <vector>
using namespace std;

// 删除排序数组中的重复项
/*
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        
        int res = 0;
        for(int i = 1; i < nums.size(); ++i){
            if(nums[res] != nums[i]){
                nums[++res] = nums[i];
            }
        }
        return res+1;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return distance(nums.begin(), unique(nums.begin(), nums.end()));
    }
};
*/
// 删除排序数组中的重复项II
/*
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() <= 2) return nums.size();
        int res = 2;
        for(int i = 2; i < nums.size(); ++i){
            if(nums[res-2] != nums[i]){
                nums[res++] = nums[i];
            }
        }
        return res;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int res = 0, sz = nums.size();
        for(int i = 0; i < sz; ++i){
            if(i > 0 && i < sz-1 && nums[i] == nums[i-1] && nums[i] == nums[i+1]) {
                continue;   
            }
            nums[res++] = nums[i];
        }
        return res;
    }
};
*/
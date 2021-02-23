#include <iostream>
#include <vector>
using namespace std;

// 删除排序数组中的重复项
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
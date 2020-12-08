// 剪绳子

// 动归
class Solution {
public:
    int cutRope(int num) {
        if(num <= 1) return 0;
        else if(num == 2) return 1;
        else if(num == 3) return 2;
        
        vector<int> v(num+1);
        for(int i = 0; i < 4; ++i) v[i] = i;
        for(int i = 4; i <= num; ++i){
            int max = 0;
            for(int j = 1; j <= i/2; ++j){
                int tmp = v[j]*v[i-j];
                if(tmp > max) max = tmp;
                v[i] = max;
            }
        }
        return v[num];
    }
};

// 贪婪
class Solution {
public:
    int cutRope(int num) {
        if(num <= 1) return 0;
        else if(num == 2) return 1;
        else if(num == 3) return 2;
        
        int x = num % 3, y = num / 3;
        if(x == 0) return pow(3, y);
        else if(x == 1) return pow(3, y-1)*2*2;
        else return pow(3, y) * x;
    }
};


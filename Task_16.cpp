// 数值的整数次方
class Solution {
public:
    double Power(double base, int exponent) {
        if(fabs(base - 0.0) < 1e-15){
            cout << "底数是0无意义" << endl;
            return 0.0;
        }
        double res = 1.0, flag = 1.0;
        if(exponent == 0) return res;
        else if(exponent < 0){
            flag = -1.0;
            exponent = fabs(exponent);
        }
        for(int i = 1; i <= exponent; ++i){
            res *= base;
        }
        return flag > 0 ? res : 1.0 / res;
    }
};

class Solution {
public:
    double Power(double base, int exponent) {
        if(fabs(base - 0.0) < 1e-15){
            cout << "底数是0无意义" << endl;
            return 0.0;
        }
        double res = 1.0, flag = 1.0;
        if(exponent == 0) return res;
        else if(exponent < 0){
            flag = -1.0;
            exponent = fabs(exponent);
        }
        // else if(exponent == 1) return base;
        // res *= Power(base, exponent>>1);
        // res *= res;
        // if(exponent & 0x1) res *= base;
        
        // 也可以用递归做，这里采用了循环
        while (exponent) {
            if (exponent & 0x1) res *= base;
            base *= base;
            exponent >>= 1;
        }
        return flag > 0 ? res : 1.0 / res;
    }
};
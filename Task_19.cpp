#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isMatch(char* str, char* pattern){
    if(str == NULL || pattern == NULL) return false;
    // 可能存在 *str == '\0' && *pattern != '\0' 这种情况
    if(*str == '\0' && *pattern == '\0') return true;
    if(*str != '\0' && *pattern == '\0') return false;

    if(*(pattern+1) == '*'){
        if(*pattern == *str || (*pattern == '.' && *str != '\0')){
            return isMatch(str+1, pattern) || isMatch(str, pattern+2);
        }
        else
            return isMatch(str, pattern+2);
    }
    if(*str == *pattern || *pattern == '.' && *str != '\0')
        return isMatch(str+1, pattern+1);

    return false;
}

bool isMatch(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    s1 = ' ' + s1, s2 = ' ' + s2;
    vector<vector<bool> > dp(n + 1, vector<bool>(m + 1));
    dp[0][0] = true;
	for (int i = 0; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (j + 1 <= m && s2[j + 1] == '*') continue;
			if (i && s2[j] != '*') 
				dp[i][j] = dp[i - 1][j - 1] && (s1[i] == s2[j] || s2[j] == '.');
			else if (s2[j] == '*')
				dp[i][j] = dp[i][j - 2] || i && dp[i - 1][j] && (s1[i] == s2[j - 1] || s2[j - 1] == '.');
		}
	}
	return dp[n][m];
}

int main(){
	string s1, s2;
	s1 = "aa";
	s2 = "a*";
	if(isMatch(s1, s2)){
		cout << "字符串匹配" << endl;
	}
	else{
		cout << "字符串不匹配" << endl;
	}
	return 0;
}
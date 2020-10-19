#include <iostream>
#include <string>
using namespace std;

char* replaceSpace_1(char* s){
    if(*s == '\0') return s;
    char *res = (char *)malloc(strlen(s)*3+1);
    int i = 0;

    while(*s != '\0'){
        if(*s == ' '){
            res[i++] = '%';
            res[i++] = '2';
            res[i++] = '0';
        }else{
            res[i++] = *s;
        }
        s++;
    }
    res[i] = '\0';
    return res;
}

string replaceSpace(string s) {
    int count = 0, len = s.size();
    // 统计空格数量
    for (char c : s) {
        if (c == ' ') count++;
    }
    // 修改 s 长度
    s.resize(len + 2 * count);
    // 倒序遍历修改
    for(int i = len - 1, j = s.size() - 1; i < j; i--, j--) {
        if (s[i] != ' ')
            s[j] = s[i];
        else {
            s[j--] = '0';
            s[j--] = '2';
            s[j] = '%';
        }
    }
    return s;
}

void replaceSpace(char *str,int length) {
    if(str == NULL ||length<=0) return;
    int sz = 0, count = 0;
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i] == ' ') count++;
        sz++;
    }
    int new_sz = sz+count*2;
    int i = sz;
    int j = new_sz;
    while(sz>=0 && j>i)
    {
        if(str[i] == ' ')
        {
            str[j--] = '0';
            str[j--] = '2';
            str[j--] = '%';
        }
        else 
            str[j--] = str[i];
        i--;
    }
}
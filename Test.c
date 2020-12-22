#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int BF(char S[],char T[])
{
	int i=0,j=0;
	while(S[i] != '\0' && T[j] != '\0')
	{
		if(S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			i=i-j+1;
			j=0;
		}
	}
	if (T[j]=='\0') return (i-j);     //主串中存在该模式返回下标号 
	else return -1;     //主串中不存在该模式 
}

void Getnext(int next[],char * t)
{
    int j = 0, k = -1;
    next[0] = -1;
    while(t[j] != '\0')
    {
        if(k == -1 || t[j] == t[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else k = next[k];
    }
}

int main(){
    char a[] = "abcdefg";
    char b[] = "ce";
    int next[10] = {0};
    char t[] = "abaabca";
    Getnext(next, t);
    for(int i = 0; i < 6; i++) printf("%d ", next[i]);
    printf("%d", BF(a, b));
    return 0;
}

#if 0
char* my_strcat(char *dst, const char *src){
	assert(dst && src);

	char *ret = dst;
	//将指向dst的指针移到字符串末尾,指向'\0'
	while (*dst++);
	dst--;
	//如果剩余要复制的元素个数为0或者到达了src字符串的末尾,则复制终止
	while ((*dst++ = *src++));
	return ret;
}

char* my_strncat(char *dst, const char *src, size_t num){
	assert(dst && src);

	char *ret = dst;
	
	//将指向dst的指针移到字符串末尾,指向'\0'
	while (*dst++);
	dst--;
	//如果剩余要复制的元素个数为0或者到达了src字符串的末尾,则复制终止
	while (num-- && (*dst++ = *src++));
	if(num == 0) *dst = 0;//复制完毕后,将最后一个元素置为'\0'
	return ret;
}

int main(){
	const char str1[10] = "0123456789";
	char str2[50] = "abcdefghijklmnopqrs";
	size_t count = 12;

	printf("调用 my_strncat前，str2 = %s\n", str2);
	my_strcat(str2, str1);
	printf("调用 my_strncat后，str2 = %s\n", str2);

	return 0;
}
#endif
#if 0
int my_strncmp(const char *str1, const char *str2, size_t num){
    assert(str1 && str2);
    
    int ret = 0;
    if(num == 0) return ret;

    while (!(ret = *(unsigned char *)str1 - *(unsigned char *)str2) && *str1 && *str2 && --num){
        str1++, str2++;
    }
    if (ret > 0) ret = 1;
    else if(ret < 0) ret = -1;

    return ret;
}

int my_strcmp (const char * str1, const char * str2 ){
    assert(str1 && str2);

    int ret = 0;
    while(!(ret = *(unsigned char *)str1 - *(unsigned char *)str2 && *str1 && *str2)){
        ++str1, ++str2;
    }
    if (ret > 0) ret = 1;
    else if(ret < 0) ret = -1;

    return ret;
}

int main(){
	const char str1[10] = "abcdabcd";
	const char str2[20] = "bbcdbdbcdabcdb";
	size_t count = 5;

	printf("调用 my_strncmp后，比较得 = %d\n", my_strncmp(str1, str2, 1));
	return 0;
}
#endif

#if 0
char * my_strstr(const char * str1, const char * str2){
    assert(str1 && str2);

    char * cp = (char *)str1;
    char * s1;
    char * s2;

    if(*str2 == '\0') return NULL;
    while(*cp){
        s1 = cp;
        s2 = (char *)str2;
        while(*s1 && *s2 && *s1 == *s2){
            s1++;
            s2++;
        }
        if(*s2 == '\0') return cp;
        cp++;
    }
    return NULL;
}

int main(){
	char arr1[] = "abcbcdef";
	char arr2[10] = "";

	printf("%s\n", my_strstr(arr1, arr2));
	return 0;
}
#endif
#if 0
char * my_strcpy_1(char * dst, const char * src){
    assert(src);
    assert(dst);    // 这个是判断dst是不是空，如果是空则没有存储src的空间。

    char * ret = dst;
    while ((*dst++ = *src++));
    //while(*src != '\0'){
    //    *dst++ = *src++;
    //}
    return ret;
}

char * my_strcpy(char * dst, const char * src){
    //if(*dst == NULL || *src == NULL) return NULL;
    assert(src && dst);

    char * ret = dst;
    int len = strlen(src);
    int i = len;
    
    //源地址和目的地址重叠，高字节向低字节拷贝
    if(dst > src && dst < src+len){
        dst = dst+len-1;
        src = src+len-1;
        while(len--){
            *dst = *src;
            dst--;
            src--;
        }
    }
    else{
        while(len--){
            *dst = *src;
            dst++;
            src++;
        }
    }
    return ret;
}

char* my_strncpy(char *dest, const char *src, size_t size){
	// 检查dest,src是否为空指针
	assert(dest && src);

	char *ret = dest;	// 记录dest指针的首地址（用于返回）
	
	// size的数据类型为size_t（unsigned int)
	// size-- 不能直接写在while中，会影响 if 的判断
	while (size && (*dest++ = *src++) != '\0'){
		size--;
	}
	if (size){
		//dest多被赋值一次'\0'，所以 -- 在 size前面
		while (--size){
			*dest++ = '\0';
		}
	}
	return ret;
}

int main(){
	const char str1[20] = "0123456789876543210";
	char str2[20] = "abcdefg";

	printf("调用 my_strcpy前，str2 = %s\n", str2);
	my_strncpy(str2+2, str2, 10);
	printf("调用 my_strcpy后，str2 = %s\n", str2);
	return 0;
}
#endif
#if 0
// 模拟实现strlen
size_t my_strlen(const char * str){
    assert(str);
    int count = 0;
    while(*str++) 
        ++count;
    return count;
}

size_t my_strlen_1(const char * str){
    if(*str == '\0') return 0;
    else return 1+my_strlen_1(++str);
}

size_t my_strlen_2(const char * str){
    const char * p = str;
    while(*p){
        p++;
    }
    return p - str;
}

int main(){
    char *arr = NULL;
	size_t ret = my_strlen(arr);
	printf("%zu\n", ret);   // %zu用来输出size_t类型
    return 0;
}
#endif
#if 0
int main () {
    char str[] ="This is a simple string";
    char * pch;
    pch = strstr (str,"simple");
    strncpy (pch,"sample",6);
    puts (str);
    return 0; 
}
#endif
#if 0
int main() {
    int i = 0;
    int j = 0;
    int k = 1;
    /*
考点:
1. 参数是从右往左传递的
2. 前置++编译器的处理方式为:先计算++的值，然后存回到变量，最后从变量中取出值传递给函数
3. 后置++编译器的处理方式为:先将变量的值保存到临时变量，然后计算++的值存回到变量
4. 优先级:后置++ > 符号 > 前置++
    */
    printf("%d, %d, %d\n", ++i, ++i, ++i);
    printf("%d, %d, %d\n", j++, j++, j++);
    printf("%d, %d, %d\n", k++, -++k, -k++);
    return 0; 
}
//程序输出的结果是什么?
#endif
#if 0
enum Color{//颜色 {
    RED=1,
    GREEN=2,
    BLUE=4
};
int main(){
    enum Color clr;
    clr = GREEN;//只能拿枚举常量给枚举变量赋值，才不会出现类型的差异。 
    printf("%d\n", clr);
    clr = (BLUE);
    printf("%d\n", clr);
    return 0;
}
#endif
#if 0
int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; ++i){
        printf("%p, %d\n", &arr[i], arr[i]);
    }
    return 0;
}
#endif
#if 0
int main(){
    int a[2000];
    char *p = (char*)a;
    for( int i = 0; i < 2000; i++){
        a[i] = -1 - i;
    }
    printf("%d\n", strlen(p));  // 1020 小端；大端的话是1023
    return 0;
}
#endif
#if 0
int main(){
    int a1= 5,  b2 = 10,c2 = 15,d2 = 20;
    printf("a1......%p\n",&a1);
    printf("b2......%p\n",&b2);
    printf("c2......%p\n",&c2);
    printf("d2......%p\n",&d2);
    int * p3 = &b2;
    printf("p3......%d\n",*p3);//输出 本身指向的值
    printf("p3......%d\n",*(p3+1));//指向 a1
    printf("p3......%d\n",*(p3-1));//指向 c2
    return 0;
}
#endif

#if 0
// 测试计算机大小端和CPU相关

union A{
    char c;
    int i;
}s;

int main(){
    s.i = 0x12345678;
    if(s.c == 0x78)
        printf("小端:Little\n");
    else
        printf("大端:Big\n");
    return 0;
}

int main_1(){
    int i = 0x12345678;
    char c = *(char *)&i;
    if(c == 0x78) 
        printf("小端:Little\n");
    else 
        printf("大端:Big\n");
    return 0;
}

int main_2(){
    int i = 0x12345678;
    char c = i; // 直接强制转换，不论CPU是大端还是小端，都是0x78
    // 当(int)char 时，赋予int型在32位的最后八位的二进制数
    if(c == 0x78) 
        printf("小端:Little\n");
    else 
        printf("大端:Big\n");
    return 0;
}
#endif

#if 0
void test(){
    printf("%d", 1);
}

typedef void(*p)(int a, int b);

struct A{
    char c;
    double d;
    p a;
};

int main(){
    printf("%d\n", (int)sizeof(struct A));

    return 0;
}
#endif
#if 0
int main() {
       int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
       int *ptr1 = (int *)(&aa + 1);
       int *ptr2 = (int *)(*(aa + 1));
       printf( "%d,%d", *(ptr1 - 1), *(ptr2 - 1));
       return 0;
}
#endif

#if 0
int main() {
    int arr[10] = {0};
    printf("arr = %p\n", arr);
    printf("&arr= %p\n", &arr);
    printf("arr+1 = %p\n", arr+1);
    printf("&arr+1= %p\n", &arr+1);
    return 0;
}
#endif
#if 0
int main(){
    float values[5];
    float *vp;
    //指针+-整数;指针的关系运算
    
    for (vp = &values[0]; vp < &values[5];) {
        *vp++ = 0;     
    }
    return 0;
}
#endif

#if 0
int main() {
    int arr[10] = {1,2,3,4,5};
    int* p = arr; 
    while(p<=&arr[9])//指针比较大小 
    {
        printf("%d ", *p);
        p++;    
    }
    return 0; 
}
#endif
#if 0
int main(){
    int a[5][5];
    int (*p)[4];
    p = a;
    printf("%p, %d", &p[4][2] - &a[4][2],  &p[4][2] - &a[4][2]);
    return 0;
}
#endif
#if 0
int main(){
    printf("%s,%5.3s\n", "computer", "computer");
    return 0;
}
#endif
#if 0
typedef struct ListNode{
    int m_value;
    struct ListNode * m_next;
}ListNode;

//void PrintListReversing(ListNode* Head){
    // 从尾到头打印链表
//}

void Insert(ListNode * head, int val){
    ListNode * temp = (ListNode *)malloc(sizeof(ListNode));
    temp->m_value = val;
#if 1
    // 头插
    temp->m_next = head->m_next;
    head->m_next = temp;
#else
    // 尾插
    ListNode * p = head;
    while(p->m_next != NULL){
        p = p->m_next;
    }
    p->m_next = temp;
    temp->m_next = NULL;
#endif
}

void Print(ListNode * head){
    ListNode * temp = head->m_next;
    while(temp){
        printf("%d->", temp->m_value);
        temp = temp->m_next;
    }
    printf("NULL\n");
}

void Free(ListNode * head){
    ListNode * p = head;
    ListNode * temp;
    while(p){
        temp = p->m_next;
        free(temp);
        p = temp;
    }
}

ListNode *init(){
    ListNode * temp = (ListNode *)malloc(sizeof(ListNode));
    temp->m_next = NULL;
    return temp;
}

int main(){
    ListNode * Head = init();
    for(int i = 1; i < 10; ++i){
        Insert(Head, i);
    }
    Print(Head);
    Free(Head);
    return 0;
}
#endif
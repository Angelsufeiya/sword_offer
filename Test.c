#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
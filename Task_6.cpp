#include <iostream>
#include <stack>
using namespace std;

typedef struct ListNode{
    int m_value;
    struct ListNode * m_next;
}ListNode;

// 从尾到头打印链表
void PrintListReversing_1(ListNode* Head){
    stack<ListNode *> s;
    ListNode * pnode = Head;
    while(pnode != NULL){
        s.push(pnode);
        pnode = pnode->m_next;
    }
    while(!s.empty()){
        pnode = s.top();
        s.pop();
        cout << pnode->m_value << "->";
    }
    cout << "NULL" << endl;
}

void PrintListReversing(ListNode* Head){
    if(Head){
        if(Head->m_next != NULL){
            PrintListReversing(Head->m_next);
        }
        cout << Head->m_value << "->";
    }
}

void Insert(ListNode * head, int val){
    ListNode * temp = new ListNode;
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
        cout << temp->m_value << "->";
        temp = temp->m_next;
    }
    cout << "NULL" << endl;
}

void Free(ListNode * head){
    ListNode * p = head;
    ListNode * temp;
    while(p){
        temp = p->m_next;
        delete temp;
        p = temp;
    }
}

ListNode *init(){
    ListNode * temp = new ListNode;
    temp->m_next = NULL;
    return temp;
}

int main(){
    ListNode * Head = init();
    for(int i = 1; i < 10; ++i){
        Insert(Head, i);
    }
    Print(Head);
    PrintListReversing(Head->m_next);
    cout << "NULL" << endl;
    PrintListReversing_1(Head->m_next);
    Free(Head);
    return 0;
}
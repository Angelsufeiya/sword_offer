#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
struct ListNode{
    int m_value;
    ListNode* m_pnext;
};

// 基于一个假设：要删除的节点在链表中
void DeleteNode(ListNode ** pListHead, ListNode * pToBeDeleted){
    if(!pListHead || !pToBeDeleted) return;
    
    // 要删除的节点不是尾节点
    if(pToBeDeleted->m_pnext != nullptr){
        ListNode * pNext = pToBeDeleted->m_pnext;
        pToBeDeleted->m_value = pNext->m_value;
        pToBeDeleted->m_pnext = pNext->m_pnext;

        delete pNext;
        pNext = nullptr;
    }
    // 链表只有一个节点
    else if(*pListHead == pToBeDeleted){
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        *pListHead = nullptr;
    }
    // 链表中有多个节点，删除尾节点
    else{
        ListNode * pNext = *pListHead;
        while(pNext->m_pnext != pToBeDeleted){
            pNext = pNext->m_pnext;
        }

        // pNext->m_pnext = nullptr;
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}
*/

struct ListNode{
    int val;
    ListNode* next;
};

ListNode* deleteDuplication(ListNode* pHead)
{
    if(pHead == nullptr || pHead->next == nullptr) return pHead;
    ListNode * head = new ListNode;    // 新建一个节点，防止头结点要被删除
    head->next = pHead;
    ListNode * pre = head, * cur = pHead;
        
    while(cur){
        if(cur->next && cur->val == cur->next->val){
            cur = cur->next;
            while(cur->next && cur->val == cur->next->val) cur = cur->next;
            cur = cur->next;
            pre->next = cur;
        }
        else{
            pre = cur;
            cur = cur->next;
        }
    }
    return head->next;
}

int main(){
    ListNode * p1 = new ListNode;
    p1->val = 1;

    ListNode * p2 = new ListNode;
    p2->val = 1;
    p1->next = p2;

    ListNode * p3 = new ListNode;
    p3->val = 1;
    p2->next = p3;

    ListNode * p4 = new ListNode;
    p4->val = 2;
    p3->next = p4;

    ListNode * p5 = new ListNode;
    p5->val = 3;
    p4->next = p5;

    ListNode * p6 = new ListNode;
    p6->val = 3;
    p5->next = p6;

    ListNode * cur = deleteDuplication(p1);
    while(cur){
        cout << cur->val << ' ';
        cur = cur->next;
    }
    return 0;
}
#include <iostream>
using namespace std;

typedef struct BinaryTreeNode{
    int m_value;
    struct BinaryTreeNode * m_left;
    struct BinaryTreeNode * m_right;
}BinaryTreeNode;

struct ListNode{
    int m_value;
    ListNode * m_next;
};

int main(){
    ListNode * node;
    node->m_next = NULL;
    node->m_value = 1;
    cout << node->m_value;
    return 0;
}
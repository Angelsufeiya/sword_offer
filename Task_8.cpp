#include <iostream>
using namespace std;

struct BinaryTreeNode{
    int m_value;
    BinaryTreeNode * m_left;
    BinaryTreeNode * m_right;
    BinaryTreeNode * m_parent;
};

BinaryTreeNode* GetNext(BinaryTreeNode* pNode){
    if(pNode == nullptr) return nullptr;

    BinaryTreeNode* pNext = nullptr;
    if(pNode->m_right != nullptr){
        BinaryTreeNode* pRight = pNode->m_right;
        while(pRight->m_left != nullptr) pRight = pRight->m_left;

        pNext = pRight;
    }
    else if(pNode->m_parent != nullptr){
        BinaryTreeNode* pCurrent = pNode;
        BinaryTreeNode* pParent = pNode->m_parent;
        while(pParent != nullptr && pCurrent == pParent->m_right){
            pCurrent = pParent;
            pParent = pParent->m_parent;
        }
        pNext = pParent;
    }
    return pNext;
}
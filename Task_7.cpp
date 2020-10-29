#include <iostream>
#include <queue>
using namespace std;

struct BinaryTreeNode{
    int m_value;
    BinaryTreeNode * m_left;
    BinaryTreeNode * m_right;
};

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder){
    BinaryTreeNode* root = new BinaryTreeNode();
    int rootValue = startPreorder[0];
    root->m_value = rootValue;
    root->m_right = root->m_left = NULL;

    if(startPreorder == endPreorder){
        if(startInorder == endInorder && *startPreorder == *startInorder) return root;
        else {
            try{
                throw std::exception();
            }
            catch(...){
                cout << "Invalid input." << endl;
            }
        }
    }
    else{
        int* rootInorder = startInorder;
        while(rootInorder < endInorder && *rootInorder != rootValue) ++rootInorder;

        if(rootInorder == endInorder && *rootInorder != rootValue) {
            try{
                throw std::exception();
            }
            catch(...){
                cout << "Invalid input." << endl;
            }
        }
        int leftLength = rootInorder - startInorder;
        int* leftPreorderEnd = startPreorder + leftLength;
        if(leftLength > 0){
            // 构建左子树
            root->m_left = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder-1);
        }
        if(leftLength < endPreorder - startPreorder){
            // 构建右子树
            root->m_right = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder+1, endInorder);
        }
    }
    return root;
}

BinaryTreeNode* Construct(int* preorder, int* inorder, int length){
    if(preorder == nullptr || inorder == nullptr || length <= 0) return nullptr;
    return ConstructCore(preorder, preorder+length-1, inorder, inorder+length-1);
}

// 层序遍历
void BinaryTreeLevelOrder(BinaryTreeNode * root){
    queue<BinaryTreeNode*> qu;
    qu.push(root);
    BinaryTreeNode* cur;

    while(!qu.empty()){
        cur = qu.front();
        cout << cur->m_value << ' ';
        if(cur->m_left) qu.push(cur->m_left);
        if(cur->m_right) qu.push(cur->m_right);
        qu.pop();
    }
}

int main(){
    /*
    int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};  // 前序遍历
    int inorder[] = {4, 7, 2, 1, 5, 3, 8, 6};   // 中序遍历
    BinaryTreeNode * root = Construct(preorder, inorder, 8);*/
    int preorder[] = {1, 2, 3, 4, 5};
    int inorder[] = {1, 2, 3, 4, 5};
    BinaryTreeNode * root = Construct(preorder, inorder, 5);

    BinaryTreeLevelOrder(root);
    return 0;
}
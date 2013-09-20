#ifndef BT_IMPL_H
#include "BinaryTree.h"
#include <vector>
#include <iostream>
using namespace std;

//二叉树的构造
BTNode * createBTreeFromStdin();//从标准输入输出构造一棵树
BTNode *createBTreeFromInorderAndPostorder_impl(vector<int>&inorder,vector<int>&postorder,int len,int inStart, int postStart);
BTNode *createBTreeFromInorderAndPostorder(vector<int>&inorder,vector<int>&postorder);
bool isValidInorderAndPostorder(vector<int>&inorder,vector<int>&postorder);
bool isValidInorderAndPostorder_impl(vector<int>&inorder,vector<int>&postorder,int len,int inStart,int postStart);


//二叉树的显示或者遍历
void showBTree(BTNode *root,TRAVERSAL_ORDER order=INORDER);
void showBTree_nr(BTNode *root,TRAVERSAL_ORDER order=INORDER);
void inorderTraversal(BTNode * root);
void preorderTraversal(BTNode *root);
void postorderTraversal(BTNode *root);
void inorderTraversal_nr(BTNode *root);
void preorderTraversal_nr(BTNode *root);
void postorderTraversal_nr(BTNode *root);

//二叉树的删除
void _destroy(BTNode *root);
void destroyBTree(BTNode **pRoot);


#endif
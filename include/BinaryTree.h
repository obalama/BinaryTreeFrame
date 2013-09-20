#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <cstdio>
#include <cstdlib>
enum TRAVERSAL_ORDER{PREORDER,INORDER,POSTORDER};
typedef struct BTNode 
{
	struct BTNode *left;
	struct BTNode *right;
	int val;
	BTNode(int v):left(NULL),right(NULL),val(v){}
}BTNode;
#endif
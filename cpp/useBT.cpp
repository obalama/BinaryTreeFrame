#include <iostream>
#include "../include/BinaryTree.h"
#include "../include/BT_impl.h"
#include "../include/ultility_vector.h"
#include <vector>

//extern void showBTree(BTNode *root,TRAVERSAL_ORDER order=INORDER);
using namespace std;

int main()
{
	vector<int> inorder=getVectorFormStdin(7);
	vector<int> postorder=getVectorFormStdin(7);
	BTNode *root=createBTreeFromInorderAndPostorder(inorder,postorder);
	//showBTree(root);
	showBTree(root,	PREORDER);
	showBTree(root,	INORDER);
	showBTree(root,	POSTORDER);

	inorderTraversal_nr(root);
	preorderTraversal_nr(root);
	postorderTraversal_nr(root);
	destroyBTree(&root);
	showBTree(root);
	system("pause");

}
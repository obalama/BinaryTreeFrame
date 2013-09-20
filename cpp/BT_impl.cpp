#include "../include/BT_impl.h"

/*
	part1:二叉树的创建
*/

BTNode *createBTreeFromInorderAndPostorder_impl(vector<int>&inorder,vector<int>&postorder,int len,int inStart,int postStart)
{
	/*函数类别：创建二叉树--已知中序和后序

		给定两个同样长度的数组区间（分别表示中序和后序），构造一棵树（实际实现）
		不进行有效性检测，也就是说输入的区间必须真的可以构造出一颗有效的树
		接口稍微麻烦一些:
			inorder：存放中序遍历结果的数组
			postorder:存放后序遍历结果的数组
			len：当前要处理子树的长度
			inStart:当前要处理的子树先序遍历结果在整棵树中序遍历结果数组中的起始位置
			postStart：当前要处理的子树后序遍历结果在整棵树后序遍历结果数组中的其实位置
	*/
	if(0==len)return NULL;
	
	int rootVal=postorder[postStart+len-1];
	int rootIndex=0;//当前树的根在中序遍历中的位置
	
	for(int i=inStart;i<inStart+len;++i)
	{
		if(inorder[i]==rootVal){rootIndex=i;break;}
	}

	BTNode *root=(BTNode *)malloc(sizeof(BTNode));
	if(root!=NULL)
	{
		root->val=rootVal;
		root->left=createBTreeFromInorderAndPostorder_impl(inorder,postorder,rootIndex-inStart,inStart,postStart);
		root->right=createBTreeFromInorderAndPostorder_impl(inorder,postorder,inStart+len-1-rootIndex,
															    rootIndex+1,postStart+rootIndex-inStart);
	}

	return root;
}



BTNode *createBTreeFromInorderAndPostorder(vector<int>&inorder,vector<int>&postorder)
{
	/*函数类别：创建二叉树--已知中序和后序

		假设不存在重复节点
		简洁的接口，但是需要进行有效性检测：
			inorder:整棵树的中序遍历结果
			postorder:整棵子树的后序遍历结果
	*/
	if(!isValidInorderAndPostorder(inorder,postorder)){cout<<"NOT a valid inorder and postorder sequeues"<<endl;return NULL;}
	return createBTreeFromInorderAndPostorder_impl(inorder,postorder,inorder.size(),0,0);
}

bool isValidInorderAndPostorder(vector<int>&inorder,vector<int>&postorder)
{
	if(inorder.size()!=postorder.size()||inorder.size()==0)return false;
	
	return isValidInorderAndPostorder_impl(inorder,postorder,inorder.size(),0,0);
}

bool isValidInorderAndPostorder_impl(vector<int>&inorder,vector<int>&postorder,int len,int inStart,int postStart)
{
	if(0==len)return true;

	int rootVal=postorder[postStart+len-1];
	int rootIndex=-1;
	for(int i=inStart;i<inStart+len;++i)
	{
		if(inorder[i]==rootVal)
		{
			rootIndex=i;break;
		}
	}

	if(rootIndex!=-1)
		return isValidInorderAndPostorder_impl(inorder,postorder,rootIndex-inStart,inStart,postStart)&&
			   isValidInorderAndPostorder_impl(inorder,postorder,rootIndex-inStart,rootIndex+1,postStart+rootIndex-inStart);

	else return false;
}


/* part2:

	二叉树的遍历
	
*/

void inorderTraversal(BTNode *root)
{
	if(root==NULL)return;
	else
	{
		inorderTraversal(root->left);
		cout<<root->val<<" ";
		inorderTraversal(root->right);
	}
}

void preorderTraversal(BTNode *root)
{
	if(root==NULL)return;
	else
	{
		cout<<root->val<<" ";
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

void postorderTraversal(BTNode *root)
{
	if(root==NULL)return ;
	else
	{
		postorderTraversal(root->left);
		postorderTraversal(root->right);
		cout<<root->val<<" ";
	}
}


void inorderTraversal_nr(BTNode *root)
{
	/*二叉树的非递归中序遍历*/
	if(root==NULL)return ;
	vector<BTNode *>myStack;
	BTNode *cur=root;
	myStack.push_back(cur);
	while(!myStack.empty())
	{
		while(cur->left!=NULL)
		{
			cur=cur->left;myStack.push_back(cur);
		}
		if(!myStack.empty())
		{
			cur=myStack.back();
			myStack.pop_back();
			cout<<cur->val<<" ";
			if(cur->right!=NULL)
			{
				myStack.push_back(cur->right);cur=cur->right;
			}
		}

	}
	cout<<endl;

}

void preorderTraversal_nr(BTNode *root)
{
		/*先序遍历的非递归实现
			需注意，入栈的时候先压入右儿子，这样出栈才会先访问右儿子
		*/
	if(root==NULL)return;
	vector<BTNode *>myStack;
	BTNode *cur=root;
	myStack.push_back(cur);

	while(!myStack.empty())
	{
		cur=myStack.back();
		cout<<cur->val<<" ";
		myStack.pop_back();
		if(cur->right!=NULL)myStack.push_back(cur->right);
		if(cur->left!=NULL)myStack.push_back(cur->left);
	}
	cout<<endl;
}


void postorderTraversal_nr(BTNode *root)
{
	/*后序遍历的非递归实现:
		后序遍历的结果相对比较复杂一点，因为父亲结点最后输出，如果发现退栈时父亲节点之前被访问过，那么说明它的
		右子树已经被访问遍历完成。
		要实现这个记录功能，要么在节点的数据结构中加入一个visit的label，要么就单独设置一个和myStack大小同时变化的visit栈来
		保存访问信息，注意，压栈的时候不算访问。
	*/
	if(root==NULL)return;
	vector<BTNode *>myStack;
	vector<bool>visitStack;
	BTNode *cur=root;
	myStack.push_back(cur);
	visitStack.push_back(false);
	while(!myStack.empty())
	{
		cur=myStack.back();
		while(cur->left!=NULL)//一直压栈直至到达最左节点
		{
			myStack.push_back(cur->left);
			visitStack.push_back(false);
			cur=cur->left;
		}
		
		
		//栈不为空则则可以去除上一个被压栈的节点，也就是最左节点的父亲节点
		while(!myStack.empty())
		{
			cur=myStack.back();//获得父亲节点
			bool isVisited=visitStack.back();
			if(cur->right!=NULL&&!isVisited)
			{
				//如果父亲节点之前没被访问且父亲节点的右儿子不为空，则需继续压栈，直至最左节点，因此需要break出本层循环
				visitStack[visitStack.size()-1]=true;
				myStack.push_back(cur->right);
				visitStack.push_back(false);
				break;
			}
			else
			{
				//如果父亲节点的右儿子为空或者父亲节点已经被访问过一次，则输出次父亲节点，并将此节点出栈
				cout<<cur->val<<" ";
				myStack.pop_back();
				visitStack.pop_back();
			}
		}
	}

	cout<<endl;
}
void showBTree(BTNode *root,TRAVERSAL_ORDER order)
{
	if(root==NULL){cout<<"The tree is empty!!"<<endl;return;}

	switch(order)
	{
		case INORDER:
			cout<<"中序遍历：";inorderTraversal(root);break;
		case PREORDER:
			cout<<"先序遍历：";preorderTraversal(root);break;
		case POSTORDER:
			cout<<"后序遍历：";postorderTraversal(root);break;
		default:break;
	};

	cout<<endl;
}

void showBTree_nr(BTNode *root,TRAVERSAL_ORDER order)
{
	if(root==NULL){cout<<"The tree is empty!!"<<endl;return;}

	switch(order)
	{
		case INORDER:
			cout<<"中序遍历：";inorderTraversal_nr(root);break;
		case PREORDER:
			cout<<"先序遍历：";preorderTraversal_nr(root);break;
		case POSTORDER:
			cout<<"后序遍历：";postorderTraversal_nr(root);break;
		default:break;
	};

	cout<<endl;
}


/*

	part3:二叉树的销毁

*/
void destroyBTree(BTNode **pRoot)
{
	_destroy(*pRoot);
	*pRoot=NULL;
}
void _destroy(BTNode *root)
{
	if(root==NULL)return ;
	_destroy(root->left);
	_destroy(root->right);
	free(root);
}


/**/
#include "../include/BT_impl.h"

/*
	part1:�������Ĵ���
*/

BTNode *createBTreeFromInorderAndPostorder_impl(vector<int>&inorder,vector<int>&postorder,int len,int inStart,int postStart)
{
	/*������𣺴���������--��֪����ͺ���

		��������ͬ�����ȵ��������䣨�ֱ��ʾ����ͺ��򣩣�����һ������ʵ��ʵ�֣�
		��������Ч�Լ�⣬Ҳ����˵��������������Ŀ��Թ����һ����Ч����
		�ӿ���΢�鷳һЩ:
			inorder���������������������
			postorder:��ź���������������
			len����ǰҪ���������ĳ���
			inStart:��ǰҪ������������������������������������������е���ʼλ��
			postStart����ǰҪ������������������������������������������е���ʵλ��
	*/
	if(0==len)return NULL;
	
	int rootVal=postorder[postStart+len-1];
	int rootIndex=0;//��ǰ���ĸ�����������е�λ��
	
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
	/*������𣺴���������--��֪����ͺ���

		���費�����ظ��ڵ�
		���Ľӿڣ�������Ҫ������Ч�Լ�⣺
			inorder:������������������
			postorder:���������ĺ���������
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

	�������ı���
	
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
	/*�������ķǵݹ��������*/
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
		/*��������ķǵݹ�ʵ��
			��ע�⣬��ջ��ʱ����ѹ���Ҷ��ӣ�������ջ�Ż��ȷ����Ҷ���
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
	/*��������ķǵݹ�ʵ��:
		��������Ľ����ԱȽϸ���һ�㣬��Ϊ���׽�������������������ջʱ���׽ڵ�֮ǰ�����ʹ�����ô˵������
		�������Ѿ������ʱ�����ɡ�
		Ҫʵ�������¼���ܣ�Ҫô�ڽڵ�����ݽṹ�м���һ��visit��label��Ҫô�͵�������һ����myStack��Сͬʱ�仯��visitջ��
		���������Ϣ��ע�⣬ѹջ��ʱ������ʡ�
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
		while(cur->left!=NULL)//һֱѹջֱ����������ڵ�
		{
			myStack.push_back(cur->left);
			visitStack.push_back(false);
			cur=cur->left;
		}
		
		
		//ջ��Ϊ���������ȥ����һ����ѹջ�Ľڵ㣬Ҳ��������ڵ�ĸ��׽ڵ�
		while(!myStack.empty())
		{
			cur=myStack.back();//��ø��׽ڵ�
			bool isVisited=visitStack.back();
			if(cur->right!=NULL&&!isVisited)
			{
				//������׽ڵ�֮ǰû�������Ҹ��׽ڵ���Ҷ��Ӳ�Ϊ�գ��������ѹջ��ֱ������ڵ㣬�����Ҫbreak������ѭ��
				visitStack[visitStack.size()-1]=true;
				myStack.push_back(cur->right);
				visitStack.push_back(false);
				break;
			}
			else
			{
				//������׽ڵ���Ҷ���Ϊ�ջ��߸��׽ڵ��Ѿ������ʹ�һ�Σ�������θ��׽ڵ㣬�����˽ڵ��ջ
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
			cout<<"���������";inorderTraversal(root);break;
		case PREORDER:
			cout<<"���������";preorderTraversal(root);break;
		case POSTORDER:
			cout<<"���������";postorderTraversal(root);break;
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
			cout<<"���������";inorderTraversal_nr(root);break;
		case PREORDER:
			cout<<"���������";preorderTraversal_nr(root);break;
		case POSTORDER:
			cout<<"���������";postorderTraversal_nr(root);break;
		default:break;
	};

	cout<<endl;
}


/*

	part3:������������

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
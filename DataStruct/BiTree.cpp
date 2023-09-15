/*							二叉树的基本概念
*	特点：1、每个节点至多只有两颗子树；2、左右子树不能颠倒（二叉树是有序树）
*	
*	满二叉树：只有最后一层有叶子结点、不存在度为1的结点、从1开始编号，结点i的左孩子为2i,右孩子为2i+1;
*	完全二叉树：每个结点与满二叉树的编号一一对应、只有最后两层可能有叶子节点、最多只能有一个度为1的结点、i<[n/2]为分支结点，i>[n/2]为叶子节点
*	二叉排序树：左子树上的所有结点的关键字均小于根节点的关键字、右子树上的所有结点均大于根节点的关键字
*	平衡二叉树：任意结点的左子树和右子树的深度之差不超过1
* 
*							二叉树的常考性质
*	设非空二叉树中度为0，1，2的节点个数分别为n0，n1，n2，则n0 = n2 + 1
*	结点总数 n = n0 + n1 + n2;
*			 n = n1 + 2*n2 + 1;(树的结点数 = 总度数 + 1) 
*/
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

bool CreateBiTree(BiTree& T);

//创建一棵二叉树，约定用户遵照前序遍历的方式输入数据
//ABDECFG
bool CreateBiTree(BiTree& T) {
	char c;
	scanf_s("%c", &c,1);

	if (' ' == c)
	{
		T = NULL;
	}
	else
	{
		T = (BiTNode*)malloc(sizeof(BiTNode));
		if (T == NULL)
			return false;
		T->data = c;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	
	return true;
}
void visit(char c, int level)
{
	printf("%c 位于第 %d 层\n", c, level);
}
//空间复杂度O(h)
// 前序遍历二叉树
void PreOrderTraverse(BiTree T, int level)
{
	if (T)
	{
		visit(T->data, level);
		PreOrderTraverse(T->lchild, level + 1);
		PreOrderTraverse(T->rchild, level + 1);
	}
}
// 中序遍历二叉树：给出中序遍历序列可通过前序遍历序列或后序遍历序列或层序遍历序列恢复二叉树
void MidOrderTraverse(BiTree T, int level)
{
	if (T)
	{
		MidOrderTraverse(T->lchild, level + 1);
		visit(T->data, level);
		MidOrderTraverse(T->rchild, level + 1);
	}
}
// 后序遍历二叉树
void PostOrderTraverse(BiTree T, int level)
{
	if (T)
	{
		PostOrderTraverse(T->lchild, level + 1);
		PostOrderTraverse(T->rchild, level + 1);
		visit(T->data, level);
	}
}

int main()
{
	BiTree T;
	CreateBiTree(T);
	PreOrderTraverse(T, 1);
	printf("\n");
	MidOrderTraverse(T, 1);
	printf("\n");
	PostOrderTraverse(T, 1);
	return 0;
}
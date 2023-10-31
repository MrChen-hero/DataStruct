#include<stdio.h>
#include<stdlib.h>
#include<stack>

// 线索存储标志位
// Link(0)：表示指向左右孩子的指针
// Thread(1)：表示指向前驱后继的线索
typedef enum { Link, Thread }PointerTag;

typedef struct BiThrNode {
	char data;
	struct BiThrNode* lchild, * rchild;
	PointerTag ltag;
	PointerTag rtag;
}BiThrNode, * BiThrTree;

void CreateBiTree(BiThrTree& T);
void InThreading(BiThrTree& T);
void PreThreading(BiThrTree& T);
void PostThreading(BiThrTree& T);

void CreateTreadTree(BiThrTree& T);

//全局变量,始终指向刚刚访问过的结点
BiThrTree pre = NULL;

//前序遍历方式输入创建二叉树
void CreateBiTree(BiThrTree& T) {
	char c;
	scanf_s("%c", &c, 1);
	if (' ' == c) {
		T = NULL;
	}//递归结束条件
	else {
		T = (BiThrNode*)malloc(sizeof(BiThrNode));
		if (T == NULL)
			return ;
		T->data = c;
		T->ltag = Link;
		T->rtag = Link;//将初始标志记为Link
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	
}
//中序线索化
void InThreading(BiThrTree& T) {
	if (T) {
		InThreading(T->lchild);//递归左孩子线索化

		if (T->lchild == NULL) {
			//如果当前结点没有左孩子
			T->lchild = pre;//将左孩子指向上一个访问过的结点，作为线索
			T->ltag = Thread;
		}
		if (pre!=NULL && pre->rchild == NULL) {
			//如果前一个结点没有右孩子
			pre->rchild = T;//将前一个结点的右孩子指向当前结点，作为线索
			pre->rtag = Thread;
		}
		pre = T;//更新pre指针到当前结点

		InThreading(T->rchild);//递归右孩子线索化
	}
}

//先序遍历线索化
void PreThreading(BiThrTree& T) {
	if (T) {
		if (T->lchild == NULL) {
			//如果当前结点没有左孩子
			T->lchild = pre;//将左孩子指向上一个访问过的结点，作为线索
			T->ltag = Thread;
		}
		if (pre != NULL && pre->rchild == NULL) {
			//如果前一个结点没有右孩子
			pre->rchild = T;//将前一个结点的右孩子指向当前结点，作为线索
			pre->rtag = Thread;
		}
		pre = T;//更新pre指针到当前结点

		if(T->ltag == Link)//防止出现死循环
			PreThreading(T->lchild);//递归左孩子线索化
		if(T->rtag == Link)
			PreThreading(T->rchild);//递归右孩子线索化
	}
}

//后序遍历线索化
void PostThreading(BiThrTree& T) {
	if (T) {
		PostThreading(T->lchild);//递归左孩子线索化

		PostThreading(T->rchild);//递归右孩子线索化

		if (T->lchild == NULL) {
			//如果当前结点没有左孩子
			T->lchild = pre;//将左孩子指向上一个访问过的结点，作为线索
			T->ltag = Thread;
		}
		if (pre != NULL && pre->rchild == NULL) {
			//如果前一个结点没有右孩子
			pre->rchild = T;//将前一个结点的右孩子指向当前结点，作为线索
			pre->rtag = Thread;
		}
		pre = T;//更新pre指针到当前结点

	}
}

void CreateTreadTree(BiThrTree& T) {
	if (T != NULL) {
		//InThreading(T);
		//PreThreading(T);
		PostThreading(T);
		if(pre->rchild == NULL)//最后一个结点的右孩子指向NULL
			pre->rtag = Thread;//将最后结点的rtag赋值为Thread
	}
}

void visit(char c)
{
	printf("%c", c);
}

// 中序遍历二叉树，非递归
void InOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T; 
	//正向中序遍历  DBEAFCG
	while (p != NULL) // 当p指向根结点时，遍历结束
	{
		while (p->ltag == Link && p->lchild != NULL) // 如果p有左孩子，就一直向左走
		{
			p = p->lchild;
		}
		visit(p->data); // 访问p结点

		while (p->rtag == Thread && p->rchild != NULL) // 如果p有右线索，就一直向右走
		{
			p = p->rchild;
			visit(p->data); // 访问p结点
		}

		p = p->rchild; // 否则，p指向p的右孩子
	}
	printf("\n");
	//逆向中序遍历  GCFAEBD
	p = T;
	while (p != NULL) // 当p指向根结点时，遍历结束
	{
		while (p->rtag == Link && p->rchild != NULL) // 找到最右下的结点
		{
			p = p->rchild;
		}
		visit(p->data); // 访问p结点

		while (p->ltag == Thread && p->lchild != NULL) // 如果p有左线索，就一直向左走
		{
			p = p->lchild;
			visit(p->data); // 访问p结点
		}

		p = p->lchild; // 否则，p指向p的右孩子
	}
}

//前序遍历非递归  找不到前驱
void PreOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T; 

	while (p != NULL) // 当p指向根结点时，遍历结束
	{
		visit(p->data); // 访问p结点

		while (p->ltag == Link && p->lchild != NULL) // 如果p有左孩子，就一直向左走
		{
			p = p->lchild;
			visit(p->data); // 访问p结点
		}

		while (p->rtag == Thread && p->rchild != NULL && p->rchild->rtag != Link) // 如果p有右线索，就一直向右走
		{
			p = p->rchild;
			visit(p->data);
		}
		p = p->rchild;
	}
}//ABDECFG

// 修改该段代码以实现后序遍历线索二叉树
void PostOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T;
	//逆序后序遍历
	while (p != NULL) {
		visit(p->data);
		while (p->rtag == Link && p->rchild != NULL)
		{
			p = p->rchild;
			visit(p->data);
		}
		while (p->ltag == Thread && p->lchild != NULL)
		{
			p = p->lchild;
			visit(p->data);
		}
		p = p->lchild;
	}
}
//DEBFGCA

int main() {
	BiThrTree T;
	CreateBiTree(T);
	CreateTreadTree(T);

	//InOrderTraverse(T);
	//PreOrderTraverse(T);
	PostOrderTraverse(T);
	return 0;
}

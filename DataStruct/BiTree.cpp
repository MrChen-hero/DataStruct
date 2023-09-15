/*							�������Ļ�������
*	�ص㣺1��ÿ���ڵ�����ֻ������������2�������������ܵߵ�������������������
*	
*	����������ֻ�����һ����Ҷ�ӽ�㡢�����ڶ�Ϊ1�Ľ�㡢��1��ʼ��ţ����i������Ϊ2i,�Һ���Ϊ2i+1;
*	��ȫ��������ÿ����������������ı��һһ��Ӧ��ֻ��������������Ҷ�ӽڵ㡢���ֻ����һ����Ϊ1�Ľ�㡢i<[n/2]Ϊ��֧��㣬i>[n/2]ΪҶ�ӽڵ�
*	�������������������ϵ����н��Ĺؼ��־�С�ڸ��ڵ�Ĺؼ��֡��������ϵ����н������ڸ��ڵ�Ĺؼ���
*	ƽ�����������������������������������֮�����1
* 
*							�������ĳ�������
*	��ǿն������ж�Ϊ0��1��2�Ľڵ�����ֱ�Ϊn0��n1��n2����n0 = n2 + 1
*	������� n = n0 + n1 + n2;
*			 n = n1 + 2*n2 + 1;(���Ľ���� = �ܶ��� + 1) 
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

//����һ�ö�������Լ���û�����ǰ������ķ�ʽ��������
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
	printf("%c λ�ڵ� %d ��\n", c, level);
}
//�ռ临�Ӷ�O(h)
// ǰ�����������
void PreOrderTraverse(BiTree T, int level)
{
	if (T)
	{
		visit(T->data, level);
		PreOrderTraverse(T->lchild, level + 1);
		PreOrderTraverse(T->rchild, level + 1);
	}
}
// �����������������������������п�ͨ��ǰ��������л����������л����������лָ�������
void MidOrderTraverse(BiTree T, int level)
{
	if (T)
	{
		MidOrderTraverse(T->lchild, level + 1);
		visit(T->data, level);
		MidOrderTraverse(T->rchild, level + 1);
	}
}
// �������������
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
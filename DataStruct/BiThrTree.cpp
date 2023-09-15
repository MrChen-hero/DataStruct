#include<stdio.h>
#include<stdlib.h>
#include<stack>

// �����洢��־λ
// Link(0)����ʾָ�����Һ��ӵ�ָ��
// Thread(1)����ʾָ��ǰ����̵�����
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

//ȫ�ֱ���,ʼ��ָ��ոշ��ʹ��Ľ��
BiThrTree pre = NULL;

//ǰ�������ʽ���봴��������
void CreateBiTree(BiThrTree& T) {
	char c;
	scanf_s("%c", &c, 1);
	if (' ' == c) {
		T = NULL;
	}//�ݹ��������
	else {
		T = (BiThrNode*)malloc(sizeof(BiThrNode));
		if (T == NULL)
			return ;
		T->data = c;
		T->ltag = Link;
		T->rtag = Link;//����ʼ��־��ΪLink
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	
}
//����������
void InThreading(BiThrTree& T) {
	if (T) {
		InThreading(T->lchild);//�ݹ�����������

		if (T->lchild == NULL) {
			//�����ǰ���û������
			T->lchild = pre;//������ָ����һ�����ʹ��Ľ�㣬��Ϊ����
			T->ltag = Thread;
		}
		if (pre!=NULL && pre->rchild == NULL) {
			//���ǰһ�����û���Һ���
			pre->rchild = T;//��ǰһ�������Һ���ָ��ǰ��㣬��Ϊ����
			pre->rtag = Thread;
		}
		pre = T;//����preָ�뵽��ǰ���

		InThreading(T->rchild);//�ݹ��Һ���������
	}
}

//�������������
void PreThreading(BiThrTree& T) {
	if (T) {
		if (T->lchild == NULL) {
			//�����ǰ���û������
			T->lchild = pre;//������ָ����һ�����ʹ��Ľ�㣬��Ϊ����
			T->ltag = Thread;
		}
		if (pre != NULL && pre->rchild == NULL) {
			//���ǰһ�����û���Һ���
			pre->rchild = T;//��ǰһ�������Һ���ָ��ǰ��㣬��Ϊ����
			pre->rtag = Thread;
		}
		pre = T;//����preָ�뵽��ǰ���

		if(T->ltag == Link)//��ֹ������ѭ��
			PreThreading(T->lchild);//�ݹ�����������
		if(T->rtag == Link)
			PreThreading(T->rchild);//�ݹ��Һ���������
	}
}

//�������������
void PostThreading(BiThrTree& T) {
	if (T) {
		PostThreading(T->lchild);//�ݹ�����������

		PostThreading(T->rchild);//�ݹ��Һ���������

		if (T->lchild == NULL) {
			//�����ǰ���û������
			T->lchild = pre;//������ָ����һ�����ʹ��Ľ�㣬��Ϊ����
			T->ltag = Thread;
		}
		if (pre != NULL && pre->rchild == NULL) {
			//���ǰһ�����û���Һ���
			pre->rchild = T;//��ǰһ�������Һ���ָ��ǰ��㣬��Ϊ����
			pre->rtag = Thread;
		}
		pre = T;//����preָ�뵽��ǰ���

	}
}

void CreateTreadTree(BiThrTree& T) {
	if (T != NULL) {
		//InThreading(T);
		//PreThreading(T);
		PostThreading(T);
		if(pre->rchild == NULL)//���һ�������Һ���ָ��NULL
			pre->rtag = Thread;//��������rtag��ֵΪThread
	}
}

void visit(char c)
{
	printf("%c", c);
}

// ����������������ǵݹ�
void InOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T; 
	//�����������  DBEAFCG
	while (p != NULL) // ��pָ������ʱ����������
	{
		while (p->ltag == Link && p->lchild != NULL) // ���p�����ӣ���һֱ������
		{
			p = p->lchild;
		}
		visit(p->data); // ����p���

		while (p->rtag == Thread && p->rchild != NULL) // ���p������������һֱ������
		{
			p = p->rchild;
			visit(p->data); // ����p���
		}

		p = p->rchild; // ����pָ��p���Һ���
	}
	printf("\n");
	//�����������  GCFAEBD
	p = T;
	while (p != NULL) // ��pָ������ʱ����������
	{
		while (p->rtag == Link && p->rchild != NULL) // �ҵ������µĽ��
		{
			p = p->rchild;
		}
		visit(p->data); // ����p���

		while (p->ltag == Thread && p->lchild != NULL) // ���p������������һֱ������
		{
			p = p->lchild;
			visit(p->data); // ����p���
		}

		p = p->lchild; // ����pָ��p���Һ���
	}
}

//ǰ������ǵݹ�  �Ҳ���ǰ��
void PreOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T; 

	while (p != NULL) // ��pָ������ʱ����������
	{
		visit(p->data); // ����p���

		while (p->ltag == Link && p->lchild != NULL) // ���p�����ӣ���һֱ������
		{
			p = p->lchild;
			visit(p->data); // ����p���
		}

		while (p->rtag == Thread && p->rchild != NULL && p->rchild->rtag != Link) // ���p������������һֱ������
		{
			p = p->rchild;
			visit(p->data);
		}
		p = p->rchild;
	}
}//ABDECFG

// �޸ĸöδ�����ʵ�ֺ����������������
void PostOrderTraverse(BiThrTree T)
{
	BiThrTree p;
	p = T;
	//����������
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

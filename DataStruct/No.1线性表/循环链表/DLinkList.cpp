#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLinkList;

bool InitList(DLinkList& L);	//初始化
bool Print(DLinkList& L);		//打印
bool DestoryList(DLinkList& L);	//销毁表
bool InsertNextDNode(DNode* p, DNode* s);	//指定节点后插
bool DelectNextDNode(DNode* p);				//指定节点后删
bool ListInsert(DLinkList& L, int i, int e);	//按位序插入


bool InitList(DLinkList& L) {
	L = (DLinkList)malloc(sizeof(DNode));
	if (L == NULL)
		return false;
	L->next = NULL;
	L->prior = NULL;
	printf("Success!\n");
	return true;
}

bool DestoryList(DLinkList& L) {
	while (L->next != NULL)//循环删除头结点L的下一节点，直到下一节点为空
		DelectNextDNode(L);
	free(L);//删除头结点
	printf("Success!\n");
	return true;
}

bool Print(DLinkList& L) {
	DNode* p = L->next;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return true;
}

//在p节点后插入s节点
bool InsertNextDNode(DNode* p, DNode* s) {
	if (p == NULL || s == NULL)
		return false;
	s->next = p->next;
	if (p->next != NULL)//当p节点的下一个节点为空时，不需要将下一个节点的prior指针指向s
		p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}

//删除p节点后节点
bool DelectNextDNode(DNode* p) {
	if (p == NULL)
		return false;
	DNode* q = p->next;
	if (q == NULL)
		return false;

	p->next = q->next;
	if (q->next != NULL)//q节点是最后一个节点时，不需要执行此操作
		q->next->prior = p;
	free(q);

	return true;
}

//位序插入
bool ListInsert(DLinkList& L,int i,int e) {
	DNode* s, * p;
	int j = 0;
	if (i < 1)
		return false;
	p = L;//头结点作为第0个节点
	while (p != NULL && j < i - 1) {//找到第i-1个节点
		p = p->next;
		j++;
	}
	s = (DNode*)malloc(sizeof(DNode));
	if (s == NULL)
		return false;
	s->data = e;
	s->prior = s->next = NULL;//初始化节点
	InsertNextDNode(p, s);

	return true;
}


int main() {
	DLinkList L;
	InitList(L);

	ListInsert(L, 1, 1);
	ListInsert(L, 2, 3);
	ListInsert(L, 3, 4);
	ListInsert(L, 2, 2);
	Print(L);

	DestoryList(L);
	return 0;
}
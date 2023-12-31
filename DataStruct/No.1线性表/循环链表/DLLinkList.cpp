#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLLinkList;

bool InitList(DLLinkList& L);	//初始化
bool Print(DLLinkList& L);		//打印
bool DestoryList(DLLinkList& L);//销毁
bool InsertNextDNode(DNode* p, DNode* s);//指定节点后插
bool DelectNextDNode(DNode* p);			 //指定节点后删
bool ListInsert(DLLinkList& L, int i, int e); //按位序插入


bool InitList(DLLinkList& L) {
	L = (DLLinkList)malloc(sizeof(DNode));
	if (L == NULL)
		return false;
	L->next = L;
	L->prior = L;
	printf("Success!\n");
	return true;
}

bool Print(DLLinkList& L) {
	DNode* p = L->next;
	while (p != L) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return true;
}

//位序插入
bool ListInsert(DLLinkList& L, int i, int e) {
	DNode* s, * p;
	int j = 0;
	if (i < 1)
		return false;
	p = L;//头结点作为第0个节点
	while (p->next != L && j < i - 1) {//找到第i-1个节点
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

bool DestoryList(DLLinkList& L) {
	while (L->next != L)//循环删除头结点L的下一节点，直到下一节点为空
		DelectNextDNode(L);
	free(L);//删除头结点
	printf("Success!\n");
	return true;
}

//在p节点后插入s节点
bool InsertNextDNode(DNode* p, DNode* s) {
	if (p == NULL || s == NULL)
		return false;
	s->next = p->next;
	p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}

//删除p节点后节点，删除前一节点秩序将next和prior调换
bool DelectNextDNode(DNode* p) {
	if (p == NULL)
		return false;
	
	DNode* q = p->next;
	if (q == NULL)
		return false;

	p->next = q->next;
	q->next->prior = p;//双循环链表中最后一个节点连接头结点，故该语句满足所有情况

	free(q);
	return true;
}

int main() {
	DLLinkList L;
	InitList(L);

	ListInsert(L, 1, 1);
	ListInsert(L, 2, 3);
	ListInsert(L, 3, 4);
	ListInsert(L, 2, 2);
	Print(L);

	DestoryList(L);
	return 0;
}
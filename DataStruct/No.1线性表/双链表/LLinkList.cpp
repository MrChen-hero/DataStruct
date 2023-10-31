#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LLinkList;

bool InitList(LLinkList& L);	//初始化
bool Print(LLinkList& L);		//打印
bool ListInsert(LLinkList& L, int i, ElemType e); //按位序插入
bool InsertNestNode(LNode* p, ElemType e);	//指定节点后插
bool DestoryList(LLinkList& L);	//销毁
bool DeletNextNode(LNode* p);	//指定节点后删

//初始化
bool InitList(LLinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL)
		return false;
	L->next = L;
	printf("success!\n");
	return true;
}

//打印
bool Print(LLinkList& L) {
	LNode* p = L;
	while (p->next != L)
	{
		p = p->next;
		printf("%d ", p->data);
	}
	printf("\n");

	return true;
}

bool ListInsert(LLinkList& L, int i, ElemType e) {
	if (i < 1)
		return false;
		LNode* p = L;
	//从0开始，将头节点视为第0个节点
		int j = 0;
	//找到第i-1个节点
		while (p != NULL && j < i - 1 ) 
		{
			p = p->next;
			j++;
		}
	if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;

	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
//指定节点后插操作
bool InsertNestNode(LNode* p, ElemType e) {
	if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
//指定节点后删
bool DeletNextNode(LNode* p) {
	if (p == NULL)
		return false;

	LNode* temp;
	temp = p->next;
	p->next = temp->next;
	free(temp);
	return true;
}
//销毁表
bool DestoryList(LLinkList& L) {
	while (L->next != L)
		DeletNextNode(L);
	free(L);
	printf("success!!!\n");
	return true;
}

int main() {
	LLinkList L;
	InitList(L);
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 3);
	ListInsert(L, 3, 4);
	ListInsert(L, 2, 2);
	Print(L);
	DestoryList(L);
	return 0;
}
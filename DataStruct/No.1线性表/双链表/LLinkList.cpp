#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LLinkList;

bool InitList(LLinkList& L);	//��ʼ��
bool Print(LLinkList& L);		//��ӡ
bool ListInsert(LLinkList& L, int i, ElemType e); //��λ�����
bool InsertNestNode(LNode* p, ElemType e);	//ָ���ڵ���
bool DestoryList(LLinkList& L);	//����
bool DeletNextNode(LNode* p);	//ָ���ڵ��ɾ

//��ʼ��
bool InitList(LLinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL)
		return false;
	L->next = L;
	printf("success!\n");
	return true;
}

//��ӡ
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
	//��0��ʼ����ͷ�ڵ���Ϊ��0���ڵ�
		int j = 0;
	//�ҵ���i-1���ڵ�
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
//ָ���ڵ������
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
//ָ���ڵ��ɾ
bool DeletNextNode(LNode* p) {
	if (p == NULL)
		return false;

	LNode* temp;
	temp = p->next;
	p->next = temp->next;
	free(temp);
	return true;
}
//���ٱ�
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
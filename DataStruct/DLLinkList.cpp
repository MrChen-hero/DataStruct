#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLLinkList;

bool InitList(DLLinkList& L);	//��ʼ��
bool Print(DLLinkList& L);		//��ӡ
bool DestoryList(DLLinkList& L);//����
bool InsertNextDNode(DNode* p, DNode* s);//ָ���ڵ���
bool DelectNextDNode(DNode* p);			 //ָ���ڵ��ɾ
bool ListInsert(DLLinkList& L, int i, int e); //��λ�����


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

//λ�����
bool ListInsert(DLLinkList& L, int i, int e) {
	DNode* s, * p;
	int j = 0;
	if (i < 1)
		return false;
	p = L;//ͷ�����Ϊ��0���ڵ�
	while (p->next != L && j < i - 1) {//�ҵ���i-1���ڵ�
		p = p->next;
		j++;
	}
	s = (DNode*)malloc(sizeof(DNode));
	if (s == NULL)
		return false;
	s->data = e;
	s->prior = s->next = NULL;//��ʼ���ڵ�
	InsertNextDNode(p, s);

	return true;
}

bool DestoryList(DLLinkList& L) {
	while (L->next != L)//ѭ��ɾ��ͷ���L����һ�ڵ㣬ֱ����һ�ڵ�Ϊ��
		DelectNextDNode(L);
	free(L);//ɾ��ͷ���
	printf("Success!\n");
	return true;
}

//��p�ڵ�����s�ڵ�
bool InsertNextDNode(DNode* p, DNode* s) {
	if (p == NULL || s == NULL)
		return false;
	s->next = p->next;
	p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}

//ɾ��p�ڵ��ڵ㣬ɾ��ǰһ�ڵ�����next��prior����
bool DelectNextDNode(DNode* p) {
	if (p == NULL)
		return false;
	
	DNode* q = p->next;
	if (q == NULL)
		return false;

	p->next = q->next;
	q->next->prior = p;//˫ѭ�����������һ���ڵ�����ͷ��㣬�ʸ���������������

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
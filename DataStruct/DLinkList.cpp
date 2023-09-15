#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLinkList;

bool InitList(DLinkList& L);	//��ʼ��
bool Print(DLinkList& L);		//��ӡ
bool DestoryList(DLinkList& L);	//���ٱ�
bool InsertNextDNode(DNode* p, DNode* s);	//ָ���ڵ���
bool DelectNextDNode(DNode* p);				//ָ���ڵ��ɾ
bool ListInsert(DLinkList& L, int i, int e);	//��λ�����


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
	while (L->next != NULL)//ѭ��ɾ��ͷ���L����һ�ڵ㣬ֱ����һ�ڵ�Ϊ��
		DelectNextDNode(L);
	free(L);//ɾ��ͷ���
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

//��p�ڵ�����s�ڵ�
bool InsertNextDNode(DNode* p, DNode* s) {
	if (p == NULL || s == NULL)
		return false;
	s->next = p->next;
	if (p->next != NULL)//��p�ڵ����һ���ڵ�Ϊ��ʱ������Ҫ����һ���ڵ��priorָ��ָ��s
		p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}

//ɾ��p�ڵ��ڵ�
bool DelectNextDNode(DNode* p) {
	if (p == NULL)
		return false;
	DNode* q = p->next;
	if (q == NULL)
		return false;

	p->next = q->next;
	if (q->next != NULL)//q�ڵ������һ���ڵ�ʱ������Ҫִ�д˲���
		q->next->prior = p;
	free(q);

	return true;
}

//λ�����
bool ListInsert(DLinkList& L,int i,int e) {
	DNode* s, * p;
	int j = 0;
	if (i < 1)
		return false;
	p = L;//ͷ�����Ϊ��0���ڵ�
	while (p != NULL && j < i - 1) {//�ҵ���i-1���ڵ�
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
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode,*LinkList;

//��ͷ������
bool InitList(LinkList& L);	//��ʼ��
bool Print(LinkList& L);	//��ӡ
bool ListInsert(LinkList& L, int i, ElemType e);	//��λ����
bool ListDelete(LinkList& L, int i);				//��λɾ��
bool InsertNestNode(LNode* p, ElemType e);	//ָ���ڵ���
bool InsertPriorNode(LNode* p, ElemType e);	//ָ���ڵ�ǰ��
LNode* OrderGet(LinkList& L, int i);	 //�������
LNode* ValueGet(LinkList& L, ElemType e);//��ֵ����
LinkList HeadInsert(LinkList& L);	//ͷ�巨
LinkList RearInsert(LinkList& L);	//β�巨

//����ͷ������
bool InitList_NoHead(LinkList& L);	//��ʼ��
bool Print_NoHead(LinkList& L);		//��ӡ
bool ListInsert_NoHead(LinkList& L, int i, ElemType e);	//��λ����
bool ListDelete_NoHead(LinkList& L, int i);				//��λɾ��
LNode* OrderGet_NoHead(LinkList& L, int i);		//�������
LNode* ValueGet_NoHead(LinkList& L, ElemType e);//��ֵ����
LinkList HeadInsert_NoHead(LinkList& L);//ͷ�巨
LinkList RearInsert_NoHead(LinkList& L);//β�巨

/*-----------------------------------------��ͷ������-----------------------------------------------*/

//��ʼ��
bool InitList(LinkList &L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL)
		return false;
	L->next = NULL;
	printf("success!\n");
	return true;
}
//��ӡ
bool Print(LinkList& L) {
	LNode* p = L;
	while (p->next != NULL)
	{
		p = p->next;
		printf("%d ", p->data);
	}
	printf("\n");

	return true;
}

//��λ�����(��ͷ���)
bool ListInsert(LinkList& L, int i, ElemType e) {
	if (i < 1)
		return false;
//	LNode* p = L;
//	//��0��ʼ����ͷ�ڵ���Ϊ��0���ڵ�
//	int j = 0;
////�ҵ���i-1���ڵ�
//	while (p != NULL && j < i - 1 ) 
//	{
//		p = p->next;
//		j++;
//	}
	LNode* p = OrderGet(L, i - 1);
	InsertNestNode(p, e);
	/*if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;

	s->data = e;
	s->next = p->next;
	p->next = s;*/
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
//ָ���ڵ�ǰ��
bool InsertPriorNode(LNode* p, ElemType e) {
	if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e;        //�������ڵ��������ʵ����ǰ��

	return true;
}
//��λ��ɾ��(��ͷ���)
bool ListDelete(LinkList& L, int i) {
	if (i < 1)
		return false;
	//LNode* p = L;
	//int j = 0; //��ͷ��㵱����0���ڵ�
	//while (p != NULL && j < i - 1) {//�ҵ���i-1���ڵ�
	//	p = p->next;
	//	j++;
	//}

	LNode* p = OrderGet(L, i - 1);
	if (p == NULL)
		return false;
	LNode* temp = p->next;
	p->next = p->next->next;
	free(temp);
	return true;
}
//��λ�����
LNode* OrderGet(LinkList& L, int i) {
	if (i < 0)
		return NULL;
	LNode* p = L;
	int j = 0;
	while (p != NULL && j < i) {//�ҵ���i���ڵ�
		p = p->next;
		j++;
	}
	return p;
}
//��ֵ����
LNode* ValueGet(LinkList& L, ElemType e) {
	LNode* p = L->next;
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	return p;
}

LinkList HeadInsert(LinkList& L) {
	LNode* s;
	int x=0;
	L = (LinkList)malloc(sizeof(LNode));
	if (L == NULL)
		return NULL;
	L->next = NULL;

	while (scanf_s("%d",&x) != EOF && x != 9999) {
		s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
			return NULL;
		s->data = x;
		s->next = L->next;
		L->next = s;
	}
	return L;
}

LinkList RearInsert(LinkList& L) {
	LNode* s, * rear;
	int x = 0;
	L = (LinkList)malloc(sizeof(LNode));
	if (L == NULL)
		return NULL;
	L->next = NULL;
	rear = L;
	while (scanf_s("%d", &x) != EOF && x != 9999) {
		s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
			return NULL;
		s->data = x;
		s->next = rear->next;
		rear->next = s;
		rear = s;
	}
	return L;
}

/*-----------------------------------------��ͷ������-----------------------------------------------*/
bool InitList_NoHead(LinkList& L) {
	L = NULL;
	printf("success!\n");
	return true;
}
//��λ�����(��ͷ���)
bool ListInsert_NoHead(LinkList& L, int i, ElemType e) {
	if (i < 1)
		return false;
	if (i == 1) {//�����һ���ڵ�ĵ����߼�
		LNode* s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
			return false;
		s->data = e;
		s->next = L;
		L = s;
		return true;
	}
	//LNode* p = L;
	//int j = 1; //ָ���һ���ڵ�
	//while (p != NULL && j < i - 1) {
	//	p = p->next;
	//	j++;
	//}

	LNode* p = OrderGet_NoHead(L, i - 1);
	InsertNestNode(p, e);

	/*if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->data = e;
	s->next = p->next;
	p->next = s;*/

	return true;
}
//��λ��ɾ��(����ͷ���)
bool ListDelete_NoHead(LinkList& L, int i) {
	if (i < 1)
		return false;
	if (i == 1) {
		LNode* temp = L;
		L = L->next;
		free(temp);
		return true;
	}
	//LNode* p = L;
	//int j = 1;
	//while (p != NULL && j < i - 1) {
	//	p = p->next;
	//	j++;
	//}

	LNode* p = OrderGet_NoHead(L, i-1);
	if (p == NULL)
		return false;
	LNode* temp = p->next;
	p->next = p->next->next;
	free(temp);
	return true;
}
LNode* OrderGet_NoHead(LinkList& L, int i) {
	if (i < 1)
		return NULL;
	LNode* p = L;
	int j = 1;
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	return p;
}

LNode* ValueGet_NoHead(LinkList& L, ElemType e) {
	LNode* p = L;
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	return p;
}

bool Print_NoHead(LinkList& L) {
	LNode* p = L;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return true;
}

LinkList HeadInsert_NoHead(LinkList& L) {
	LNode* s;
	int x;
	L = NULL;
	while (scanf_s("%d", &x) != EOF && x != 9999) {
		s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
			return NULL;
		s->data = x;
		s->next = L;
		L = s;
	}
	return L;
}

LinkList RearInsert_NoHead(LinkList& L) {
	LNode* s, * rear;
	int x;
	L = NULL;
	rear = L;
	while (scanf_s("%d", &x) != EOF && x != 9999) {
		s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
			return NULL;
		if (L == NULL) {//��һ���ڵ�Ĳ���
			s->data = x;
			s->next = L;
			L = s;
			rear = L;
			continue;
		}
		s->data = x;
		s->next = rear->next;
		rear->next = s;
		rear = s;
	}
	return L;
}


int main() {
	LinkList L;
	//��ͷ���ͷ��β�巨
	//HeadInsert_NoHead(L);
	RearInsert_NoHead(L);
	Print_NoHead(L);


	//��ͷ�ڵ�ͷ��β�巨
	//HeadInsert(L);
	//RearInsert(L);
	//Print(L);
	
	//��ͷ����ʼ��
	//InitList(L);
	////λ�����(��ͷ���)
	//ListInsert(L, 1, 1);
	//ListInsert(L, 2, 3);
	//ListInsert(L, 3, 4);
	//ListInsert(L, 2, 2);
	////λ��ɾ��(��ͷ���)
	//ListDelete(L, 2);
	//Print(L);
	////printf("%d", ValueGet(L, 3)->data);
	
	//����ͷ�ڵ��ʼ��
	//InitList_NoHead(L);
	////λ�����(����ͷ���)
	//ListInsert_NoHead(L, 1, 2);
	//ListInsert_NoHead(L, 2, 3);
	//ListInsert_NoHead(L, 3, 4);
	//ListInsert_NoHead(L, 1, 1);
	////λ��ɾ��(����ͷ���)
	//ListDelete_NoHead(L, 2);
	//Print_NoHead(L);
	////printf("%d", ValueGet_NoHead(L, 3)->data);
	return 0;
}



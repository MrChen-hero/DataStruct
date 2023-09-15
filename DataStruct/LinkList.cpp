#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode,*LinkList;

//含头结点操作
bool InitList(LinkList& L);	//初始化
bool Print(LinkList& L);	//打印
bool ListInsert(LinkList& L, int i, ElemType e);	//按位插入
bool ListDelete(LinkList& L, int i);				//按位删除
bool InsertNestNode(LNode* p, ElemType e);	//指定节点后插
bool InsertPriorNode(LNode* p, ElemType e);	//指定节点前插
LNode* OrderGet(LinkList& L, int i);	 //按序查找
LNode* ValueGet(LinkList& L, ElemType e);//按值查找
LinkList HeadInsert(LinkList& L);	//头插法
LinkList RearInsert(LinkList& L);	//尾插法

//不含头结点操作
bool InitList_NoHead(LinkList& L);	//初始化
bool Print_NoHead(LinkList& L);		//打印
bool ListInsert_NoHead(LinkList& L, int i, ElemType e);	//按位插入
bool ListDelete_NoHead(LinkList& L, int i);				//按位删除
LNode* OrderGet_NoHead(LinkList& L, int i);		//按序查找
LNode* ValueGet_NoHead(LinkList& L, ElemType e);//按值查找
LinkList HeadInsert_NoHead(LinkList& L);//头插法
LinkList RearInsert_NoHead(LinkList& L);//尾插法

/*-----------------------------------------有头结点操作-----------------------------------------------*/

//初始化
bool InitList(LinkList &L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL)
		return false;
	L->next = NULL;
	printf("success!\n");
	return true;
}
//打印
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

//按位序插入(带头结点)
bool ListInsert(LinkList& L, int i, ElemType e) {
	if (i < 1)
		return false;
//	LNode* p = L;
//	//从0开始，将头节点视为第0个节点
//	int j = 0;
////找到第i-1个节点
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
//指定节点前插
bool InsertPriorNode(LNode* p, ElemType e) {
	if (p == NULL)
		return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e;        //交换两节点的数据以实现拟前插

	return true;
}
//按位序删除(带头结点)
bool ListDelete(LinkList& L, int i) {
	if (i < 1)
		return false;
	//LNode* p = L;
	//int j = 0; //将头结点当作第0个节点
	//while (p != NULL && j < i - 1) {//找到第i-1个节点
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
//按位序查找
LNode* OrderGet(LinkList& L, int i) {
	if (i < 0)
		return NULL;
	LNode* p = L;
	int j = 0;
	while (p != NULL && j < i) {//找到第i个节点
		p = p->next;
		j++;
	}
	return p;
}
//按值查找
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

/*-----------------------------------------无头结点操作-----------------------------------------------*/
bool InitList_NoHead(LinkList& L) {
	L = NULL;
	printf("success!\n");
	return true;
}
//按位序插入(无头结点)
bool ListInsert_NoHead(LinkList& L, int i, ElemType e) {
	if (i < 1)
		return false;
	if (i == 1) {//插入第一个节点的单独逻辑
		LNode* s = (LNode*)malloc(sizeof(LNode));
		if (s == NULL)
			return false;
		s->data = e;
		s->next = L;
		L = s;
		return true;
	}
	//LNode* p = L;
	//int j = 1; //指向第一个节点
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
//按位序删除(不带头结点)
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
		if (L == NULL) {//第一个节点的操作
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
	//无头结点头插尾插法
	//HeadInsert_NoHead(L);
	RearInsert_NoHead(L);
	Print_NoHead(L);


	//有头节点头插尾插法
	//HeadInsert(L);
	//RearInsert(L);
	//Print(L);
	
	//带头结点初始化
	//InitList(L);
	////位序插入(带头结点)
	//ListInsert(L, 1, 1);
	//ListInsert(L, 2, 3);
	//ListInsert(L, 3, 4);
	//ListInsert(L, 2, 2);
	////位序删除(带头结点)
	//ListDelete(L, 2);
	//Print(L);
	////printf("%d", ValueGet(L, 3)->data);
	
	//不带头节点初始化
	//InitList_NoHead(L);
	////位序插入(不带头结点)
	//ListInsert_NoHead(L, 1, 2);
	//ListInsert_NoHead(L, 2, 3);
	//ListInsert_NoHead(L, 3, 4);
	//ListInsert_NoHead(L, 1, 1);
	////位序删除(不带头结点)
	//ListDelete_NoHead(L, 2);
	//Print_NoHead(L);
	////printf("%d", ValueGet_NoHead(L, 3)->data);
	return 0;
}



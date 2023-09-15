#include<stdio.h>
#include<stdlib.h>

#define ElemType int

//结点结构
typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode;
//队列结构
typedef struct LiQueue {
	LNode* front, * rear;
}LiQueue;

/**************************************带头结点操作*****************************************/
bool InitQueue(LiQueue& Q);	//初始化
bool Print(LiQueue& Q);		//打印
bool IsEmpty(LiQueue& Q);	//判断队空
bool EnQueue(LiQueue& Q, ElemType e);	//入队
bool DeQueue(LiQueue& Q, ElemType& e);	//出队

/**************************************无头结点操作*****************************************/
bool InitQueue_NoHead(LiQueue& Q);	//初始化
bool Print_NoHead(LiQueue& Q);		//打印
bool IsEmpty_NoHead(LiQueue& Q);	//判断队空
bool EnQueue_NoHead(LiQueue& Q, ElemType e);	//入队
bool DeQueue_NoHead(LiQueue& Q, ElemType& e);	//出队

/**************************************带头结点操作*****************************************/
bool InitQueue(LiQueue& Q) {
	Q.front = Q.rear = (LNode*)malloc(sizeof(LNode));
	if (Q.front == NULL || Q.rear == NULL)
		return false;
	Q.front->next = Q.rear->next = NULL;
	return true;
}
bool IsEmpty(LiQueue& Q) {
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}
bool Print(LiQueue& Q) {
	if (IsEmpty(Q))
		return false;
	LNode* temp = Q.front->next;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n带头结点成功\n");
	return true;
}
//入队
bool EnQueue(LiQueue& Q, ElemType e) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->data = e;
	s->next = Q.rear->next;
	Q.rear->next = s;
	Q.rear = s;
}
//出队
bool DeQueue(LiQueue& Q, ElemType& e) {
	if (IsEmpty(Q))
		return false;
	LNode* temp = Q.front->next;
	e = temp->data;
	Q.front->next = temp->next;
	if (Q.rear == temp)	//最后一个节点的操作
		Q.rear = Q.front;
	free(temp);
}
/**************************************无头结点操作*****************************************/
bool InitQueue_NoHead(LiQueue& Q) {
	Q.front = Q.rear = NULL;
	return true;
}
bool Print_NoHead(LiQueue& Q) {
	if (IsEmpty_NoHead(Q))
		return false;
	LNode* temp = Q.front;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n无头结点成功\n");
}
bool IsEmpty_NoHead(LiQueue& Q) {
	if (Q.front == NULL)
		return true;
	else
		return false;
}
//入队
bool EnQueue_NoHead(LiQueue& Q, ElemType e) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->data = e;
	if (IsEmpty_NoHead(Q)) {
		//插入第一个元素操作
		s->next = Q.rear;
		Q.front = s;
		Q.rear = s;
	}
	else {
		s->next = Q.rear->next;
		Q.rear->next = s;
		Q.rear = s;
	}
	return true;
}
//出队
bool DeQueue_NoHead(LiQueue& Q, ElemType& e) {
	if (IsEmpty_NoHead(Q))
		return false;
	LNode* temp = Q.front;
	e = temp->data;
	Q.front = Q.front->next;
	if (temp == Q.rear) {
		//最后一个节点
		Q.front = Q.rear = NULL;
	}
	return true;
}

int main() {
	ElemType e;

	LiQueue Q1;
	InitQueue(Q1);
	EnQueue(Q1, 1);
	EnQueue(Q1, 2);
	EnQueue(Q1, 3);
	EnQueue(Q1, 4);
	DeQueue(Q1, e);

	Print(Q1);

	LiQueue Q2;
	InitQueue_NoHead(Q2);
	EnQueue_NoHead(Q2, 1);
	EnQueue_NoHead(Q2, 2);
	EnQueue_NoHead(Q2, 3);
	EnQueue_NoHead(Q2, 4);
	DeQueue_NoHead(Q2, e);

	Print_NoHead(Q2);

	return 0;
}
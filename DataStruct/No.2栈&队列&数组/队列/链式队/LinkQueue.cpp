#include<stdio.h>
#include<stdlib.h>

#define ElemType int

//���ṹ
typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode;
//���нṹ
typedef struct LiQueue {
	LNode* front, * rear;
}LiQueue;

/**************************************��ͷ������*****************************************/
bool InitQueue(LiQueue& Q);	//��ʼ��
bool Print(LiQueue& Q);		//��ӡ
bool IsEmpty(LiQueue& Q);	//�ж϶ӿ�
bool EnQueue(LiQueue& Q, ElemType e);	//���
bool DeQueue(LiQueue& Q, ElemType& e);	//����

/**************************************��ͷ������*****************************************/
bool InitQueue_NoHead(LiQueue& Q);	//��ʼ��
bool Print_NoHead(LiQueue& Q);		//��ӡ
bool IsEmpty_NoHead(LiQueue& Q);	//�ж϶ӿ�
bool EnQueue_NoHead(LiQueue& Q, ElemType e);	//���
bool DeQueue_NoHead(LiQueue& Q, ElemType& e);	//����

/**************************************��ͷ������*****************************************/
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
	printf("\n��ͷ���ɹ�\n");
	return true;
}
//���
bool EnQueue(LiQueue& Q, ElemType e) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->data = e;
	s->next = Q.rear->next;
	Q.rear->next = s;
	Q.rear = s;
}
//����
bool DeQueue(LiQueue& Q, ElemType& e) {
	if (IsEmpty(Q))
		return false;
	LNode* temp = Q.front->next;
	e = temp->data;
	Q.front->next = temp->next;
	if (Q.rear == temp)	//���һ���ڵ�Ĳ���
		Q.rear = Q.front;
	free(temp);
}
/**************************************��ͷ������*****************************************/
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
	printf("\n��ͷ���ɹ�\n");
}
bool IsEmpty_NoHead(LiQueue& Q) {
	if (Q.front == NULL)
		return true;
	else
		return false;
}
//���
bool EnQueue_NoHead(LiQueue& Q, ElemType e) {
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;
	s->data = e;
	if (IsEmpty_NoHead(Q)) {
		//�����һ��Ԫ�ز���
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
//����
bool DeQueue_NoHead(LiQueue& Q, ElemType& e) {
	if (IsEmpty_NoHead(Q))
		return false;
	LNode* temp = Q.front;
	e = temp->data;
	Q.front = Q.front->next;
	if (temp == Q.rear) {
		//���һ���ڵ�
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
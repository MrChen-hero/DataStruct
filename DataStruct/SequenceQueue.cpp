#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define MAXSIZE 10

typedef struct SqQueue {
	ElemType data[MAXSIZE];
	int front, rear;//��βָ�룬����ָ��
	//int size;		//����size������Ϊ�ж϶����Ƿ�Ϊ����գ���ʱ�����ö��е�ȫ���ռ�
	//int tag;		//Ҳ����tag������ÿ��ɾ���ɹ�ʱtag=0������ɹ�ʱtag=1��ֻ��ɾ���������¶ӿգ�ֻ�в���������¶�������ʱ�����ö��е�ȫ���ռ�
}SqQueue;

bool InitQueue(SqQueue& Q);	//��ʼ��
bool Print(SqQueue& Q);	//��ӡ
bool EnQueue(SqQueue& Q, ElemType e);	//���
bool DeQueue(SqQueue& Q, ElemType& e);	//����
int GetSize(SqQueue& Q);	//��ȡ����Ԫ�ظ���


bool InitQueue(SqQueue& Q) {
	Q.front = Q.rear = 0;
	return true;
}

bool Print(SqQueue& Q) {
	if (Q.front == Q.rear)
		return false;	//����Ϊ��
	int temp = Q.front;
	while (temp != Q.rear) {
		printf("%d ", Q.data[temp]);
		temp = (temp + 1) % MAXSIZE;
	}
	printf("\n");
	printf("����Ԫ�ظ���Ϊ��%d\n", GetSize(Q));
	return true;
}

bool EnQueue(SqQueue& Q, ElemType e) {
	if ( (Q.rear + 1)%MAXSIZE == Q.front)
		return false;
	Q.data[Q.rear] = e;
	//Q.rear += 1;	//��ͨ�������
	Q.rear = (Q.rear + 1) % MAXSIZE;	//ѭ��������ӣ������ֵȡģʹ�ö�βָ�뵽���ֵʱ�ܻص��ʼ��λ��ʵ���߼��ϵ�ѭ��
	return true;
}

bool DeQueue(SqQueue& Q, ElemType& e) {
	if (Q.rear == Q.front)
		return false;
	e = Q.data[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return true;
}

int GetSize(SqQueue& Q) {
	return (Q.rear + MAXSIZE - Q.front) % MAXSIZE;
}

int main()
{
	SqQueue Q;
	ElemType e;
	InitQueue(Q);
	EnQueue(Q, 1);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	EnQueue(Q, 4);
	EnQueue(Q, 5);
	EnQueue(Q, 6);

	DeQueue(Q, e);
	DeQueue(Q, e);

	EnQueue(Q, 7);
	EnQueue(Q, 8);
	EnQueue(Q, 9);

	Print(Q);

	return 0;
}

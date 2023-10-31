#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define MAXSIZE 10

typedef struct SqQueue {
	ElemType data[MAXSIZE];
	int front, rear;//队尾指针，队首指针
	//int size;		//可用size变量作为判断队列是否为满或空，此时可利用队列的全部空间
	//int tag;		//也可用tag变量，每次删除成功时tag=0；插入成功时tag=1，只有删除操作导致队空，只有插入操作导致队满，此时可利用队列的全部空间
}SqQueue;

bool InitQueue(SqQueue& Q);	//初始化
bool Print(SqQueue& Q);	//打印
bool EnQueue(SqQueue& Q, ElemType e);	//入队
bool DeQueue(SqQueue& Q, ElemType& e);	//出队
int GetSize(SqQueue& Q);	//获取队列元素个数


bool InitQueue(SqQueue& Q) {
	Q.front = Q.rear = 0;
	return true;
}

bool Print(SqQueue& Q) {
	if (Q.front == Q.rear)
		return false;	//对列为空
	int temp = Q.front;
	while (temp != Q.rear) {
		printf("%d ", Q.data[temp]);
		temp = (temp + 1) % MAXSIZE;
	}
	printf("\n");
	printf("队列元素个数为：%d\n", GetSize(Q));
	return true;
}

bool EnQueue(SqQueue& Q, ElemType e) {
	if ( (Q.rear + 1)%MAXSIZE == Q.front)
		return false;
	Q.data[Q.rear] = e;
	//Q.rear += 1;	//普通队列入队
	Q.rear = (Q.rear + 1) % MAXSIZE;	//循环队列入队，对最大值取模使得队尾指针到最大值时能回到最开始的位置实现逻辑上的循环
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

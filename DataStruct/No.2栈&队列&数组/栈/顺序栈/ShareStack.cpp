#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10
#define ElemType int

typedef struct ShStack{
	ElemType data[MAXSIZE];
	int top0;
	int top1;
}ShStack;

bool InitStack(ShStack& S);	//��ʼ��
bool Push(ShStack& S, int StackNum, ElemType e);	//��ջ
bool Pop(ShStack& S, int StackNum, ElemType& x);	//��ջ

//��ʼ��
bool InitStack(ShStack& S) {
	S.top0 = -1;
	S.top1 = MAXSIZE;
	return true;
}
//��ջ
bool Push(ShStack& S, int StackNum, ElemType e) {
	if (S.top0 + 1 == S.top1)
		return false;
	
	if (StackNum == 0)
		S.data[++S.top0] = e;
	
	if (StackNum == 1)
		S.data[--S.top1] = e;
	
	return 0;
}
//��ջ
bool Pop(ShStack& S, int StackNum, ElemType& x) {
	if (StackNum == 0) {
		if (S.top0 == -1)
			return false;
		x = S.data[S.top0--];
	}
	
	if (StackNum == 1) {
		if (S.top1 == MAXSIZE)
			return false;
		x = S.data[S.top1++];
	}
	return true;
}


bool Print(ShStack& S) {
	if (S.top0 == -1 && S.top1 == MAXSIZE)
		return false;
	//0��ջ
	printf("No.0_Stack: ");
	while (S.top0 != -1)
		printf("%d ", S.data[S.top0--]);
	printf("\n");
	//1��ջ
	printf("No.1_Stack: ");
	while (S.top1 != MAXSIZE)
		printf("%d ", S.data[S.top1++]);
	printf("\n");
	return true;
}

int main()
{
	ShStack S;
	ElemType x;
	InitStack(S);
	Push(S, 0, 1);
	Push(S, 0, 2);
	Push(S, 0, 3);
	Push(S, 0, 4);

	Push(S, 1, 1);
	Push(S, 1, 2);
	Push(S, 1, 3);
	Push(S, 1, 4);

	Pop(S, 0, x);
	Pop(S, 1, x);

	Print(S);
	return 0;
}
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10
#define ElemType int

typedef struct ShStack{
	ElemType data[MAXSIZE];
	int top0;
	int top1;
}ShStack;

bool InitStack(ShStack& S);	//初始化
bool Push(ShStack& S, int StackNum, ElemType e);	//入栈
bool Pop(ShStack& S, int StackNum, ElemType& x);	//出栈

//初始化
bool InitStack(ShStack& S) {
	S.top0 = -1;
	S.top1 = MAXSIZE;
	return true;
}
//入栈
bool Push(ShStack& S, int StackNum, ElemType e) {
	if (S.top0 + 1 == S.top1)
		return false;
	
	if (StackNum == 0)
		S.data[++S.top0] = e;
	
	if (StackNum == 1)
		S.data[--S.top1] = e;
	
	return 0;
}
//出栈
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
	//0号栈
	printf("No.0_Stack: ");
	while (S.top0 != -1)
		printf("%d ", S.data[S.top0--]);
	printf("\n");
	//1号栈
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
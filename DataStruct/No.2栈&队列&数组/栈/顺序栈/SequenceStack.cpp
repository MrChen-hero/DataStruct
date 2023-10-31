#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10
#define ElemType int

typedef struct SqStack{
	ElemType data[MAXSIZE];
	int top;
}SqStack;

bool InitStack(SqStack& S);	 //初始化
bool StackEmpty(SqStack& S); //判断栈空
bool Push(SqStack& S, ElemType e);	//入栈
bool Pop(SqStack& S, ElemType& x);	//出栈

//初始化
bool InitStack(SqStack& S) {
	S.top = -1;//初始化栈顶指针
	return true;
}

//判断栈空
bool StackEmpty(SqStack& S) {
	if (S.top == -1)
		return true;
	else
		return false;
}
//入栈
bool Push(SqStack& S, ElemType e) {
	//栈满
	if (S.top == MAXSIZE - 1)
		return false;
	S.data[++S.top] = e;
	return true;
}
//出栈
bool Pop(SqStack& S, ElemType &x) {
	//栈空
	if (S.top == -1)
		return false;
	x = S.data[S.top--];
	return true;
}

bool Print(SqStack& S) {
	int temp = S.top;
	if (S.top == -1)
		return false;
	while (temp != -1) {
		printf("%d ", S.data[temp--]);
	}
	printf("\n");
	return true;
}

int main()
{
	SqStack S;
	ElemType x;
	InitStack(S);
	//入栈
	Push(S, 1);
	Push(S, 2);
	Push(S, 3);
	Push(S, 4);
	//出战
	Pop(S, x);
	printf("%d\n", x);

	Print(S);
	return 0;
}
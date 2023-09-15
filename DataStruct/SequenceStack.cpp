#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10
#define ElemType int

typedef struct SqStack{
	ElemType data[MAXSIZE];
	int top;
}SqStack;

bool InitStack(SqStack& S);	 //��ʼ��
bool StackEmpty(SqStack& S); //�ж�ջ��
bool Push(SqStack& S, ElemType e);	//��ջ
bool Pop(SqStack& S, ElemType& x);	//��ջ

//��ʼ��
bool InitStack(SqStack& S) {
	S.top = -1;//��ʼ��ջ��ָ��
	return true;
}

//�ж�ջ��
bool StackEmpty(SqStack& S) {
	if (S.top == -1)
		return true;
	else
		return false;
}
//��ջ
bool Push(SqStack& S, ElemType e) {
	//ջ��
	if (S.top == MAXSIZE - 1)
		return false;
	S.data[++S.top] = e;
	return true;
}
//��ջ
bool Pop(SqStack& S, ElemType &x) {
	//ջ��
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
	//��ջ
	Push(S, 1);
	Push(S, 2);
	Push(S, 3);
	Push(S, 4);
	//��ս
	Pop(S, x);
	printf("%d\n", x);

	Print(S);
	return 0;
}
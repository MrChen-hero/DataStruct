#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct LSNode {
	ElemType data;
	struct LSNode* next;
}LSNode, *LiStack;

bool InitStack(LiStack& S);	//初始化
bool Print(LiStack& S);		//打印
bool Push(LiStack& S, ElemType e);	//入栈
bool Pop(LiStack& S, ElemType& e);	//出栈


//初始化
bool InitStack(LiStack& S) {
	S = NULL;
	return true;
}

//打印
bool Print(LiStack& S) {
	LSNode* top = S;
	while (top != NULL) {
		printf("%d ", top->data);
		top = top->next;
	}
	return true;
}

//入栈(使用头插法)
bool Push(LiStack& S, ElemType e) {
	LSNode* node = (LSNode*)malloc(sizeof(LSNode));
	if (node == NULL)
		return false;
	node->data = e;
	node->next = S;
	S = node;

	return true;
}

//出栈
bool Pop(LiStack& S, ElemType& e) {
	if (S == NULL)
		return false;
	LSNode* temp = S;
	e = S->data;
	S = S->next;
	free(temp);

	return true;
}

int main() {
	LiStack S;
	ElemType e;
	InitStack(S);
	Push(S, 1);
	Push(S, 2);
	Push(S, 3);
	Push(S, 4);

	Pop(S, e);
	Print(S);
	return 0;
}
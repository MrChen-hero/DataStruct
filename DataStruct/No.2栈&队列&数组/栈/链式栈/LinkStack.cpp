#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct LSNode {
	ElemType data;
	struct LSNode* next;
}LSNode, *LiStack;

bool InitStack(LiStack& S);	//��ʼ��
bool Print(LiStack& S);		//��ӡ
bool Push(LiStack& S, ElemType e);	//��ջ
bool Pop(LiStack& S, ElemType& e);	//��ջ


//��ʼ��
bool InitStack(LiStack& S) {
	S = NULL;
	return true;
}

//��ӡ
bool Print(LiStack& S) {
	LSNode* top = S;
	while (top != NULL) {
		printf("%d ", top->data);
		top = top->next;
	}
	return true;
}

//��ջ(ʹ��ͷ�巨)
bool Push(LiStack& S, ElemType e) {
	LSNode* node = (LSNode*)malloc(sizeof(LSNode));
	if (node == NULL)
		return false;
	node->data = e;
	node->next = S;
	S = node;

	return true;
}

//��ջ
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
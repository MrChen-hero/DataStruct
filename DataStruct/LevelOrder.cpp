#include <stdio.h>
#include <stdlib.h>
#include <queue>

typedef char ElemType;

typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

bool CreateBiTree(BiTree& T);

//����һ�ö�������Լ���û�����ǰ������ķ�ʽ��������
//ABDECFG
bool CreateBiTree(BiTree& T) {
	char c;
	scanf_s("%c", &c, 1);

	if (' ' == c)
	{
		T = NULL;
	}
	else
	{
		T = (BiTNode*)malloc(sizeof(BiTNode));
		if (T == NULL)
			return false;
		T->data = c;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}

	return true;
}
void visit(char c, int level)
{
	printf("%c λ�ڵ� %d ��\n", c, level);
}
//����һ�ö�������Լ���û�����ǰ������ķ�ʽ��������
//ABD  E  CF  G  
// ��α���������
void LevelOrderTraverse(BiTree T, int level)
{
	std::queue <BiTree> Q;
	BiTree temp = NULL;
	int next_level = level;  // ʹ��һ�������ı�����������һ���㼶
	Q.push(T);
	while (!Q.empty()) {
		int current_level = next_level;  // ʹ��ǰһ���㼶����һ�㼶��Ϊ��ǰ�㼶
		next_level = current_level + 1;  // �����ӽڵ����һ�㼶
		int level_nodes_count = Q.size();  // ������ǰ�㼶�Ľڵ�
		for (int i = 0; i < level_nodes_count; i++) {
			temp = Q.front();
			Q.pop();
			visit(temp->data, current_level);
			if (temp->lchild != NULL) {
				Q.push(temp->lchild);
			}
			if (temp->rchild != NULL) {
				Q.push(temp->rchild);
			}
		}
	}
}

int main()
{
	BiTree T;
	CreateBiTree(T);
	LevelOrderTraverse(T, 1);
	return 0;
}
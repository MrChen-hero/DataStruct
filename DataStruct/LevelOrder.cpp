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

//创建一棵二叉树，约定用户遵照前序遍历的方式输入数据
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
	printf("%c 位于第 %d 层\n", c, level);
}
//创建一棵二叉树，约定用户遵照前序遍历的方式输入数据
//ABD  E  CF  G  
// 层次遍历二叉树
void LevelOrderTraverse(BiTree T, int level)
{
	std::queue <BiTree> Q;
	BiTree temp = NULL;
	int next_level = level;  // 使用一个单独的变量来跟踪下一个层级
	Q.push(T);
	while (!Q.empty()) {
		int current_level = next_level;  // 使用前一个层级的下一层级作为当前层级
		next_level = current_level + 1;  // 更新子节点的下一层级
		int level_nodes_count = Q.size();  // 计数当前层级的节点
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
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100 // 树中最多结点数

typedef char TElemType; // 树结点的数据类型

// 孩子兄弟表示法
typedef struct CSNode
{
    TElemType data; // 数据域
    struct CSNode* firstchild, * nextsibling; // 指向第一个孩子和右兄弟的指针
} CSNode, * CSTree;

// 树结点
typedef struct TreeNode
{
    TElemType data; // 数据域
    struct TreeNode* firstchild, * rightsibling; // 指向第一个孩子和右兄弟的指针
} TreeNode, * Tree;

// 森林
typedef struct ForestNode
{
    Tree tree; // 指向树的指针
    struct ForestNode* next; // 指向下一个森林结点的指针
} ForestNode, * Forest;

// 创建树
void CreateTree(Tree* T)
{
    TElemType ch;
    scanf_s("%c", &ch,1);
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (Tree)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        CreateTree(&((*T)->firstchild));
        CreateTree(&((*T)->rightsibling));
    }
}

// 先序遍历
void PreOrderTraverse(Tree T)
{
    if (T)
    {
        printf("%c ", T->data);
        PreOrderTraverse(T->firstchild);
        PreOrderTraverse(T->rightsibling);
    }
}

// 中序遍历
void InOrderTraverse(Tree T)
{
    if (T)
    {
        InOrderTraverse(T->firstchild);
        printf("%c ", T->data);
        InOrderTraverse(T->rightsibling);
    }
}

int main()
{
    Forest forest = NULL; // 初始化森林为空
    int n; // 树的个数
    printf("请输入森林中树的个数：");
    scanf_s("%d", &n);
    getchar(); // 读取换行符
    for (int i = 1; i <= n; i++)
    {
        printf("请输入第%d棵树的结点，用#表示空结点：\n", i);
        Tree T;
        CreateTree(&T);
        getchar(); // 读取换行符
        ForestNode* node = (ForestNode*)malloc(sizeof(ForestNode)); // 创建一个新的森林结点
        node->tree = T; // 将树的指针赋值给森林结点
        node->next = NULL; // 将森林结点的next指针初始化为NULL
        if (forest == NULL) // 如果森林为空，将森林结点作为森林的头部
        {
            forest = node;
        }
        else // 否则，将森林结点插入到森林的尾部
        {
            ForestNode* p = forest;
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = node;
        }
    }//BEK#L##F###   CG###  DHM##I#J###
    printf("森林的先序遍历结果为：");
    for (ForestNode* p = forest; p != NULL; p = p->next)
    {
        PreOrderTraverse(p->tree);
    }
    printf("\n森林的中序遍历结果为：");
    for (ForestNode* p = forest; p != NULL; p = p->next)
    {
        InOrderTraverse(p->tree);
    }
    printf("\n");
    return 0;
}
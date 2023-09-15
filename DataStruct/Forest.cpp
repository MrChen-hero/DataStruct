#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100 // �����������

typedef char TElemType; // ��������������

// �����ֵܱ�ʾ��
typedef struct CSNode
{
    TElemType data; // ������
    struct CSNode* firstchild, * nextsibling; // ָ���һ�����Ӻ����ֵܵ�ָ��
} CSNode, * CSTree;

// �����
typedef struct TreeNode
{
    TElemType data; // ������
    struct TreeNode* firstchild, * rightsibling; // ָ���һ�����Ӻ����ֵܵ�ָ��
} TreeNode, * Tree;

// ɭ��
typedef struct ForestNode
{
    Tree tree; // ָ������ָ��
    struct ForestNode* next; // ָ����һ��ɭ�ֽ���ָ��
} ForestNode, * Forest;

// ������
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

// �������
void PreOrderTraverse(Tree T)
{
    if (T)
    {
        printf("%c ", T->data);
        PreOrderTraverse(T->firstchild);
        PreOrderTraverse(T->rightsibling);
    }
}

// �������
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
    Forest forest = NULL; // ��ʼ��ɭ��Ϊ��
    int n; // ���ĸ���
    printf("������ɭ�������ĸ�����");
    scanf_s("%d", &n);
    getchar(); // ��ȡ���з�
    for (int i = 1; i <= n; i++)
    {
        printf("�������%d�����Ľ�㣬��#��ʾ�ս�㣺\n", i);
        Tree T;
        CreateTree(&T);
        getchar(); // ��ȡ���з�
        ForestNode* node = (ForestNode*)malloc(sizeof(ForestNode)); // ����һ���µ�ɭ�ֽ��
        node->tree = T; // ������ָ�븳ֵ��ɭ�ֽ��
        node->next = NULL; // ��ɭ�ֽ���nextָ���ʼ��ΪNULL
        if (forest == NULL) // ���ɭ��Ϊ�գ���ɭ�ֽ����Ϊɭ�ֵ�ͷ��
        {
            forest = node;
        }
        else // ���򣬽�ɭ�ֽ����뵽ɭ�ֵ�β��
        {
            ForestNode* p = forest;
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = node;
        }
    }//BEK#L##F###   CG###  DHM##I#J###
    printf("ɭ�ֵ�����������Ϊ��");
    for (ForestNode* p = forest; p != NULL; p = p->next)
    {
        PreOrderTraverse(p->tree);
    }
    printf("\nɭ�ֵ�����������Ϊ��");
    for (ForestNode* p = forest; p != NULL; p = p->next)
    {
        InOrderTraverse(p->tree);
    }
    printf("\n");
    return 0;
}
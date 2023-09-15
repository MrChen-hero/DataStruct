/*								���ĳ�������
*	���Ķ�--���ڵ�Ķȵ����ֵ				m����--ÿ���ڵ����ֻ����m�����ӵ���
*	��Ϊm����								m����
*	������Ķ�<= m(���m������)			����ڵ�Ķ�<= m(���m������)
*	������һ������= m(��m������)			�������нڵ�Ķȶ�< m
*	һ���Ƿǿ�����������m+1�����			�����ǿ���
* 
*	��Ϊm������i��������m��i-1�η������
*	�߶�Ϊh��m���������� (m��h�η�-1)/(m-1)����㣺�ȱ��������
*	�߶�Ϊh��m����������h�����
*	�߶�Ϊh����Ϊm����������h+m-1�����
*	��n������m��������С�߶�Ϊ[logm(n(m-1)+1)]
* 
*								���Ĵ洢�ṹ
*	˫�ױ�ʾ����ÿ���ڵ��б���ָ��˫�׵�ָ��
*	���ӱ�ʾ��
*	�����ֵܱ�ʾ�������Ͷ�������ת��
*	ɭ�ֺͶ�������ת��
*	
*								����ɭ�ֵı���
*	����
*	�ȸ��������ȷ��ʸ��ڵ㣬�����ζ�ÿ���������ȸ����� == ת������������������
*	����������ȶ�ÿ������������������ʸ��ڵ� == ת������������������ --> ������ȱ���
*	��α���������ʵ��  --> ������ȱ���
* 
*   ɭ�֣�
*   �������ɭ�� == ��ÿ�����ȸ����� == ���������������
*   �������ɭ�� == ��ÿ����������� == ���������������
*   
*/

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

// ������
void CreateTree(CSTree* T)
{
    TElemType ch;
    scanf_s("%c", &ch,1);
    if (ch == ' ')
    {
        *T = NULL;
    }
    else
    {
        *T = (CSTree)malloc(sizeof(CSNode));
        if (T == NULL)
            return;
        (*T)->data = ch;
        CreateTree(&((*T)->firstchild));
        CreateTree(&((*T)->nextsibling));
    }
}//ABEK##F##CG##DH#I#J####

// �ȸ�����
void PreOrderTraverse(CSTree T)
{
    if (T)
    {
        printf("%c ", T->data);
        PreOrderTraverse(T->firstchild);
        PreOrderTraverse(T->nextsibling);
    }
}

// �������
void PostOrderTraverse(CSTree T)
{
    if (T)
    {
        PostOrderTraverse(T->firstchild);
        printf("%c ", T->data);
        PostOrderTraverse(T->nextsibling);
    }
}

// ��α���
void LevelOrderTraverse(CSTree T)
{
    CSTree queue[MAX_TREE_SIZE]; // �������
    int front = 0, rear = 0; // �����ͷ�Ͷ�βָ��
    if (T)
    {
        queue[rear++] = T; // ��������
        while (front != rear) // ���в�Ϊ��ʱѭ��
        {
            CSTree p = queue[front++]; // ����
            printf("%c ", p->data); // ���ʽ��
            if (p->firstchild) // ����к��ӽ�㣬�������
            {
                queue[rear++] = p->firstchild;
            }
            if (p->nextsibling) // ������ֵܽ�㣬�������
            {
                queue[rear++] = p->nextsibling;
            }
        }
    }
}

int main()
{
    CSTree T;
    printf("���������Ľ�㣬��' '��ʾ�ս�㣺\n");
    CreateTree(&T);
    printf("�ȸ��������Ϊ��");
    PreOrderTraverse(T);
    printf("\n����������Ϊ��");
    PostOrderTraverse(T);
    printf("\n��α������Ϊ��");
    LevelOrderTraverse(T);
    printf("\n");
    return 0;
}
/*								树的常考性质
*	树的度--各节点的度的最大值				m叉树--每个节点最多只能有m个孩子的树
*	度为m的树								m叉树
*	任意结点的度<= m(最多m个孩子)			任意节点的度<= m(最多m个孩子)
*	至少有一个结点度= m(有m个孩子)			允许所有节点的度都< m
*	一定是非空树，至少有m+1个结点			可以是空树
* 
*	度为m的树第i层至多有m的i-1次方个结点
*	高度为h的m叉树至多有 (m的h次方-1)/(m-1)个结点：等比数列求和
*	高度为h的m叉树至少有h个结点
*	高度为h、度为m的树至少有h+m-1个结点
*	有n个结点的m叉树的最小高度为[logm(n(m-1)+1)]
* 
*								树的存储结构
*	双亲表示法：每个节点中保存指向双亲的指针
*	孩子表示法
*	孩子兄弟表示法：数和二叉树的转化
*	森林和二叉树的转换
*	
*								树和森林的遍历
*	树：
*	先根遍历：先访问根节点，再依次对每棵树进行先根遍历 == 转化后二叉树的先序遍历
*	后根遍历：先对每棵树后根遍历，最后访问根节点 == 转化后二叉树的中序遍历 --> 深度优先遍历
*	层次遍历：队列实现  --> 广度优先遍历
* 
*   森林：
*   先序遍历森林 == 对每棵树先根遍历 == 二叉树的先序遍历
*   中序遍历森林 == 对每棵树后根遍历 == 二叉树的中序遍历
*   
*/

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

// 创建树
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

// 先根遍历
void PreOrderTraverse(CSTree T)
{
    if (T)
    {
        printf("%c ", T->data);
        PreOrderTraverse(T->firstchild);
        PreOrderTraverse(T->nextsibling);
    }
}

// 后根遍历
void PostOrderTraverse(CSTree T)
{
    if (T)
    {
        PostOrderTraverse(T->firstchild);
        printf("%c ", T->data);
        PostOrderTraverse(T->nextsibling);
    }
}

// 层次遍历
void LevelOrderTraverse(CSTree T)
{
    CSTree queue[MAX_TREE_SIZE]; // 定义队列
    int front = 0, rear = 0; // 定义队头和队尾指针
    if (T)
    {
        queue[rear++] = T; // 根结点入队
        while (front != rear) // 队列不为空时循环
        {
            CSTree p = queue[front++]; // 出队
            printf("%c ", p->data); // 访问结点
            if (p->firstchild) // 如果有孩子结点，将其入队
            {
                queue[rear++] = p->firstchild;
            }
            if (p->nextsibling) // 如果有兄弟结点，将其入队
            {
                queue[rear++] = p->nextsibling;
            }
        }
    }
}

int main()
{
    CSTree T;
    printf("请输入树的结点，用' '表示空结点：\n");
    CreateTree(&T);
    printf("先根遍历结果为：");
    PreOrderTraverse(T);
    printf("\n后根遍历结果为：");
    PostOrderTraverse(T);
    printf("\n层次遍历结果为：");
    LevelOrderTraverse(T);
    printf("\n");
    return 0;
}
/*ͼG(V,E),V���㼯��E�߼�
* -���ж����Ϊ2|E|
* -GΪ��ͨͼ�����ٱ�Ϊn-1
* -GΪ����ͨͼ�������(n-1)(n-2)/2����
* 
* GΪ����ͼ
*-G�����=����=|E|
*-���ж�֮�� = 2|E|
*-GΪǿ��ͨͼ�����ٱ�Ϊn
*-������ȫͼ��n(n-1)/2����
* 
*/
#include <stdio.h>
#include <stdlib.h>

#define MaxVexNum 10
/********************�ڽӾ���*********************/
//�Ǵ�Ȩͼ
typedef enum { NoLink, Link }LinkTag;
typedef struct MGraph {
	char Vex[MaxVexNum];
	LinkTag Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}MGraph;

//��Ȩͼ
typedef struct WGraph {
	char Vex[MaxVexNum];
	int Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}WGraph;

/********************�ڽӱ�*********************/
//�߽��
typedef struct AdjNode {
	char adjVex;
	struct AdjNode* next;
	//int weight;	//Ȩֵ
}AdjNode;
//���㼯
typedef struct VNode {
	char Vex;
	AdjNode* fristEdg;	//��һ����
}VNode, AdjList[MaxVexNum];
//�ڽӱ�
typedef struct ALGraph {
	AdjList adjList;
	int Vexnum, Edgenum;
}ALGraph;


/********************ʮ������*********************/
//�߽��
typedef struct AcrNode {
	char headVex, tailVex;	//��ͷ���㣬��β����
	struct AcrNode* headLink, * tailLink;	//���ӻ�ͷ��ͬ����һ���������ӻ�β��ͬ����һ����
	//int weight;	//Ȩֵ
}AcrNode;
//���㼯
typedef struct VexNode {
	char Vex;
	AcrNode* headFrist, * tailFirst;	//��Ϊ��ͷ�ĵ�һ���ߣ���Ϊ��β�ĵ�һ����
}VexNode, AcrList[MaxVexNum];
//ʮ������
typedef struct AcrGraph {
	AcrList acrossLinker;
	int Vexnum, Edgenum;
}AcrGraph;

/********************�ڽӶ��ر�*********************/
//�߽��
typedef struct MAdjNode {
	char i, j;
	struct MAdjNode* iLink, * jLink;	//������i���ıߣ�������j���ı�
	//int weight;
}MAdjNode;
//���㼯
typedef struct Vertex {
	char Vex;
	MAdjNode* frist;
}Vertex, MAdjList[MaxVexNum];
//ͼ
typedef struct MAdjGraph {
	MAdjList madjList;
	int Vexnum, Edgenum;
}MAdjGraph;

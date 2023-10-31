/*图G(V,E),V顶点集，E边集
* -所有顶点度为2|E|
* -G为连通图，最少边为n-1
* -G为非连通图，最多有(n-1)(n-2)/2条边
* 
* G为有向图
*-G的入度=出度=|E|
*-所有度之和 = 2|E|
*-G为强连通图，最少边为n
*-有向完全图有n(n-1)/2条边
* 
*/
#include <stdio.h>
#include <stdlib.h>

#define MaxVexNum 10
/********************邻接矩阵*********************/
//非带权图
typedef enum { NoLink, Link }LinkTag;
typedef struct MGraph {
	char Vex[MaxVexNum];
	LinkTag Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}MGraph;

//带权图
typedef struct WGraph {
	char Vex[MaxVexNum];
	int Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}WGraph;

/********************邻接表*********************/
//边结点
typedef struct AdjNode {
	char adjVex;
	struct AdjNode* next;
	//int weight;	//权值
}AdjNode;
//顶点集
typedef struct VNode {
	char Vex;
	AdjNode* fristEdg;	//第一条边
}VNode, AdjList[MaxVexNum];
//邻接表
typedef struct ALGraph {
	AdjList adjList;
	int Vexnum, Edgenum;
}ALGraph;


/********************十字链表*********************/
//边结点
typedef struct AcrNode {
	char headVex, tailVex;	//弧头顶点，弧尾顶点
	struct AcrNode* headLink, * tailLink;	//连接弧头相同的下一条弧，连接弧尾相同的下一条弧
	//int weight;	//权值
}AcrNode;
//顶点集
typedef struct VexNode {
	char Vex;
	AcrNode* headFrist, * tailFirst;	//作为弧头的第一条边，作为弧尾的第一条边
}VexNode, AcrList[MaxVexNum];
//十字链表
typedef struct AcrGraph {
	AcrList acrossLinker;
	int Vexnum, Edgenum;
}AcrGraph;

/********************邻接多重表*********************/
//边结点
typedef struct MAdjNode {
	char i, j;
	struct MAdjNode* iLink, * jLink;	//依附于i结点的边，依附于j结点的边
	//int weight;
}MAdjNode;
//顶点集
typedef struct Vertex {
	char Vex;
	MAdjNode* frist;
}Vertex, MAdjList[MaxVexNum];
//图
typedef struct MAdjGraph {
	MAdjList madjList;
	int Vexnum, Edgenum;
}MAdjGraph;

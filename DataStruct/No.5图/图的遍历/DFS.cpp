/*************深度优先遍历：递归实现，函数调用栈*************/
#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10
/**************************邻接矩阵***************************/
//非带权图
typedef enum { NoLink, Link }LinkTag;
typedef struct MGraph {
	char Vex[MaxVexNum];
	LinkTag Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}MGraph;

void InitMGraph(MGraph* G);
void CreateMGraph(MGraph* G);
int FirstNeighbor_MGraph(MGraph G, int v);
int NextNeighbor_MGraph(MGraph G, int v, int w);
void DFS(MGraph G, int v, bool* visited);
void DFSTraverse(MGraph G);

/*初始化*/
void InitMGraph(MGraph* G) {
	G->Edgenum = G->Vexnum = 0;
	for (int i = 0; i < MaxVexNum; i++) {
		G->Vex[i] = '\0';
		for (int j = 0; j < MaxVexNum; j++) {
			G->Edge[i][j] = NoLink;
		}
	}
	CreateMGraph(G);
}
/*输入无向图*/
void CreateMGraph(MGraph* G) {
	cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
	cin >> G->Vexnum;
	cin >> G->Edgenum;
	//初始化结点命名
	for (int i = 0; i < G->Vexnum; i++) {
		G->Vex[i] = i + '1';
	}
	cout << "Enter the Edge of Vex[v] and vex[w]:" << endl;
	int v, w;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w;
		G->Edge[v-1][w-1] = Link;
		G->Edge[w-1][v-1] = Link;
	}
}
//寻找第一个邻接顶点
int FirstNeighbor_MGraph(MGraph G, int v) {
	for (int i = 0; i < G.Vexnum; i++) {
		if (G.Edge[v][i] == Link) {
			return i;	//返回第一个邻接顶点的序号
		}
	}
	return -1;	//无邻接顶点时返回 -1
}
//寻找接下来的邻接顶点
int NextNeighbor_MGraph(MGraph G, int v, int w) {
	for (int i = w + 1; i < G.Vexnum; i++) {
		if (G.Edge[v][i] == Link) {
			return i; //返回邻接顶点的序号
		}
	}
	return -1;  //无邻接顶点时返回 -1
}
//广度优先遍历
void DFSTraverse(MGraph G) {
	bool visited[MaxVexNum];
	for (int i = 0; i < G.Vexnum; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < G.Vexnum; i++) {
		if (visited[i] == false) {
			DFS(G, i,visited);
		}
	}
}
void DFS(MGraph G, int v, bool* visited) {
	cout << v+1 << " ";	//访问结点
	visited[v] = true;	//标记v结点已访问
	for (int w = FirstNeighbor_MGraph(G, v); w >= 0; w = NextNeighbor_MGraph(G, v, w)) {
		//依次找到所有邻接结点,递归访问结点，树的先根遍历
		if (!visited[w]) {
			//w结点未被访问
			DFS(G, w, visited);
		}
	}
}

void PrintMGraph(MGraph G) {
	for (int i = 0; i < G.Vexnum; i++) {
		for (int j = 0; j < G.Vexnum; j++) {
			cout << G.Edge[i][j] << "\t";
		}
		cout << "\n";
	}
}
/**************************邻接表***************************/
//边结点
typedef struct AdjNode {
	int adjVex;
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

void InitALGraph(ALGraph* G);
void CreateALGraph(ALGraph* G);
int FirstNeighbor_ALGraph(ALGraph G, int v);
int NextNeighbor_ALGraph(ALGraph G, int v, int w);
void DFS_ALGraph(ALGraph G, int v, bool* visited);
void DFSTraverse_ALGraph(ALGraph G);

void InitALGraph(ALGraph* G) {
	G->Vexnum = 0;
	G->Edgenum = 0;
	for (int i = 0; i < MaxVexNum; i++) {
		G->adjList[i].Vex = '\0';
		G->adjList[i].fristEdg = nullptr;
	}
	CreateALGraph(G);
}
void CreateALGraph(ALGraph* G) {
	cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
	cin >> G->Vexnum;
	cin >> G->Edgenum;
	//初始化结点命名
	for (int i = 0; i < G->Vexnum; i++) {
		G->adjList[i].Vex = i + '1';
	}
	cout << "Enter the Edge of Vex[v] and vex[w]:" << endl;
	int v, w;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w;

		AdjNode* newEdge_v = new AdjNode;
		//头插法插入边集
		newEdge_v->adjVex = w - 1;
		newEdge_v->next = G->adjList[v - 1].fristEdg;
		G->adjList[v - 1].fristEdg = newEdge_v;

		//无向图对应节点插入
		AdjNode* newEdge_w = new AdjNode;
		newEdge_w->adjVex = v - 1;
		newEdge_w->next = G->adjList[w - 1].fristEdg;
		G->adjList[w - 1].fristEdg = newEdge_w;
	}
}
int FirstNeighbor_ALGraph(ALGraph G, int v) {
	AdjNode* p = G.adjList[v].fristEdg;
	if (p) {
		return p->adjVex;
	}
	else
	{
		return -1;
	}
}
int NextNeighbor_ALGraph(ALGraph G, int v, int w) {
	AdjNode* p = G.adjList[v].fristEdg;
	while (p) {
		if (p->adjVex == w && p->next != nullptr) {
			return p->next->adjVex;
		}
		p = p->next;
	}
	return -1;
}
//邻接表的广度优先遍历
void DFSTraverse_ALGraph(ALGraph G) {
	bool visited[MaxVexNum];
	for (int i = 0; i < G.Vexnum; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < G.Vexnum; i++) {
		if (visited[i] == false) {
			DFS_ALGraph(G, i, visited);
		}
	}
}
void DFS_ALGraph(ALGraph G, int v, bool* visited) {
	cout << v + 1 << " ";
	visited[v] = true;
	for (int w = FirstNeighbor_ALGraph(G, v); w >= 0; w = NextNeighbor_ALGraph(G, v, w)) {
		if (!visited[w]) {
			DFS_ALGraph(G, w, visited);
		}
	}
}

void PrintALGraph(ALGraph G) {
	for (int i = 0; i < G.Vexnum; i++) {
		cout << G.adjList[i].Vex << " -> ";
		AdjNode* p = G.adjList[i].fristEdg;
		while (p) {
			cout << G.adjList[p->adjVex].Vex << " ";
			p = p->next;
		}
		cout << endl;
	}
}

/****************************************/
int main() {
	MGraph MG;
	InitMGraph(&MG);
	PrintMGraph(MG);
	DFSTraverse(MG);

	/*ALGraph ALG;
	InitALGraph(&ALG);
	PrintALGraph(ALG);
	DFSTraverse_ALGraph(ALG);*/
	return 0;
}
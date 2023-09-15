#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10

/******************************************邻接表实现**************************************************/
//边结点
typedef struct AdjNode {
	int adjVex;
	struct AdjNode* next;
	int weight;	//权值
	AdjNode(int adjVex, int weight) : adjVex(adjVex), weight(weight), next(nullptr) {} // 添加构造函数
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
void CountInDegree(ALGraph* G, int* indegree);
bool TopologicalSort(ALGraph* G);


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
		G->adjList[i].Vex = i + '0';
	}
	cout << "Enter the Edge of Vex[v] and vex[w] and weight:" << endl;
	int v, w, weight;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w >> weight;

		AdjNode* newEdge_v = new AdjNode(w, weight); // 使用构造函数创建边结点
		//头插法插入边集，有向图
		newEdge_v->next = G->adjList[v].fristEdg;
		G->adjList[v].fristEdg = newEdge_v;
	}
}
void PrintALGraph(ALGraph G) {
	for (int i = 0; i < G.Vexnum; i++) {
		cout << G.adjList[i].Vex << " -> ";
		AdjNode* p = G.adjList[i].fristEdg;
		while (p) {
			cout << G.adjList[p->adjVex].Vex << "(" << p->weight << ")" << " ";
			p = p->next;
		}
		cout << endl;
	}
}

// 计算每个顶点的入度
void CountInDegree(ALGraph* G, int* indegree) {
	for (int i = 0; i < G->Vexnum; i++) {
		indegree[i] = 0; // 初始化为0
	}
	for (int i = 0; i < G->Vexnum; i++) {
		AdjNode* p = G->adjList[i].fristEdg; // 遍历第i个顶点的邻接表
		while (p) {
			indegree[p->adjVex]++; // 将邻接顶点的入度加1
			p = p->next;
		}
	}
}

// 邻接表结构的拓扑排序算法
bool TopologicalSort(ALGraph* G) {
	int indegree[MaxVexNum]; // 存储每个顶点的入度
	CountInDegree(G, indegree); // 计算每个顶点的入度
	queue<int> Q; // 创建一个队列
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // 将入度为0的顶点入队
			Q.push(i);
		}
	}
	int count = 0; // 记录已经输出的顶点数
	while (!Q.empty()) {
		int v = Q.front(); // 取出队首元素
		Q.pop();
		cout << G->adjList[v].Vex << " "; // 输出顶点
		count++;
		AdjNode* p = G->adjList[v].fristEdg; // 遍历第v个顶点的邻接表
		while (p) {
			int w = p->adjVex; // 获取邻接顶点
			indegree[w]--; // 将邻接顶点的入度减1
			if (indegree[w] == 0) { // 如果邻接顶点的入度为0，将其入队
				Q.push(w);
			}
			p = p->next;
		}
	}
	if (count < G->Vexnum) { // 如果输出的顶点数小于总顶点数，说明有环存在
		return false;
	}
	else {
		return true;
	}
}

/*********************************************邻接矩阵实现**************************************************/
typedef struct WGraph {
	char Vex[MaxVexNum];
	int Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}WGraph;

void InitWGraph(WGraph* G);
void CreateWGraph(WGraph* G);
bool TopologicalSort_WGraph(WGraph* G);
void CountInDegree_WGraph(WGraph* G, int* indegree);


/*初始化*/
void InitWGraph(WGraph* G) {
	G->Edgenum = G->Vexnum = 0;
	for (int i = 0; i < MaxVexNum; i++) {
		G->Vex[i] = '\0';
		for (int j = 0; j < MaxVexNum; j++) {
			G->Edge[i][j] = INT32_MAX;
		}
		G->Edge[i][i] = 0;
	}
	CreateWGraph(G);
}
/*输入有向图*/
void CreateWGraph(WGraph* G) {
	cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
	cin >> G->Vexnum;
	cin >> G->Edgenum;
	//初始化结点命名
	for (int i = 0; i < G->Vexnum; i++) {
		G->Vex[i] = i + '0';
	}
	cout << "Enter the Edge of Vex[v] and vex[w] and weight:" << endl;
	int v, w, weight;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w >> weight;
		G->Edge[v][w] = weight;
	}
}

void PrintWGraph(WGraph G) {
	for (int i = 0; i < G.Vexnum; i++) {
		for (int j = 0; j < G.Vexnum; j++) {
			if (G.Edge[i][j] == INT32_MAX)
				cout << "∞" << "\t";
			else
				cout << G.Edge[i][j] << "\t";
		}
		cout << "\n";
	}
}

// 计算每个顶点的入度
void CountInDegree_WGraph(WGraph* G, int* indegree) {
	for (int i = 0; i < G->Vexnum; i++) {
		indegree[i] = 0; // 初始化为0
	}
	for (int i = 0; i < G->Vexnum; i++) {
		for (int j = 0; j < G->Vexnum; j++) {
			if (G->Edge[i][j] > 0 && G->Edge[i][j] < INT32_MAX) { // 如果存在边(i, j)
				indegree[j]++; // 将j顶点的入度加1
			}
		}
	}
}

// 邻接矩阵结构的拓扑排序算法
bool TopologicalSort_WGraph(WGraph* G) {
	int indegree[MaxVexNum]; // 存储每个顶点的入度
	CountInDegree_WGraph(G, indegree); // 计算每个顶点的入度
	queue<int> Q; // 创建一个队列
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // 将入度为0的顶点入队
			Q.push(i);
		}
	}
	int count = 0; // 记录已经输出的顶点数
	while (!Q.empty()) {
		int v = Q.front(); // 取出队首元素
		Q.pop();
		cout << G->Vex[v] << " "; // 输出顶点
		count++;
		for (int w = 0; w < G->Vexnum; w++) {
			if (G->Edge[v][w] != 0) { // 如果存在边(v, w)
				indegree[w]--; // 将w顶点的入度减1
				if (indegree[w] == 0) { // 如果w顶点的入度为0，将其入队
					Q.push(w);
				}
			}
		}
	}
	if (count < G->Vexnum) { // 如果输出的顶点数小于总顶点数，说明有环存在
		return false;
	}
	else {
		return true;
	}
}

int main() {
	WGraph WG;
	InitWGraph(&WG);
	PrintWGraph(WG);
	TopologicalSort_WGraph(&WG);

	//ALGraph ALG;
	//InitALGraph(&ALG);
	//PrintALGraph(ALG);
	//TopologicalSort(&ALG);
	return 0;
}
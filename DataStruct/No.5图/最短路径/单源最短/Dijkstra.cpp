/*Dijkstra: 每次遍历所在点与个点的距离，
找出距离最小的点，更新后以其作为当前点，
继续重复。 注：对负权值路径会失效*/

#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10

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
int FirstNeighbor_ALGraph(ALGraph G, int v);
int NextNeighbor_ALGraph(ALGraph G, int v, int w);
int GetWeight_ALGraph(ALGraph G, int v, int w); // 添加获取权重的函数

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

// 获取v和w之间的边的权重
int GetWeight_ALGraph(ALGraph G, int v, int w) {
	AdjNode* p = G.adjList[v].fristEdg;
	while (p) {
		if (p->adjVex == w) {
			return p->weight;
		}
		p = p->next;
	}
	return INT_MAX; // 如果没有找到边，返回无穷大
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

/*****************************Dijkstra******************************/
// 定义打印最短路径的函数
void printPath(int s, int t, int* prev) {
	// 如果s和t相同，打印s
	if (s == t) {
		cout << s << " ";
		return;
	}
	// 如果t没有前驱，说明不存在路径
	if (prev[t] == -1) {
		cout << "No path from " << s << " to " << t << endl;
		return;
	}
	// 递归打印前驱顶点和t
	printPath(s, prev[t], prev);
	cout << t << " ";
}
void Dijkstra(ALGraph G, int v) {
	bool final[MaxVexNum];
	int dist[MaxVexNum];
	int path[MaxVexNum];
	//初始化结点最短路径集合、距离与父结点的数组辅助
	for (int i = 0; i < MaxVexNum; i++) {
		final[i] = false;
		dist[i] = INT_MAX; 
		path[i] = -1;
	}
	final[v] = true;//首先将第一个节点v加入最短路径集合，S集合中只有一个元素V0
	dist[v] = 0;

	for (int e = FirstNeighbor_ALGraph(G, v); e >= 0; e = NextNeighbor_ALGraph(G, v, e)) {
		dist[e] = GetWeight_ALGraph(G, v, e); //使用GetWeight_ALGraph函数获取v和e之间的边的权重
		path[e] = v; //更新前驱节点
	}

	for (int i = 0; i < G.Vexnum; i++) { //遍历所有顶点
		int min = INT_MAX;
		int w = -1;
		for (int j = 0; j < G.Vexnum; j++) {
			if (!final[j] && dist[j] < min) {
				min = dist[j];
				w = j;// 找到未加入路径且权值最小的结点w
			}
		}
		if (w == -1) break; //说明剩下的结点与已加入的结点不连通
		//将节点w加入最短路径集合之前，检查w是否为-1，避免访问无效的数组下标
		final[w] = true;

		//更新w到各个结点的距离
		for (int e = FirstNeighbor_ALGraph(G, w); e >= 0; e = NextNeighbor_ALGraph(G, w, e)) {
			if (!final[e] && (min + GetWeight_ALGraph(G, w, e) < dist[e])) { //使用GetWeight_ALGraph函数获取w和e之间的边的权重
				dist[e] = min + GetWeight_ALGraph(G, w, e);
				path[e] = w;
			}
		}
	}

	// Print dist[]
	cout << "dist[]: ";
	for (int i = 0; i < G.Vexnum; i++) {
		cout << dist[i] << " ";
	}
	cout << endl;

	// Print path[]
	cout << "path[]: ";
	for (int i = 0; i < G.Vexnum; i++) {
		cout << path[i] << " ";
	}
	cout << endl;

	// Print the shortest path from v to each vertex
	cout << "The shortest path from " << v << " to each vertex is:" << endl;
	for (int i = 0; i < G.Vexnum; i++) {
		if (i == v) continue; // skip the source vertex itself
		cout << v << " to " << i << ": ";
		printPath(v, i, path); // use the printPath function to print the vertex sequence
		cout << endl;
	}
}


int main() {
	ALGraph ALG;
	InitALGraph(&ALG);
	PrintALGraph(ALG);
	Dijkstra(ALG, 0);
	return 0;
}

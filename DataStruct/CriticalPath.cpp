#include <iostream>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

const int MaxVexNum = 10; // 最大顶点数

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

// 定义一个结构体，用于存储每个顶点的最早发生时间和最迟发生时间
typedef struct Event{
	int ve; // 最早发生时间
	int vl; // 最迟发生时间
}Event;

// 定义一个结构体，用于存储每条边的最早开始时间，最迟开始时间和时间余量
typedef struct Activity{
	int e; // 最早开始时间
	int l; // 最迟开始时间
	int d; // 时间余量
}Activity;

void InitALGraph(ALGraph* G);
void CreateALGraph(ALGraph* G);
void CountInDegree(ALGraph* G, int* indegree);
void CriticalPath(ALGraph* G);

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
/*
- 所有事件的最早发生时间ve[]：它是从源点到某个事件的最长路径长度，也就是该事件能够开始的最早时间。
							它可以通过拓扑排序求出，具体方法是：令ve[源点] = 0，然后按照拓扑序遍历每个事件，
							对于每个事件i，更新其所有后继事件j的ve值，使之等于max{ve[i] + w[i][j]}，其中w[i][j]是活动<i, j>的持续时间.

- 所有事件的最迟发生时间vl[]：它是在不推迟整个工程完成时间的前提下，该事件能够开始的最晚时间。
							它可以通过逆拓扑排序求出，具体方法是：令vl[汇点] = ve[汇点]，然后按照逆拓扑序遍历每个事件，
							对于每个事件i，更新其所有前驱事件j的vl值，使之等于min{vl[i] - w[j][i]}。

- 所有活动的最早发生时间e[]：它是该活动能够开始的最早时间，也就是该活动的起始事件的最早发生时间。
							它可以通过ve[]求出，具体方法是：对于每个活动<i, j>，令e[i][j] = ve[i]。

- 所有活动的最迟发生时间l[]：它是该活动能够开始的最晚时间，也就是该活动的终止事件的最迟发生时间减去该活动的持续时间。
							它可以通过vl[]求出，具体方法是：对于每个活动<i, j>，令l[i][j] = vl[j] - w[i][j]。

- 所有活动的时间余量d[]：它是该活动能够推迟的时间，也就是该活动的最迟发生时间减去该活动的最早发生时间。
						它可以通过e[]和l[]求出，具体方法是：对于每个活动<i, j>，令d[i][j] = l[i][j] - e[i][j]。
*/
// 求AOE网的关键路径算法
void CriticalPath(ALGraph* G) {
	int indegree[MaxVexNum]; // 存储每个顶点的入度
	CountInDegree(G, indegree); // 计算每个顶点的入度
	queue<int> Q; // 创建一个队列
	Event events[MaxVexNum]; // 存储每个事件的最早发生时间和最迟发生时间
	Activity activities[MaxVexNum][MaxVexNum]; // 存储每个活动的最早开始时间，最迟开始时间和时间余量

	// 初始化事件数组和活动数组
	for (int i = 0; i < G->Vexnum; i++) {
		events[i].ve = 0; // 最早发生时间初始化为0
		events[i].vl = INT_MAX; // 最迟发生时间初始化为无穷大
		for (int j = 0; j < G->Vexnum; j++) {
			activities[i][j].e = 0; // 最早开始时间初始化为0
			activities[i][j].l = INT_MAX; // 最迟开始时间初始化为无穷大
			activities[i][j].d = INT_MAX; // 时间余量初始化为无穷大
		}
	}

	// 拓扑排序，求出每个事件的最早发生时间ve[]
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // 将入度为0的顶点入队
			Q.push(i);
		}
	}
	while (!Q.empty()) {
		int v = Q.front(); // 取出队首元素
		Q.pop();
		AdjNode* p = G->adjList[v].fristEdg; // 遍历第v个顶点的邻接表
		while (p) {
			int w = p->adjVex; // 获取邻接顶点
			indegree[w]--; // 将邻接顶点的入度减1
			if (indegree[w] == 0) { // 如果邻接顶点的入度为0，将其入队
				Q.push(w);
			}
			if (events[v].ve + p->weight > events[w].ve) { // 如果存在更大的最早发生时间，更新邻接顶点的最早发生时间
				events[w].ve = events[v].ve + p->weight;
			}
			p = p->next;
		}
	}

	// 求出整个工程的完成时间，即所有事件中最大的最早发生时间，并将其赋值给所有事件的最迟发生时间vl[]
	int maxTime = 0;
	for (int i = 0; i < G->Vexnum; i++) {
		if (events[i].ve > maxTime) {
			maxTime = events[i].ve;
		}
	}
	for (int i = 0; i < G->Vexnum; i++) {
		events[i].vl = maxTime;
	}

	// 逆拓扑排序，求出每个事件的最迟发生时间vl[]
	stack<int> S; // 创建一个栈，用于存储逆拓扑序列
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // 将入度为0的顶点入栈
			S.push(i);
		}
	}
	while (!S.empty()) {
		int v = S.top(); // 取出栈顶元素
		S.pop();
		AdjNode* p = G->adjList[v].fristEdg; // 遍历第v个顶点的邻接表
		while (p) {
			int w = p->adjVex; // 获取邻接顶点
			if (events[w].vl - p->weight < events[v].vl) { // 如果存在更小的最迟发生时间，更新当前顶点的最迟发生时间
				events[v].vl = events[w].vl - p->weight;
			}
			p = p->next;
		}
	}

	// 求出每条边的最早开始时间e[]，最迟开始时间l[]和时间余量d[]
	for (int i = 0; i < G->Vexnum; i++) {
		AdjNode* p = G->adjList[i].fristEdg; // 遍历第i个顶点的邻接表
		while (p) {
			int j = p->adjVex; // 获取邻接顶点
			activities[i][j].e = events[i].ve; // 最早开始时间等于起始事件的最早发生时间
			activities[i][j].l = events[j].vl - p->weight; // 最迟开始时间等于终止事件的最迟发生时间减去活动持续时间
			activities[i][j].d = activities[i][j].l - activities[i][j].e; // 时间余量等于最迟开始时间减去最早开始时间
			p = p->next;
		}
	}

	// 输出每个事件的最早发生时间ve[]和最迟发生时间vl[]
	cout << "每个事件的最早发生时间和最迟发生时间如下：" << endl;
	for (int i = 0; i < G->Vexnum; i++) {
		cout << "事件" << G->adjList[i].Vex << ": ve=" << events[i].ve << ", vl=" << events[i].vl << endl;
	}

	// 输出每条边的最早开始时间e[]，最迟开始时间l[]和时间余量d[]
	cout << "每条边的最早开始时间，最迟开始时间和时间余量如下：" << endl;
	for (int i = 0; i < G->Vexnum; i++) {
		for (int j = 0; j < G->Vexnum; j++) {
			if (activities[i][j].d != INT_MAX) { // 如果存在边(i, j)
				cout << "边" << G->adjList[i].Vex << "->" << G->adjList[j].Vex << ": e=" << activities[i][j].e << ", l=" << activities[i][j].l << ", d=" << activities[i][j].d << endl;
				if (activities[i][j].d == 0) { // 如果时间余量为0，说明是关键活动
					cout << "这是一条关键活动！" << endl;
				}
			}
		}
	}
}

int main() {
	ALGraph ALG;
	InitALGraph(&ALG);
	PrintALGraph(ALG);
	CriticalPath(&ALG);

	return 0;
}
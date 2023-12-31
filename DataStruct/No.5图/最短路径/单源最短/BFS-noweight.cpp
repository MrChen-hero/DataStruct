#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10

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
void BFS_noweight(MGraph G, int v, bool* visited);
void BFSTraverse(MGraph G);
void PrintShortestPath(MGraph G, int* dist, int* path);


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
		G->Edge[v - 1][w - 1] = Link;
		G->Edge[w - 1][v - 1] = Link;
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
void BFSTraverse(MGraph G) {
	bool visited[MaxVexNum];
	for (int i = 0; i < G.Vexnum; i++) {
		visited[i] = false;
	}
	for (int i = 1; i < G.Vexnum; i++) {
		if (visited[i] == false) {
			BFS_noweight(G, i, visited);
		}
	}
}
void BFS_noweight(MGraph G, int v, bool* visited) {
	visited[v] = true;	//标记v结点已访问
	int dist[MaxVexNum];	//记录源点到其他顶点最短路径距离
	int path[MaxVexNum];	//记录最短路径路线
	for (int i = 0; i < G.Vexnum; i++) {
		dist[i] = INT32_MAX;
		path[i] = -1;
	}	//初始化

	queue<int> Q;
	Q.push(v);	//v结点入队
	dist[v] = 0;
	while (!Q.empty())
	{
		int cur = Q.front();	//记录队首结点
		Q.pop();
		for (int w = FirstNeighbor_MGraph(G, cur); w >= 0; w = NextNeighbor_MGraph(G, cur, w)) {
			//依次找到所有邻接结点,无邻接结点时返回-1，结束循环，cur结点更新为队首结点继续遍历
			if (!visited[w]) {
				//w结点未被访问
				dist[w] = dist[cur] + 1;	//距离等于当前的父节点距离加一
				path[w] = cur + 1;
				visited[w] = true;
				Q.push(w);
			}
		}
	}

	PrintShortestPath(G, dist, path);
}

void PrintShortestPath(MGraph G,int* dist, int *path) {
	for (int i = 0; i < G.Vexnum; i++) {
		cout << dist[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < G.Vexnum; i++) {
		cout << path[i] << " ";
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

int main() {
	MGraph MG;
	InitMGraph(&MG);
	PrintMGraph(MG);
	BFSTraverse(MG);

	return 0;
}


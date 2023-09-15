/*从某一顶点开始，每次将最小代价顶点加入生成树，直到全部顶点都纳入*/
#include<iostream>
using namespace std;

#define MaxVexNum 10
/*********************************邻接矩阵实现*************************************/
//带权图
typedef struct WGraph {
	char Vex[MaxVexNum];
	int Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}WGraph;

void InitWGraph(WGraph* G);
void CreateWGraph(WGraph* G);
/*初始化*/
void InitWGraph(WGraph* G) {
	G->Edgenum = G->Vexnum = 0;
	for (int i = 0; i < MaxVexNum; i++) {
		G->Vex[i] = '\0';
		for (int j = 0; j < MaxVexNum; j++) {
			G->Edge[i][j] = INT32_MAX;
		}
	}
	CreateWGraph(G);
}
/*输入无向图*/
void CreateWGraph(WGraph* G) {
	cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
	cin >> G->Vexnum;
	cin >> G->Edgenum;
	//初始化结点命名
	for (int i = 0; i < G->Vexnum; i++) {
		G->Vex[i] = i + '1';
	}
	cout << "Enter the Edge of Vex[v] and vex[w] and weight:" << endl;
	int v, w, weight;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w >> weight;
		G->Edge[v - 1][w - 1] = weight;
		G->Edge[w - 1][v - 1] = weight;
	}
}
//记录顶点代价集合
typedef struct Vertex_Array {
	int start;
	int end;
	int weight;
}VexArray;
void Prim(WGraph WG,int begin) {
	Vertex_Array* lowcost = new VexArray[WG.Vexnum];
	int sum = 0;
	//初始化最小代价集合，记录从起点出发到各边的权值
	for (int i = 0; i < WG.Vexnum; i++) {
		lowcost[i].start = begin - 1;
		lowcost[i].end = i;
		lowcost[i].weight = WG.Edge[begin - 1][i];
	}
	//将起点结点权值设为-1，表示已经加入最小代价集合
	lowcost[begin - 1].weight = -1;
	//访问剩下的结点
	for (int i = 1; i < WG.Vexnum; i++) {
		int mincost = INT32_MAX;
		int node = -1;
		for (int k = 0; k < WG.Vexnum; k++) {
			if (lowcost[k].weight != -1 && lowcost[k].weight < mincost) {
				//不断找到与结点相连中权值最小的结点
				mincost = lowcost[k].weight;
				node = k;
			}
		}
		lowcost[node].weight = -1;	//将最小代价结点加入集合
		cout << WG.Vex[lowcost[node].start]
			<< "--"
			<< WG.Vex[lowcost[node].end]
			<< "="
			<< WG.Edge[lowcost[node].start][lowcost[node].end]
			<< endl;
		sum += WG.Edge[lowcost[node].start][lowcost[node].end];
		//更新lowcost数组
		for (int j = 0; j < WG.Vexnum; j++) {
			if (WG.Edge[lowcost[node].end][j] < lowcost[j].weight) {
				lowcost[j].weight = WG.Edge[lowcost[node].end][j];
				lowcost[j].start = lowcost[node].end;
				lowcost[j].end = j;
			}
		}
	}
	cout << sum << endl;
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

/*****************************邻接表*********************************/
//边结点
typedef struct AdjNode {
	int adjVex;
	struct AdjNode* next;
	int weight;	//权值
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
	cout << "Enter the Edge of Vex[v] and vex[w] and weight:" << endl;
	int v, w, weight;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w >> weight;

		AdjNode* newEdge_v = new AdjNode;
		//头插法插入边集
		newEdge_v->adjVex = w - 1;
		newEdge_v->weight = weight;
		newEdge_v->next = G->adjList[v - 1].fristEdg;
		G->adjList[v - 1].fristEdg = newEdge_v;

		//无向图对应节点插入
		AdjNode* newEdge_w = new AdjNode;
		newEdge_w->adjVex = v - 1;
		newEdge_w->weight = weight;
		newEdge_w->next = G->adjList[w - 1].fristEdg;
		G->adjList[w - 1].fristEdg = newEdge_w;
	}
}
void Prim_2(ALGraph G, int begin) {
	Vertex_Array* lowcost = new VexArray[G.Vexnum];
	int sum = 0;
	//初始化最小代价集合，记录从起点出发到各边的权值
	for (int i = 0; i < G.Vexnum; i++) {
		lowcost[i].weight = INT32_MAX;
	}
	AdjNode* arc = G.adjList[begin - 1].fristEdg;
	while (arc) {
		lowcost[arc->adjVex].start = begin - 1;
		lowcost[arc->adjVex].end = arc->adjVex;
		lowcost[arc->adjVex].weight = arc->weight;
		arc = arc->next;
	}
	lowcost[begin - 1].weight = -1;	//起始结点已经加入最低代价
	//处理剩下的结点
	for (int i = 1; i < G.Vexnum; i++) {
		int min = INT32_MAX;
		int index;
		//寻找数组lowcost中权重最小的那个边
		for (int k = 0; k < G.Vexnum; k++) {
			if (lowcost[k].weight != -1) {
				if (lowcost[k].weight < min) {
					min = lowcost[k].weight;
					index = k;
				}
			}
		}
		//输出对应的边的信息
		cout << G.adjList[lowcost[index].start].Vex
			<< "-----"
			<< G.adjList[lowcost[index].end].Vex
			<< "="
			<< lowcost[index].weight
			<< endl;
		//将权重最小的那条边的终点也加入到集合U
		lowcost[index].weight = -1;
		//更新我们的close_edge数组。            
		AdjNode* temp = G.adjList[lowcost[index].end].fristEdg;
		while (temp) {
			if (lowcost[temp->adjVex].weight > temp->weight) {
				lowcost[temp->adjVex].weight = temp->weight;
				lowcost[temp->adjVex].start = index;
				lowcost[temp->adjVex].end = temp->adjVex;
			}
			temp = temp->next;
		}
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
/***************************************************************************/

int main() {
	//WGraph WG;
	//InitWGraph(&WG);
	//PrintWGraph(WG);
	//Prim(WG, 4);

	ALGraph ALG;
	InitALGraph(&ALG);
	PrintALGraph(ALG);
	Prim_2(ALG, 4);

	return 0;
}
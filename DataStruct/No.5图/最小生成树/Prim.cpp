/*��ĳһ���㿪ʼ��ÿ�ν���С���۶��������������ֱ��ȫ�����㶼����*/
#include<iostream>
using namespace std;

#define MaxVexNum 10
/*********************************�ڽӾ���ʵ��*************************************/
//��Ȩͼ
typedef struct WGraph {
	char Vex[MaxVexNum];
	int Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}WGraph;

void InitWGraph(WGraph* G);
void CreateWGraph(WGraph* G);
/*��ʼ��*/
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
/*��������ͼ*/
void CreateWGraph(WGraph* G) {
	cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
	cin >> G->Vexnum;
	cin >> G->Edgenum;
	//��ʼ���������
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
//��¼������ۼ���
typedef struct Vertex_Array {
	int start;
	int end;
	int weight;
}VexArray;
void Prim(WGraph WG,int begin) {
	Vertex_Array* lowcost = new VexArray[WG.Vexnum];
	int sum = 0;
	//��ʼ����С���ۼ��ϣ���¼�������������ߵ�Ȩֵ
	for (int i = 0; i < WG.Vexnum; i++) {
		lowcost[i].start = begin - 1;
		lowcost[i].end = i;
		lowcost[i].weight = WG.Edge[begin - 1][i];
	}
	//�������Ȩֵ��Ϊ-1����ʾ�Ѿ�������С���ۼ���
	lowcost[begin - 1].weight = -1;
	//����ʣ�µĽ��
	for (int i = 1; i < WG.Vexnum; i++) {
		int mincost = INT32_MAX;
		int node = -1;
		for (int k = 0; k < WG.Vexnum; k++) {
			if (lowcost[k].weight != -1 && lowcost[k].weight < mincost) {
				//�����ҵ�����������Ȩֵ��С�Ľ��
				mincost = lowcost[k].weight;
				node = k;
			}
		}
		lowcost[node].weight = -1;	//����С���۽����뼯��
		cout << WG.Vex[lowcost[node].start]
			<< "--"
			<< WG.Vex[lowcost[node].end]
			<< "="
			<< WG.Edge[lowcost[node].start][lowcost[node].end]
			<< endl;
		sum += WG.Edge[lowcost[node].start][lowcost[node].end];
		//����lowcost����
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
				cout << "��" << "\t";
			else
				cout << G.Edge[i][j] << "\t";
		}
		cout << "\n";
	}
}

/*****************************�ڽӱ�*********************************/
//�߽��
typedef struct AdjNode {
	int adjVex;
	struct AdjNode* next;
	int weight;	//Ȩֵ
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
	//��ʼ���������
	for (int i = 0; i < G->Vexnum; i++) {
		G->adjList[i].Vex = i + '1';
	}
	cout << "Enter the Edge of Vex[v] and vex[w] and weight:" << endl;
	int v, w, weight;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w >> weight;

		AdjNode* newEdge_v = new AdjNode;
		//ͷ�巨����߼�
		newEdge_v->adjVex = w - 1;
		newEdge_v->weight = weight;
		newEdge_v->next = G->adjList[v - 1].fristEdg;
		G->adjList[v - 1].fristEdg = newEdge_v;

		//����ͼ��Ӧ�ڵ����
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
	//��ʼ����С���ۼ��ϣ���¼�������������ߵ�Ȩֵ
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
	lowcost[begin - 1].weight = -1;	//��ʼ����Ѿ�������ʹ���
	//����ʣ�µĽ��
	for (int i = 1; i < G.Vexnum; i++) {
		int min = INT32_MAX;
		int index;
		//Ѱ������lowcost��Ȩ����С���Ǹ���
		for (int k = 0; k < G.Vexnum; k++) {
			if (lowcost[k].weight != -1) {
				if (lowcost[k].weight < min) {
					min = lowcost[k].weight;
					index = k;
				}
			}
		}
		//�����Ӧ�ıߵ���Ϣ
		cout << G.adjList[lowcost[index].start].Vex
			<< "-----"
			<< G.adjList[lowcost[index].end].Vex
			<< "="
			<< lowcost[index].weight
			<< endl;
		//��Ȩ����С�������ߵ��յ�Ҳ���뵽����U
		lowcost[index].weight = -1;
		//�������ǵ�close_edge���顣            
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
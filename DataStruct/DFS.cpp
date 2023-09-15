/*************������ȱ������ݹ�ʵ�֣���������ջ*************/
#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10
/**************************�ڽӾ���***************************/
//�Ǵ�Ȩͼ
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

/*��ʼ��*/
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
/*��������ͼ*/
void CreateMGraph(MGraph* G) {
	cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
	cin >> G->Vexnum;
	cin >> G->Edgenum;
	//��ʼ���������
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
//Ѱ�ҵ�һ���ڽӶ���
int FirstNeighbor_MGraph(MGraph G, int v) {
	for (int i = 0; i < G.Vexnum; i++) {
		if (G.Edge[v][i] == Link) {
			return i;	//���ص�һ���ڽӶ�������
		}
	}
	return -1;	//���ڽӶ���ʱ���� -1
}
//Ѱ�ҽ��������ڽӶ���
int NextNeighbor_MGraph(MGraph G, int v, int w) {
	for (int i = w + 1; i < G.Vexnum; i++) {
		if (G.Edge[v][i] == Link) {
			return i; //�����ڽӶ�������
		}
	}
	return -1;  //���ڽӶ���ʱ���� -1
}
//������ȱ���
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
	cout << v+1 << " ";	//���ʽ��
	visited[v] = true;	//���v����ѷ���
	for (int w = FirstNeighbor_MGraph(G, v); w >= 0; w = NextNeighbor_MGraph(G, v, w)) {
		//�����ҵ������ڽӽ��,�ݹ���ʽ�㣬�����ȸ�����
		if (!visited[w]) {
			//w���δ������
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
/**************************�ڽӱ�***************************/
//�߽��
typedef struct AdjNode {
	int adjVex;
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
	//��ʼ���������
	for (int i = 0; i < G->Vexnum; i++) {
		G->adjList[i].Vex = i + '1';
	}
	cout << "Enter the Edge of Vex[v] and vex[w]:" << endl;
	int v, w;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w;

		AdjNode* newEdge_v = new AdjNode;
		//ͷ�巨����߼�
		newEdge_v->adjVex = w - 1;
		newEdge_v->next = G->adjList[v - 1].fristEdg;
		G->adjList[v - 1].fristEdg = newEdge_v;

		//����ͼ��Ӧ�ڵ����
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
//�ڽӱ�Ĺ�����ȱ���
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
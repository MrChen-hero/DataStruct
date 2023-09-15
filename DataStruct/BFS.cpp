/**********������ȱ���������**********/
#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10
/********************�ڽӾ���*********************/
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
void BFS(MGraph G, int v, bool* visited);
void BFSTraverse(MGraph G);

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
void BFSTraverse(MGraph G) {
	bool visited[MaxVexNum];
	for (int i = 0; i < G.Vexnum; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < G.Vexnum; i++) {
		if (visited[i] == false) {
			BFS(G, i,visited);
		}
	}
}
void BFS(MGraph G, int v, bool* visited) {
	cout << v+1 << " ";	//���ʽ��
	visited[v] = true;	//���v����ѷ���
	queue<int> Q;
	Q.push(v);	//v������
	while (!Q.empty())
	{
		int cur = Q.front();	//��¼���׽��
		Q.pop();
		for (int w = FirstNeighbor_MGraph(G, cur); w >= 0; w = NextNeighbor_MGraph(G, cur, w)) {
			//�����ҵ������ڽӽ��,���ڽӽ��ʱ����-1������ѭ����cur������Ϊ���׽���������
			if (!visited[w]) {
				//w���δ������
				cout << w+1 << " ";
				visited[w] = true;
				Q.push(w);
			}
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
/********************�ڽӱ�*********************/
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
void BFS_ALGraph(ALGraph G, int v, bool* visited);
void BFSTraverse_ALGraph(ALGraph G);

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
void BFSTraverse_ALGraph(ALGraph G) {
	bool visited[MaxVexNum];
	for (int i = 0; i < G.Vexnum; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < G.Vexnum; i++) {
		if (visited[i] == false) {
			BFS_ALGraph(G, i, visited);
		}
	}
}
void BFS_ALGraph(ALGraph G, int v, bool* visited) {
	queue<int> Q;
	cout << v + 1 << " ";
	visited[v] = true;
	Q.push(v);
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		for (int w = FirstNeighbor_ALGraph(G, cur); w >= 0; w = NextNeighbor_ALGraph(G, cur, w)) {
			if (!visited[w]) {
				cout << w + 1 << " ";
				visited[w] = true;
				Q.push(w);
			}
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
	//MGraph MG;
	//InitMGraph(&MG);
	//PrintMGraph(MG);
	//BFSTraverse(MG);

	ALGraph ALG;
	InitALGraph(&ALG);
	PrintALGraph(ALG);
	BFSTraverse_ALGraph(ALG);
	return 0;
}
#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10

/******************************************�ڽӱ�ʵ��**************************************************/
//�߽��
typedef struct AdjNode {
	int adjVex;
	struct AdjNode* next;
	int weight;	//Ȩֵ
	AdjNode(int adjVex, int weight) : adjVex(adjVex), weight(weight), next(nullptr) {} // ��ӹ��캯��
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
	//��ʼ���������
	for (int i = 0; i < G->Vexnum; i++) {
		G->adjList[i].Vex = i + '0';
	}
	cout << "Enter the Edge of Vex[v] and vex[w] and weight:" << endl;
	int v, w, weight;
	for (int i = 0; i < G->Edgenum; i++) {
		cout << "Enter Edge " << i + 1 << ": ";
		cin >> v >> w >> weight;

		AdjNode* newEdge_v = new AdjNode(w, weight); // ʹ�ù��캯�������߽��
		//ͷ�巨����߼�������ͼ
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

// ����ÿ����������
void CountInDegree(ALGraph* G, int* indegree) {
	for (int i = 0; i < G->Vexnum; i++) {
		indegree[i] = 0; // ��ʼ��Ϊ0
	}
	for (int i = 0; i < G->Vexnum; i++) {
		AdjNode* p = G->adjList[i].fristEdg; // ������i��������ڽӱ�
		while (p) {
			indegree[p->adjVex]++; // ���ڽӶ������ȼ�1
			p = p->next;
		}
	}
}

// �ڽӱ�ṹ�����������㷨
bool TopologicalSort(ALGraph* G) {
	int indegree[MaxVexNum]; // �洢ÿ����������
	CountInDegree(G, indegree); // ����ÿ����������
	queue<int> Q; // ����һ������
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // �����Ϊ0�Ķ������
			Q.push(i);
		}
	}
	int count = 0; // ��¼�Ѿ�����Ķ�����
	while (!Q.empty()) {
		int v = Q.front(); // ȡ������Ԫ��
		Q.pop();
		cout << G->adjList[v].Vex << " "; // �������
		count++;
		AdjNode* p = G->adjList[v].fristEdg; // ������v��������ڽӱ�
		while (p) {
			int w = p->adjVex; // ��ȡ�ڽӶ���
			indegree[w]--; // ���ڽӶ������ȼ�1
			if (indegree[w] == 0) { // ����ڽӶ�������Ϊ0���������
				Q.push(w);
			}
			p = p->next;
		}
	}
	if (count < G->Vexnum) { // �������Ķ�����С���ܶ�������˵���л�����
		return false;
	}
	else {
		return true;
	}
}

/*********************************************�ڽӾ���ʵ��**************************************************/
typedef struct WGraph {
	char Vex[MaxVexNum];
	int Edge[MaxVexNum][MaxVexNum];
	int Vexnum, Edgenum;
}WGraph;

void InitWGraph(WGraph* G);
void CreateWGraph(WGraph* G);
bool TopologicalSort_WGraph(WGraph* G);
void CountInDegree_WGraph(WGraph* G, int* indegree);


/*��ʼ��*/
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
/*��������ͼ*/
void CreateWGraph(WGraph* G) {
	cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
	cin >> G->Vexnum;
	cin >> G->Edgenum;
	//��ʼ���������
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
				cout << "��" << "\t";
			else
				cout << G.Edge[i][j] << "\t";
		}
		cout << "\n";
	}
}

// ����ÿ����������
void CountInDegree_WGraph(WGraph* G, int* indegree) {
	for (int i = 0; i < G->Vexnum; i++) {
		indegree[i] = 0; // ��ʼ��Ϊ0
	}
	for (int i = 0; i < G->Vexnum; i++) {
		for (int j = 0; j < G->Vexnum; j++) {
			if (G->Edge[i][j] > 0 && G->Edge[i][j] < INT32_MAX) { // ������ڱ�(i, j)
				indegree[j]++; // ��j�������ȼ�1
			}
		}
	}
}

// �ڽӾ���ṹ�����������㷨
bool TopologicalSort_WGraph(WGraph* G) {
	int indegree[MaxVexNum]; // �洢ÿ����������
	CountInDegree_WGraph(G, indegree); // ����ÿ����������
	queue<int> Q; // ����һ������
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // �����Ϊ0�Ķ������
			Q.push(i);
		}
	}
	int count = 0; // ��¼�Ѿ�����Ķ�����
	while (!Q.empty()) {
		int v = Q.front(); // ȡ������Ԫ��
		Q.pop();
		cout << G->Vex[v] << " "; // �������
		count++;
		for (int w = 0; w < G->Vexnum; w++) {
			if (G->Edge[v][w] != 0) { // ������ڱ�(v, w)
				indegree[w]--; // ��w�������ȼ�1
				if (indegree[w] == 0) { // ���w��������Ϊ0���������
					Q.push(w);
				}
			}
		}
	}
	if (count < G->Vexnum) { // �������Ķ�����С���ܶ�������˵���л�����
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
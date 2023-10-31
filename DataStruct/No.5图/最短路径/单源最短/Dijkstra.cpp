/*Dijkstra: ÿ�α������ڵ������ľ��룬
�ҳ�������С�ĵ㣬���º�������Ϊ��ǰ�㣬
�����ظ��� ע���Ը�Ȩֵ·����ʧЧ*/

#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10

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
int FirstNeighbor_ALGraph(ALGraph G, int v);
int NextNeighbor_ALGraph(ALGraph G, int v, int w);
int GetWeight_ALGraph(ALGraph G, int v, int w); // ��ӻ�ȡȨ�صĺ���

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

// ��ȡv��w֮��ıߵ�Ȩ��
int GetWeight_ALGraph(ALGraph G, int v, int w) {
	AdjNode* p = G.adjList[v].fristEdg;
	while (p) {
		if (p->adjVex == w) {
			return p->weight;
		}
		p = p->next;
	}
	return INT_MAX; // ���û���ҵ��ߣ����������
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
// �����ӡ���·���ĺ���
void printPath(int s, int t, int* prev) {
	// ���s��t��ͬ����ӡs
	if (s == t) {
		cout << s << " ";
		return;
	}
	// ���tû��ǰ����˵��������·��
	if (prev[t] == -1) {
		cout << "No path from " << s << " to " << t << endl;
		return;
	}
	// �ݹ��ӡǰ�������t
	printPath(s, prev[t], prev);
	cout << t << " ";
}
void Dijkstra(ALGraph G, int v) {
	bool final[MaxVexNum];
	int dist[MaxVexNum];
	int path[MaxVexNum];
	//��ʼ��������·�����ϡ������븸�������鸨��
	for (int i = 0; i < MaxVexNum; i++) {
		final[i] = false;
		dist[i] = INT_MAX; 
		path[i] = -1;
	}
	final[v] = true;//���Ƚ���һ���ڵ�v�������·�����ϣ�S������ֻ��һ��Ԫ��V0
	dist[v] = 0;

	for (int e = FirstNeighbor_ALGraph(G, v); e >= 0; e = NextNeighbor_ALGraph(G, v, e)) {
		dist[e] = GetWeight_ALGraph(G, v, e); //ʹ��GetWeight_ALGraph������ȡv��e֮��ıߵ�Ȩ��
		path[e] = v; //����ǰ���ڵ�
	}

	for (int i = 0; i < G.Vexnum; i++) { //�������ж���
		int min = INT_MAX;
		int w = -1;
		for (int j = 0; j < G.Vexnum; j++) {
			if (!final[j] && dist[j] < min) {
				min = dist[j];
				w = j;// �ҵ�δ����·����Ȩֵ��С�Ľ��w
			}
		}
		if (w == -1) break; //˵��ʣ�µĽ�����Ѽ���Ľ�㲻��ͨ
		//���ڵ�w�������·������֮ǰ�����w�Ƿ�Ϊ-1�����������Ч�������±�
		final[w] = true;

		//����w���������ľ���
		for (int e = FirstNeighbor_ALGraph(G, w); e >= 0; e = NextNeighbor_ALGraph(G, w, e)) {
			if (!final[e] && (min + GetWeight_ALGraph(G, w, e) < dist[e])) { //ʹ��GetWeight_ALGraph������ȡw��e֮��ıߵ�Ȩ��
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

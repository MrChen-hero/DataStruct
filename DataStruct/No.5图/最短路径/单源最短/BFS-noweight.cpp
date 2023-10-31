#include<iostream>
#include<queue>
using namespace std;

#define MaxVexNum 10

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
void BFS_noweight(MGraph G, int v, bool* visited);
void BFSTraverse(MGraph G);
void PrintShortestPath(MGraph G, int* dist, int* path);


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
		G->Edge[v - 1][w - 1] = Link;
		G->Edge[w - 1][v - 1] = Link;
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
	for (int i = 1; i < G.Vexnum; i++) {
		if (visited[i] == false) {
			BFS_noweight(G, i, visited);
		}
	}
}
void BFS_noweight(MGraph G, int v, bool* visited) {
	visited[v] = true;	//���v����ѷ���
	int dist[MaxVexNum];	//��¼Դ�㵽�����������·������
	int path[MaxVexNum];	//��¼���·��·��
	for (int i = 0; i < G.Vexnum; i++) {
		dist[i] = INT32_MAX;
		path[i] = -1;
	}	//��ʼ��

	queue<int> Q;
	Q.push(v);	//v������
	dist[v] = 0;
	while (!Q.empty())
	{
		int cur = Q.front();	//��¼���׽��
		Q.pop();
		for (int w = FirstNeighbor_MGraph(G, cur); w >= 0; w = NextNeighbor_MGraph(G, cur, w)) {
			//�����ҵ������ڽӽ��,���ڽӽ��ʱ����-1������ѭ����cur������Ϊ���׽���������
			if (!visited[w]) {
				//w���δ������
				dist[w] = dist[cur] + 1;	//������ڵ�ǰ�ĸ��ڵ�����һ
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


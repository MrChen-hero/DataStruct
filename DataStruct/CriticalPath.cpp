#include <iostream>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

const int MaxVexNum = 10; // ��󶥵���

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

// ����һ���ṹ�壬���ڴ洢ÿ����������緢��ʱ�����ٷ���ʱ��
typedef struct Event{
	int ve; // ���緢��ʱ��
	int vl; // ��ٷ���ʱ��
}Event;

// ����һ���ṹ�壬���ڴ洢ÿ���ߵ����翪ʼʱ�䣬��ٿ�ʼʱ���ʱ������
typedef struct Activity{
	int e; // ���翪ʼʱ��
	int l; // ��ٿ�ʼʱ��
	int d; // ʱ������
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
/*
- �����¼������緢��ʱ��ve[]�����Ǵ�Դ�㵽ĳ���¼����·�����ȣ�Ҳ���Ǹ��¼��ܹ���ʼ������ʱ�䡣
							������ͨ������������������巽���ǣ���ve[Դ��] = 0��Ȼ�������������ÿ���¼���
							����ÿ���¼�i�����������к���¼�j��veֵ��ʹ֮����max{ve[i] + w[i][j]}������w[i][j]�ǻ<i, j>�ĳ���ʱ��.

- �����¼�����ٷ���ʱ��vl[]�������ڲ��Ƴ������������ʱ���ǰ���£����¼��ܹ���ʼ������ʱ�䡣
							������ͨ��������������������巽���ǣ���vl[���] = ve[���]��Ȼ���������������ÿ���¼���
							����ÿ���¼�i������������ǰ���¼�j��vlֵ��ʹ֮����min{vl[i] - w[j][i]}��

- ���л�����緢��ʱ��e[]�����Ǹû�ܹ���ʼ������ʱ�䣬Ҳ���Ǹû����ʼ�¼������緢��ʱ�䡣
							������ͨ��ve[]��������巽���ǣ�����ÿ���<i, j>����e[i][j] = ve[i]��

- ���л����ٷ���ʱ��l[]�����Ǹû�ܹ���ʼ������ʱ�䣬Ҳ���Ǹû����ֹ�¼�����ٷ���ʱ���ȥ�û�ĳ���ʱ�䡣
							������ͨ��vl[]��������巽���ǣ�����ÿ���<i, j>����l[i][j] = vl[j] - w[i][j]��

- ���л��ʱ������d[]�����Ǹû�ܹ��Ƴٵ�ʱ�䣬Ҳ���Ǹû����ٷ���ʱ���ȥ�û�����緢��ʱ�䡣
						������ͨ��e[]��l[]��������巽���ǣ�����ÿ���<i, j>����d[i][j] = l[i][j] - e[i][j]��
*/
// ��AOE���Ĺؼ�·���㷨
void CriticalPath(ALGraph* G) {
	int indegree[MaxVexNum]; // �洢ÿ����������
	CountInDegree(G, indegree); // ����ÿ����������
	queue<int> Q; // ����һ������
	Event events[MaxVexNum]; // �洢ÿ���¼������緢��ʱ�����ٷ���ʱ��
	Activity activities[MaxVexNum][MaxVexNum]; // �洢ÿ��������翪ʼʱ�䣬��ٿ�ʼʱ���ʱ������

	// ��ʼ���¼�����ͻ����
	for (int i = 0; i < G->Vexnum; i++) {
		events[i].ve = 0; // ���緢��ʱ���ʼ��Ϊ0
		events[i].vl = INT_MAX; // ��ٷ���ʱ���ʼ��Ϊ�����
		for (int j = 0; j < G->Vexnum; j++) {
			activities[i][j].e = 0; // ���翪ʼʱ���ʼ��Ϊ0
			activities[i][j].l = INT_MAX; // ��ٿ�ʼʱ���ʼ��Ϊ�����
			activities[i][j].d = INT_MAX; // ʱ��������ʼ��Ϊ�����
		}
	}

	// �����������ÿ���¼������緢��ʱ��ve[]
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // �����Ϊ0�Ķ������
			Q.push(i);
		}
	}
	while (!Q.empty()) {
		int v = Q.front(); // ȡ������Ԫ��
		Q.pop();
		AdjNode* p = G->adjList[v].fristEdg; // ������v��������ڽӱ�
		while (p) {
			int w = p->adjVex; // ��ȡ�ڽӶ���
			indegree[w]--; // ���ڽӶ������ȼ�1
			if (indegree[w] == 0) { // ����ڽӶ�������Ϊ0���������
				Q.push(w);
			}
			if (events[v].ve + p->weight > events[w].ve) { // ������ڸ�������緢��ʱ�䣬�����ڽӶ�������緢��ʱ��
				events[w].ve = events[v].ve + p->weight;
			}
			p = p->next;
		}
	}

	// ����������̵����ʱ�䣬�������¼����������緢��ʱ�䣬�����丳ֵ�������¼�����ٷ���ʱ��vl[]
	int maxTime = 0;
	for (int i = 0; i < G->Vexnum; i++) {
		if (events[i].ve > maxTime) {
			maxTime = events[i].ve;
		}
	}
	for (int i = 0; i < G->Vexnum; i++) {
		events[i].vl = maxTime;
	}

	// �������������ÿ���¼�����ٷ���ʱ��vl[]
	stack<int> S; // ����һ��ջ�����ڴ洢����������
	for (int i = 0; i < G->Vexnum; i++) {
		if (indegree[i] == 0) { // �����Ϊ0�Ķ�����ջ
			S.push(i);
		}
	}
	while (!S.empty()) {
		int v = S.top(); // ȡ��ջ��Ԫ��
		S.pop();
		AdjNode* p = G->adjList[v].fristEdg; // ������v��������ڽӱ�
		while (p) {
			int w = p->adjVex; // ��ȡ�ڽӶ���
			if (events[w].vl - p->weight < events[v].vl) { // ������ڸ�С����ٷ���ʱ�䣬���µ�ǰ�������ٷ���ʱ��
				events[v].vl = events[w].vl - p->weight;
			}
			p = p->next;
		}
	}

	// ���ÿ���ߵ����翪ʼʱ��e[]����ٿ�ʼʱ��l[]��ʱ������d[]
	for (int i = 0; i < G->Vexnum; i++) {
		AdjNode* p = G->adjList[i].fristEdg; // ������i��������ڽӱ�
		while (p) {
			int j = p->adjVex; // ��ȡ�ڽӶ���
			activities[i][j].e = events[i].ve; // ���翪ʼʱ�������ʼ�¼������緢��ʱ��
			activities[i][j].l = events[j].vl - p->weight; // ��ٿ�ʼʱ�������ֹ�¼�����ٷ���ʱ���ȥ�����ʱ��
			activities[i][j].d = activities[i][j].l - activities[i][j].e; // ʱ������������ٿ�ʼʱ���ȥ���翪ʼʱ��
			p = p->next;
		}
	}

	// ���ÿ���¼������緢��ʱ��ve[]����ٷ���ʱ��vl[]
	cout << "ÿ���¼������緢��ʱ�����ٷ���ʱ�����£�" << endl;
	for (int i = 0; i < G->Vexnum; i++) {
		cout << "�¼�" << G->adjList[i].Vex << ": ve=" << events[i].ve << ", vl=" << events[i].vl << endl;
	}

	// ���ÿ���ߵ����翪ʼʱ��e[]����ٿ�ʼʱ��l[]��ʱ������d[]
	cout << "ÿ���ߵ����翪ʼʱ�䣬��ٿ�ʼʱ���ʱ���������£�" << endl;
	for (int i = 0; i < G->Vexnum; i++) {
		for (int j = 0; j < G->Vexnum; j++) {
			if (activities[i][j].d != INT_MAX) { // ������ڱ�(i, j)
				cout << "��" << G->adjList[i].Vex << "->" << G->adjList[j].Vex << ": e=" << activities[i][j].e << ", l=" << activities[i][j].l << ", d=" << activities[i][j].d << endl;
				if (activities[i][j].d == 0) { // ���ʱ������Ϊ0��˵���ǹؼ��
					cout << "����һ���ؼ����" << endl;
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
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
void Floyd(WGraph* G, int D[][MaxVexNum], int P[][MaxVexNum]);
void PrintPath(WGraph* G, int P[][MaxVexNum], int i, int j);
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

/*Floyd�㷨������������������·��*/
void Floyd(WGraph* G, int D[][MaxVexNum], int P[][MaxVexNum]) {
    //��ʼ��D��P
    for (int i = 0; i < G->Vexnum; i++) {
        for (int j = 0; j < G->Vexnum; j++) {
            D[i][j] = G->Edge[i][j]; //DΪ�ڽӾ���
            P[i][j] = -1; //PΪǰ�����󣬳�ʼֵΪ-1
        }
    }
    //��̬�滮������D��P
    for (int k = 0; k < G->Vexnum; k++) { //kΪ�м���
        for (int i = 0; i < G->Vexnum; i++) { //iΪ��ʼ���
            for (int j = 0; j < G->Vexnum; j++) { //jΪ��ֹ���
                if (D[i][k] != INT32_MAX && D[k][j] != INT32_MAX && D[i][k] + D[k][j] < D[i][j]) { //�������k����·�����̣������D��P
                    D[i][j] = D[i][k] + D[k][j]; //������̾���
                    P[i][j] = k; //��¼ǰ�����
                }
            }
        }
    }
}

/*��ӡ���·��*/
void PrintPath(WGraph* G, int P[][MaxVexNum], int i, int j) {
    if (P[i][j] == -1) { //û���м��㣬ֱ�����
        cout << G->Vex[i] << "->" << G->Vex[j];
    }
    else { //���м��㣬�ݹ����
        int k = P[i][j]; //kΪ�м���
        PrintPath(G, P, i, k); //���i��k��·��
        cout << "->"; //�����ͷ
        PrintPath(G, P, k, j); //���k��j��·��
    }
}

int main() {
    WGraph WG;
    InitWGraph(&WG);
    PrintWGraph(WG);

    int D[MaxVexNum][MaxVexNum]; //DΪ��̾������
    int P[MaxVexNum][MaxVexNum]; //PΪǰ������
    Floyd(&WG, D, P); //����Floyd�㷨

    cout << "The shortest distance matrix is: " << endl;
    for (int i = 0; i < WG.Vexnum; i++) {
        for (int j = 0; j < WG.Vexnum; j++) {
            if (D[i][j] == INT32_MAX)
                cout << "��" << "\t";
            else
                cout << D[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "The shortest path matrix is: " << endl;
    for (int i = 0; i < WG.Vexnum; i++) {
        for (int j = 0; j < WG.Vexnum; j++) {
            if (P[i][j] == -1)
                cout << "-" << "\t";
            else
                cout << P[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "Enter the start and end vertex of the path: " << endl;
    int s, e;
    cin >> s >> e;
    cout << "The shortest path from " << s << " to " << e << " is: ";
    PrintPath(&WG, P, s, e);
    cout << endl;

    return 0;
}

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
void Floyd(WGraph* G, int D[][MaxVexNum], int P[][MaxVexNum]);
void PrintPath(WGraph* G, int P[][MaxVexNum], int i, int j);
/*初始化*/
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
/*输入有向图*/
void CreateWGraph(WGraph* G) {
    cout << "Enter the Vexnum and Edgenum of Graph: " << endl;
    cin >> G->Vexnum;
    cin >> G->Edgenum;
    //初始化结点命名
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
                cout << "∞" << "\t";
            else
                cout << G.Edge[i][j] << "\t";
        }
        cout << "\n";
    }
}

/*Floyd算法，求出任意两点间的最短路径*/
void Floyd(WGraph* G, int D[][MaxVexNum], int P[][MaxVexNum]) {
    //初始化D和P
    for (int i = 0; i < G->Vexnum; i++) {
        for (int j = 0; j < G->Vexnum; j++) {
            D[i][j] = G->Edge[i][j]; //D为邻接矩阵
            P[i][j] = -1; //P为前驱矩阵，初始值为-1
        }
    }
    //动态规划，更新D和P
    for (int k = 0; k < G->Vexnum; k++) { //k为中间结点
        for (int i = 0; i < G->Vexnum; i++) { //i为起始结点
            for (int j = 0; j < G->Vexnum; j++) { //j为终止结点
                if (D[i][k] != INT32_MAX && D[k][j] != INT32_MAX && D[i][k] + D[k][j] < D[i][j]) { //如果经过k结点的路径更短，则更新D和P
                    D[i][j] = D[i][k] + D[k][j]; //更新最短距离
                    P[i][j] = k; //记录前驱结点
                }
            }
        }
    }
}

/*打印最短路径*/
void PrintPath(WGraph* G, int P[][MaxVexNum], int i, int j) {
    if (P[i][j] == -1) { //没有中间结点，直接输出
        cout << G->Vex[i] << "->" << G->Vex[j];
    }
    else { //有中间结点，递归输出
        int k = P[i][j]; //k为中间结点
        PrintPath(G, P, i, k); //输出i到k的路径
        cout << "->"; //输出箭头
        PrintPath(G, P, k, j); //输出k到j的路径
    }
}

int main() {
    WGraph WG;
    InitWGraph(&WG);
    PrintWGraph(WG);

    int D[MaxVexNum][MaxVexNum]; //D为最短距离矩阵
    int P[MaxVexNum][MaxVexNum]; //P为前驱矩阵
    Floyd(&WG, D, P); //调用Floyd算法

    cout << "The shortest distance matrix is: " << endl;
    for (int i = 0; i < WG.Vexnum; i++) {
        for (int j = 0; j < WG.Vexnum; j++) {
            if (D[i][j] == INT32_MAX)
                cout << "∞" << "\t";
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

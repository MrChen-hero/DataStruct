/*Kruskal�㷨�����ڲ��鼯ʵ�֣�
ÿ�ν�������С�ı���δ��ͨ�ı߲��벢�鼯��
ֱ�����е���ͨ*/
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

//������������Ͷ�������ֵ�Ƿ���Ч�������Լ�����Ϊɶ��
//�������ͱ����Ĺ�ϵ�ǣ�((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 || ((Vexnum * (Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}

//�ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool check_edge(int Vexnum, int start, int end, int weight) {
    if (start<1 || end<1 || start>Vexnum || end>Vexnum || weight < 0) {
        return false;
    }
    return true;
}

//�߼��ṹ�����ڱ���ÿ���ߵ���Ϣ
typedef struct edge_tag {
    bool visit; //�ж��������Ƿ���뵽����С��������
    int start;   //�ñߵ����
    int end;   //�ñߵ��յ�
    int weight; //�ñߵ�Ȩ��
}Edge;

//����һ��ͼ������ͼ��ʹ�ñ߼��ṹ������
void createGraph(Edge*& e, int Vexnum, int edge) {
    e = new Edge[edge];//Ϊÿ���߼����ٿռ�
    int start = 0;
    int end = 0;
    int weight = 0;

    int i = 0;
    cout << "����ÿ���ߵ���㡢�յ��Ȩ�أ�" << endl;
    while (i != edge)
    {
        cin >> start >> end >> weight;
        while (!check_edge(Vexnum, start, end, weight)) {
            cout << "�����ֵ���Ϸ�������������ÿ���ߵ���㡢�յ��Ȩ�أ�" << endl;
            cin >> start >> end >> weight;
        }
        e[i].start = start;
        e[i].end = end;
        e[i].weight = weight;
        e[i].visit = false; //ÿ���߶���û����ʼ��
        ++i;

    }
}

//������Ҫ�Ա߼��������������ǰ���ÿ���ߵ�Ȩ�أ���С��������
int cmp(const void* first, const void* second) {
    return ((Edge*)first)->weight - ((Edge*)second)->weight;
}

//���ˣ�����������Ҫ������ͨ��һ���ķ�ʽ���ж�
//������ǰѵ�ǰ�ı߼��뵽���������Ƿ���л����֡�
//ͨ������֮ǰѧϰ����֪ʶ�����ǿ���֪������ܶ���������һ��ɭ�֣�����
//���ͬһ�������������������һ���ߣ���ô�ͻ���ֻ���
//�������Ǿ�ͨ�������ʽ���жϼ�����һ���µıߺ��Ƿ���������
//��ʼ���������ǵ�ͼ��ÿ�����㶼��һ�Ŷ���������ͨ�����ϵ���ϣ������ɭ�ֱ�
//����Դ��ͬһ�Ŷ������
//�������⣬����ͼ�������ˣ�

//�������Ҹ��ڵ�ĺ���,
//����parent���������������ĸ����
//child����ÿ�����㺢�ӽ��ĸ���
int find_root(int child, int* parent) {

    //��ʱ�Ѿ��ҵ��˸ö����������ĸ��ڵ���
    if (parent[child] == child) {
        return child;
    }
    //��ǰ�ݹ飬Ѱ�������׵����������ĸ����
    parent[child] = find_root(parent[child], parent);
    return parent[child];
}

//�ϲ���������
bool union_tree(Edge  e, int* parent, int* child) {
    //���ҳ��ı����������ĸ��ڵ�
    int root1;
    int root2;
    //��ס���Ƕ����1��ʼ�ģ�����Ҫ��1
    root1 = find_root(e.start - 1, parent);
    root2 = find_root(e.end - 1, parent);
    //ֻ���������㲻��ͬһ�������ϣ��ſ��԰���������δһ����
    if (root1 != root2) {
        //С���ϲ��������У������ǵĺ��Ӹ���
        if (child[root1] > child[root2]) {
            parent[root2] = root1;
            //�����ĺ���������С���ĺ�����������
            //�����ĺ��������ڼ���С�����ڵ��Լ�
            child[root1] += child[root2] + 1;
        }
        else {
            parent[root1] = root2;
            child[root2] += child[root1] + 1;
        }
        return true;
    }
    return false;
}

//��³˹���㷨��ʵ��
void Kruskal() {
    int Vexnum = 0;
    int edge = 0;
    cout << "������ͼ�Ķ������ͱ�����" << endl;
    cin >> Vexnum >> edge;
    while (!check(Vexnum, edge)) {
        cout << "�������ͼ�Ķ������ͱ������Ϸ������������룺" << endl;
        cin >> Vexnum >> edge;
    }

    //����һ���߼�����
    Edge* edge_tag;
    //����ÿ���ߵ���Ϣ
    createGraph(edge_tag, Vexnum, edge);

    int* parent = new int[Vexnum]; //��¼ÿ���������������ĸ��ڵ��±�
    int* child = new int[Vexnum]; //��¼ÿ������Ϊ���ڵ�ʱ�����еĺ��ӽڵ�ĸ���
    int i;
    for (i = 0; i < Vexnum; i++) {
        parent[i] = i;
        child[i] = 0;
    }
    //�Ա߼�����������򣬰���Ȩ�ش�С��������
    qsort(edge_tag, edge, sizeof(Edge), cmp);
    int count_vex; //��¼����ıߵ�����

    count_vex = i = 0;
    while (i != edge) {
        //������������������һ��˵���ñ�����������һ����
        if (union_tree(edge_tag[i], parent, child)) {
            cout << ("v" + std::to_string(edge_tag[i].start))
                << "-----"
                << ("v" + std::to_string(edge_tag[i].end))
                << "="
                << edge_tag[i].weight
                << endl;
            edge_tag[i].visit = true;
            ++count_vex; //�������ı߼�1
        }
        //�����ʾ���еı߶��Ѿ�����ɹ�
        if (count_vex == Vexnum - 1) {
            break;
        }
        ++i;
    }

    if (count_vex != Vexnum - 1) {
        cout << "��ͼΪ����ͨͼ���޷�������С��������" << endl;
    }
    delete[] edge_tag;
    delete[] parent;
    delete[] child;
}

int main() {
    Kruskal();
    system("pause");
    return 0;
}

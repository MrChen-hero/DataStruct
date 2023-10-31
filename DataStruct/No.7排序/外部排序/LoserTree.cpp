#include <iostream>
#include <vector>
#include <algorithm>

// �������ṹ
struct LoserTree {
    int k;                             // k·�鲢
    std::vector<std::vector<int>> data;// �鲢����
    std::vector<int> index;            // ����
    std::vector<int> loserTree;       // ������

    LoserTree(int k) : k(k), data(k, std::vector<int>(3)), index(k), loserTree(k) {}

    int minLeaf();

    void initialize();
    void adjust(int s);
    void kWayMerge();
};

// ��ȡ��СҶ�ӽڵ�
int LoserTree::minLeaf() {
    int minIndex = -1;
    int minValue = INT_MAX;

    for (int i = 0; i < k; ++i) {
        if (index[i] < data[i].size() && data[i][index[i]] < minValue) {
            minValue = data[i][index[i]];
            minIndex = i;
        }
    }

    return minIndex;
}

// ��ʼ��
void LoserTree::initialize() {
    std::fill(index.begin(), index.end(), 0);

    int minIndex = minLeaf();
    for (int i = 1; i < k; ++i) {
        adjust(minIndex);
        minIndex = minLeaf();
    }
}

// ����ʤ������
void LoserTree::adjust(int s) {
    int t = (s + k) / 2;

    while (t > 0) {
        if (s >= 0 && (loserTree[t] == -1 || data[s][index[s]] > data[loserTree[t]][index[loserTree[t]]])) {
            std::swap(s, loserTree[t]);
        }

        t /= 2;
    }

    loserTree[0] = s;
}

// k·�鲢
void LoserTree::kWayMerge() {
    for (int i = 0; i < k; i++) {
        std::sort(data[i].begin(), data[i].end());
    }
    initialize();

    while (loserTree[0] != -1) {
        int minValue = data[loserTree[0]][index[loserTree[0]]];
        std::cout << minValue << " ";
        index[loserTree[0]]++;

        if (index[loserTree[0]] >= data[loserTree[0]].size()) {
            loserTree[0] = -1;
        }

        adjust(loserTree[0]);
    }

    std::cout << std::endl;
}

// ������
int main() {
    LoserTree tree(4);
    std::vector<std::vector<int>> data = {
        {12, 6, 3},
        {45, 28, 9},
        {27, 47, 13},
        {55, 24, 19},
        {32, 16, 4},
        {29, 14, 7},
        {41, 2, 21},
        {26, 43, 38}
    };

    tree.data = data;

    tree.kWayMerge();

    std::cout << "�������ṹ: ";
    for (int i : tree.loserTree) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

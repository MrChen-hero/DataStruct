#include <iostream>
#include <vector>
#include <algorithm>

// 败者树结构
struct LoserTree {
    int k;                             // k路归并
    std::vector<std::vector<int>> data;// 归并数据
    std::vector<int> index;            // 索引
    std::vector<int> loserTree;       // 败者树

    LoserTree(int k) : k(k), data(k, std::vector<int>(3)), index(k), loserTree(k) {}

    int minLeaf();

    void initialize();
    void adjust(int s);
    void kWayMerge();
};

// 获取最小叶子节点
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

// 初始化
void LoserTree::initialize() {
    std::fill(index.begin(), index.end(), 0);

    int minIndex = minLeaf();
    for (int i = 1; i < k; ++i) {
        adjust(minIndex);
        minIndex = minLeaf();
    }
}

// 调整胜败者树
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

// k路归并
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

// 主函数
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

    std::cout << "败者树结构: ";
    for (int i : tree.loserTree) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

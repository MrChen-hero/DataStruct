#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 定义一个结点类
class Node {
public:
    int key; // 关键字
    double p; // 查找概率
    Node* left; // 左孩子
    Node* right; // 右孩子
    Node(int k, double pr) : key(k), p(pr), left(nullptr), right(nullptr) {} // 构造函数
};

// 自定义比较函数，按照关键字从小到大排序
bool compare(Node* a, Node* b) {
    return a->key < b->key;
}

// 递归构造查找判定树
Node* buildTree(vector<Node*>::iterator begin, vector<Node*>::iterator end) {
    if (begin == end) return nullptr;

    vector<Node*>::iterator mid = begin + (end - begin) / 2; // 中间结点
    Node* root = *mid; // 根结点

    root->left = buildTree(begin, mid); // 递归构建左子树
    root->right = buildTree(mid + 1, end); // 递归构建右子树

    return root; // 返回根结点
}

// 查找给定的关键字，返回是否找到、查找长度和查找路径
pair<bool, pair<int, string>> search(Node* root, int key) {
    int len = 0; // 查找长度
    string path = ""; // 查找路径
    Node* cur = root; // 当前结点

    while (cur != nullptr) {
        len++;
        if (cur->key == key) {
            return { true, {len, path} }; // 找到目标关键字，返回真、查找长度和查找路径
        }
        else if (key < cur->key) {
            cur = cur->left; // 向左走
            path += "L"; // 记录路径
        }
        else {
            cur = cur->right; // 向右走
            path += "R"; // 记录路径
        }
    }

    return { false, {len, path} }; // 没有找到目标关键字，返回假、查找长度和查找路径
}

int main() {
    vector<Node*> nodes; // 存储结点的数组
    nodes.push_back(new Node(12, 0.05));
    nodes.push_back(new Node(25, 0.1));
    nodes.push_back(new Node(16, 0.09));
    nodes.push_back(new Node(20, 0.08));
    nodes.push_back(new Node(18, 0.07));
    nodes.push_back(new Node(22, 0.06));

    sort(nodes.begin(), nodes.end(), compare); // 按照关键字排序

    Node* root = buildTree(nodes.begin(), nodes.end()); // 构造查找判定树

    cout << "Search for 16: " << endl;
    auto res1 = search(root, 16); // 查找16
    cout << "Found: " << res1.first << ", Length: " << res1.second.first << ", Path: " << res1.second.second << endl;

    cout << "Search for 23: " << endl;
    auto res2 = search(root, 23); // 查找23
    cout << "Found: " << res2.first << ", Length: " << res2.second.first << ", Path: " << res2.second.second << endl;

    return 0;
}

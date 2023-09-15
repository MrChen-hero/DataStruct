#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// �������������������ж�����
Node* buildTree(vector<int>::iterator begin, vector<int>::iterator end) {
    if (begin == end) return nullptr;

    vector<int>::iterator mid = begin + (end - begin) / 2;
    Node* root = new Node(*mid);

    root->left = buildTree(begin, mid);
    root->right = buildTree(mid + 1, end);

    return root;
}

// ���Ҳ����·��
pair<bool, string> search(Node* root, int key, string path = "") {
    if (root == nullptr) {
        return { false, path + " -> NULL" };
    }

    path += " -> " + to_string(root->key);

    if (root->key == key) {
        return { true, path };
    }
    else if (key < root->key) {
        return search(root->left, key, path);
    }
    else {
        return search(root->right, key, path);
    }
}

// ��ӡ���ṹ
void printTree(Node* root, string indent = "") {
    if (root == nullptr) {
        cout << indent << "NULL" << endl;
        return;
    }

    cout << indent << root->key << endl;
    indent += "  ";

    printTree(root->left, indent);
    printTree(root->right, indent);
}

int main() {
    vector<int> keys = { 12, 16, 18, 20, 22, 25 };

    // ����������������Ѿ�������ģ�������ǣ�����ʹ�� std::sort ��������
    // sort(keys.begin(), keys.end());

    Node* root = buildTree(keys.begin(), keys.end());

    cout << "Tree structure:" << endl;
    printTree(root);

    auto res1 = search(root, 16);
    cout << "Search for 16:" << endl;
    cout << "Found: " << res1.first << ", Path:" << res1.second << endl;

    auto res2 = search(root, 23);
    cout << "Search for 23:" << endl;
    cout << "Found: " << res2.first << ", Path:" << res2.second << endl;

    return 0;
}

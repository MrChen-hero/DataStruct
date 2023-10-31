#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ����һ�������
class Node {
public:
    int key; // �ؼ���
    double p; // ���Ҹ���
    Node* left; // ����
    Node* right; // �Һ���
    Node(int k, double pr) : key(k), p(pr), left(nullptr), right(nullptr) {} // ���캯��
};

// �Զ���ȽϺ��������չؼ��ִ�С��������
bool compare(Node* a, Node* b) {
    return a->key < b->key;
}

// �ݹ鹹������ж���
Node* buildTree(vector<Node*>::iterator begin, vector<Node*>::iterator end) {
    if (begin == end) return nullptr;

    vector<Node*>::iterator mid = begin + (end - begin) / 2; // �м���
    Node* root = *mid; // �����

    root->left = buildTree(begin, mid); // �ݹ鹹��������
    root->right = buildTree(mid + 1, end); // �ݹ鹹��������

    return root; // ���ظ����
}

// ���Ҹ����Ĺؼ��֣������Ƿ��ҵ������ҳ��ȺͲ���·��
pair<bool, pair<int, string>> search(Node* root, int key) {
    int len = 0; // ���ҳ���
    string path = ""; // ����·��
    Node* cur = root; // ��ǰ���

    while (cur != nullptr) {
        len++;
        if (cur->key == key) {
            return { true, {len, path} }; // �ҵ�Ŀ��ؼ��֣������桢���ҳ��ȺͲ���·��
        }
        else if (key < cur->key) {
            cur = cur->left; // ������
            path += "L"; // ��¼·��
        }
        else {
            cur = cur->right; // ������
            path += "R"; // ��¼·��
        }
    }

    return { false, {len, path} }; // û���ҵ�Ŀ��ؼ��֣����ؼ١����ҳ��ȺͲ���·��
}

int main() {
    vector<Node*> nodes; // �洢��������
    nodes.push_back(new Node(12, 0.05));
    nodes.push_back(new Node(25, 0.1));
    nodes.push_back(new Node(16, 0.09));
    nodes.push_back(new Node(20, 0.08));
    nodes.push_back(new Node(18, 0.07));
    nodes.push_back(new Node(22, 0.06));

    sort(nodes.begin(), nodes.end(), compare); // ���չؼ�������

    Node* root = buildTree(nodes.begin(), nodes.end()); // ��������ж���

    cout << "Search for 16: " << endl;
    auto res1 = search(root, 16); // ����16
    cout << "Found: " << res1.first << ", Length: " << res1.second.first << ", Path: " << res1.second.second << endl;

    cout << "Search for 23: " << endl;
    auto res2 = search(root, 23); // ����23
    cout << "Found: " << res2.first << ", Length: " << res2.second.first << ", Path: " << res2.second.second << endl;

    return 0;
}

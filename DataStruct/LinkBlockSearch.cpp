#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>

using namespace std;

// ����ڵ㶨��
struct Node {
    int value;
    Node* next;
};

// ˳�����������
int sequentialSearch(vector<int>& indexTable, int target) {
    for (int i = 0; i < indexTable.size(); ++i) {
        if (indexTable[i] >= target) {
            return i;
        }
    }
    return -1;
}

// ˳����������
Node* sequentialSearchInBlock(Node* head, int target) {
    Node* cur = head;
    while (cur) {
        if (cur->value == target) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

int main() {
    // ԭʼ����
    vector<int> arr = { 1, 3, 5, 8, 14, 18, 19, 21, 33, 37, 39, 41, 45, 49, 50 };
    int target = 19;

    // �ֿ��С
    int blockSize = sqrt(arr.size());
    list<Node*> blocks;
    vector<int> indexTable;

    // ����������������
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < arr.size(); ++i) {
        Node* newNode = new Node{ arr[i], nullptr };
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        if ((i + 1) % blockSize == 0 || i == arr.size() - 1) {
            blocks.push_back(head);
            indexTable.push_back(tail->value);
            head = nullptr;
            tail = nullptr;
        }
    }

    // ���������в���
    int index = sequentialSearch(indexTable, target);
    if (index == -1) {
        cout << "Element not found" << endl;
        return 0;
    }

    // ����Ӧ�Ŀ��в���
    auto it = next(blocks.begin(), index);
    Node* found = sequentialSearchInBlock(*it, target);
    if (found) {
        cout << "Element found: " << found->value << endl;
    }
    else {
        cout << "Element not found" << endl;
    }

    return 0;
}

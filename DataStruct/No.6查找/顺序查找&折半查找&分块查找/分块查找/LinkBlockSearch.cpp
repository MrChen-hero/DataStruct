#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>

using namespace std;

// 链表节点定义
struct Node {
    int value;
    Node* next;
};

// 顺序查找索引表
int sequentialSearch(vector<int>& indexTable, int target) {
    for (int i = 0; i < indexTable.size(); ++i) {
        if (indexTable[i] >= target) {
            return i;
        }
    }
    return -1;
}

// 顺序查找链表块
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
    // 原始数组
    vector<int> arr = { 1, 3, 5, 8, 14, 18, 19, 21, 33, 37, 39, 41, 45, 49, 50 };
    int target = 19;

    // 分块大小
    int blockSize = sqrt(arr.size());
    list<Node*> blocks;
    vector<int> indexTable;

    // 创建链表块和索引表
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

    // 在索引表中查找
    int index = sequentialSearch(indexTable, target);
    if (index == -1) {
        cout << "Element not found" << endl;
        return 0;
    }

    // 在相应的块中查找
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

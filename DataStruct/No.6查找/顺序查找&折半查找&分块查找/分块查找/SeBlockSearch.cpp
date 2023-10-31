#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// �۰����������
int binarySearch(vector<int>& indexTable, int target) {
    int low = 0, high = indexTable.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (indexTable[mid] == target) {
            return mid;
        }
        else if (indexTable[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low;  // ���ص�һ�����ڵ���Ŀ�������
}

int main() {
    // ԭʼ����
    vector<int> arr = { 1, 3, 5, 8, 14, 18, 19, 21, 33, 37, 39, 41, 45, 49, 50 };
    int target = 19;

    // �ֿ��С
    int blockSize = sqrt(arr.size());
    vector<vector<int>> blocks;
    vector<int> indexTable;

    // �������������
    vector<int> block;
    for (int i = 0; i < arr.size(); ++i) {
        block.push_back(arr[i]);
        if ((i + 1) % blockSize == 0 || i == arr.size() - 1) {
            blocks.push_back(block);
            indexTable.push_back(block.back());
            block.clear();
        }
    }

    // ���������в���
    int index = binarySearch(indexTable, target);
    if (index == -1 || index >= indexTable.size()) {
        cout << "Element not found" << endl;
        return 0;
    }

    // ����Ӧ�Ŀ��в���
    auto it = find(blocks[index].begin(), blocks[index].end(), target);
    if (it != blocks[index].end()) {
        cout << "Element found: " << *it << endl;
    }
    else {
        cout << "Element not found" << endl;
    }

    return 0;
}

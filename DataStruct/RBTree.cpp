#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <algorithm>
#include "RBTree.h"

void testRBTree(int n) {
    RBTree tree;
    std::set<int> dataSet; // 用 set 数据结构存储生成的随机数，方便进行验证
    std::vector<int> dataVec;
    std::srand(std::time(0));

    std::cout << "开始插入 " << n << " 个随机数据到红黑树中..." << std::endl;
    for (int i = 0; i < n; i++) {
        int data = std::rand() % 100;
        dataVec.push_back(data);
        dataSet.insert(data);
        tree.insert(data);
    }
    std::cout << "插入完成，打印红黑树的结构:" << std::endl;
    tree.print();

    std::cout << "开始删除一些数据..." << std::endl;
    std::random_shuffle(dataVec.begin(), dataVec.end());
    for (int i = 0; i < n / 2; i++) {
        int data = dataVec[i];
        std::cout << "删除数据: " << data << std::endl;
        dataSet.erase(data); // 从 set 数据结构中移除数据
        tree.deleteNode(data);
    }
    std::cout << "删除完成，打印红黑树的结构:" << std::endl;
    tree.print();

    std::cout << "开始查询一些数据..." << std::endl;
    std::random_shuffle(dataVec.begin(), dataVec.end());
    for (int i = 0; i < n / 2; i++) {
        int data = dataVec[i];
        std::cout << "查询数据: " << data << std::endl;
        RBNode* node = tree.find(data);
        if (node != nullptr) {
            std::string color = node->color ? "RED" : "BLACK";
            std::cout << "找到了节点: " << node->data << "(" << color << ")";

            // 与 set 数据结构的查询结果进行比较，检查是否正确
            if (dataSet.find(data) != dataSet.end()) {
                std::cout << " [验证通过]" << std::endl;
            }
            else {
                std::cout << " [验证失败]" << std::endl;
            }
        }
        else {
            std::cout << "没有找到节点";

            // 与 set 数据结构的查询结果进行比较，检查是否正确
            if (dataSet.find(data) == dataSet.end()) {
                std::cout << " [验证通过]" << std::endl;
            }
            else {
                std::cout << " [验证失败]" << std::endl;
            }
        }
    }
    std::cout << "查询完成" << std::endl;
}


// 定义main函数，调用测试函数
int main() {
    testRBTree(10); // 测试10个随机数据
    return 0;
}

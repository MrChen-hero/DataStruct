#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <algorithm>
#include "RBTree.h"

void testRBTree(int n) {
    RBTree tree;
    std::set<int> dataSet; // �� set ���ݽṹ�洢���ɵ�����������������֤
    std::vector<int> dataVec;
    std::srand(std::time(0));

    std::cout << "��ʼ���� " << n << " ��������ݵ��������..." << std::endl;
    for (int i = 0; i < n; i++) {
        int data = std::rand() % 100;
        dataVec.push_back(data);
        dataSet.insert(data);
        tree.insert(data);
    }
    std::cout << "������ɣ���ӡ������Ľṹ:" << std::endl;
    tree.print();

    std::cout << "��ʼɾ��һЩ����..." << std::endl;
    std::random_shuffle(dataVec.begin(), dataVec.end());
    for (int i = 0; i < n / 2; i++) {
        int data = dataVec[i];
        std::cout << "ɾ������: " << data << std::endl;
        dataSet.erase(data); // �� set ���ݽṹ���Ƴ�����
        tree.deleteNode(data);
    }
    std::cout << "ɾ����ɣ���ӡ������Ľṹ:" << std::endl;
    tree.print();

    std::cout << "��ʼ��ѯһЩ����..." << std::endl;
    std::random_shuffle(dataVec.begin(), dataVec.end());
    for (int i = 0; i < n / 2; i++) {
        int data = dataVec[i];
        std::cout << "��ѯ����: " << data << std::endl;
        RBNode* node = tree.find(data);
        if (node != nullptr) {
            std::string color = node->color ? "RED" : "BLACK";
            std::cout << "�ҵ��˽ڵ�: " << node->data << "(" << color << ")";

            // �� set ���ݽṹ�Ĳ�ѯ������бȽϣ�����Ƿ���ȷ
            if (dataSet.find(data) != dataSet.end()) {
                std::cout << " [��֤ͨ��]" << std::endl;
            }
            else {
                std::cout << " [��֤ʧ��]" << std::endl;
            }
        }
        else {
            std::cout << "û���ҵ��ڵ�";

            // �� set ���ݽṹ�Ĳ�ѯ������бȽϣ�����Ƿ���ȷ
            if (dataSet.find(data) == dataSet.end()) {
                std::cout << " [��֤ͨ��]" << std::endl;
            }
            else {
                std::cout << " [��֤ʧ��]" << std::endl;
            }
        }
    }
    std::cout << "��ѯ���" << std::endl;
}


// ����main���������ò��Ժ���
int main() {
    testRBTree(10); // ����10���������
    return 0;
}

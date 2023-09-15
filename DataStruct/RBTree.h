#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

// ����һ�� RBNode �࣬���ڱ�ʾ������Ľڵ�
class RBNode {
public:
    int data;           // �ڵ��д洢������
    bool color;         // �ڵ����ɫ��true Ϊ��ɫ��false Ϊ��ɫ
    RBNode* left;       // ���ӽڵ�
    RBNode* right;      // ���ӽڵ�
    RBNode* parent;     // ���ڵ�

    // ���캯�������������ֵ��ʼ���ڵ�
    RBNode(int value) : data(value), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

// ����һ�� RBTree �࣬���ڱ�ʾ������Ľṹ
class RBTree {
private:
    RBNode* root;       // ���ڵ�
    
    // findMinValueNode �������ڸ����ڵ���������ҵ�������Сֵ�Ľڵ�
    RBNode* findMinValueNode(RBNode* node) {
        RBNode* current = node;

        // ��������������Сֵ�Ľڵ�
        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }
    // leftRotate ������ʵ�ֽڵ������ת����
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;      // �� x �����ӽڵ� y ��Ϊ�µĸ��ڵ�
        RBNode* T2 = y->left;      // ��ȡ y �����ӽڵ� T2

        y->left = x;               // ���� y �����ӽڵ㣨ԭ�������ӽڵ� x��
        x->right = T2;             // ���� x �����ӽڵ㣨ԭ�� y �����ӽڵ� T2��

        // ���� x �� y �ĸ��ڵ�
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        x->parent = y;

        // ����Ҫ���½ڵ�ĸ߶ȣ���Ϊ������������߶Ƚ���ƽ��
    }

    // rightRotate ������ʵ�ֽڵ������ת����
    void rightRotate(RBNode* y) {
        RBNode* x = y->left;       // �� y �����ӽڵ� x ��Ϊ�µĸ��ڵ�
        RBNode* T2 = x->right;     // ��ȡ x �����ӽڵ� T2

        x->right = y;              // ���� x �����ӽڵ㣨ԭ�������ӽڵ� y��
        y->left = T2;              // ���� y �����ӽڵ㣨ԭ�� x �����ӽڵ� T2��

        // ���� y �� x �ĸ��ڵ�
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        }
        else if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
        y->parent = x;

        // ����Ҫ���½ڵ�ĸ߶ȣ���Ϊ������������߶Ƚ���ƽ��
    }

    // fixInsert �������޸��������������ƻ���������ʵ����
    void fixInsert(RBNode* node) {
        RBNode* parent = nullptr;
        RBNode* grandparent = nullptr;

        while (node != root && node->color && node->parent->color) {
            parent = node->parent;
            grandparent = parent->parent;

            if (grandparent == nullptr) {
                break;
            }

            if (parent == grandparent->left) {   // ���ڵ����游�ڵ������
                RBNode* uncle = grandparent->right;  // ����ڵ����游�ڵ���Һ���

                if (uncle != nullptr && uncle->color) {   // �����������ڵ�Ҳ�Ǻ�ɫ
                    parent->color = false;                // �����ڵ������ڵ�Ⱦ�ɺ�ɫ
                    uncle->color = false;
                    grandparent->color = true;            // ���游�ڵ�Ⱦ�ɺ�ɫ
                    node = grandparent;                   // ���游�ڵ���Ϊ�µĽڵ㣬�������ϵ���
                }
                else {  // ����ڵ��Ǻ�ɫ�򲻴���
                    if (node == parent->right) {  // ����ģ��ڵ��Ǹ��ڵ���Һ���
                        leftRotate(parent);       // �Ը��ڵ����������ת��Ϊ�����
                        node = parent;            // �����ڵ���Ϊ�µĽڵ�
                        parent = node->parent;
                    }
                    // ����壺�ڵ��Ǹ��ڵ������
                    rightRotate(grandparent);     // ���游�ڵ��������������λ�ú���ɫ
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else {  // ���ڵ����游�ڵ���Һ��ӣ������������Գ�
                RBNode* uncle = grandparent->left;   // ����ڵ����游�ڵ������

                if (uncle != nullptr && uncle->color) {   // �����������ڵ�Ҳ�Ǻ�ɫ
                    parent->color = false;                // �����ڵ������ڵ�Ⱦ�ɺ�ɫ
                    uncle->color = false;
                    grandparent->color = true;            // ���游�ڵ�Ⱦ�ɺ�ɫ
                    node = grandparent;                   // ���游�ڵ���Ϊ�µĽڵ㣬�������ϵ���
                }
                else {  // ����ڵ��Ǻ�ɫ�򲻴���
                    if (node == parent->left) {   // ����ģ��ڵ��Ǹ��ڵ������
                        rightRotate(parent);      // �Ը��ڵ����������ת��Ϊ�����
                        node = parent;            // �����ڵ���Ϊ�µĽڵ�
                        parent = node->parent;
                    }
                    // ����壺�ڵ��Ǹ��ڵ���Һ���
                    leftRotate(grandparent);      // ���游�ڵ��������������λ�ú���ɫ
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = false;  // ��֤���ڵ�ʼ���Ǻ�ɫ
    }

    // fixDelete �������޸�ɾ������������ƻ���������ʵ����
    void fixDelete(RBNode* node) {
        if (node == nullptr) {
            return;
        }

        RBNode* sibling = nullptr;

        while (node != root && (!node || !node->color)) {
            if (node == node->parent->left) {
                sibling = node->parent->right;

                if (sibling && sibling->color) {
                    sibling->color = false;
                    node->parent->color = true;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling && !sibling->left->color && !sibling->right->color) {
                    sibling->color = true;
                    node = node->parent;
                }
                else {
                    if (sibling && !sibling->right->color) {
                        sibling->left->color = false;
                        sibling->color = true;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }

                    if (sibling) {
                        sibling->color = node->parent->color;
                        sibling->right->color = false;
                    }
                    node->parent->color = false;
                    leftRotate(node->parent);
                    node = root;
                }
            }
            else {
                sibling = node->parent->left;

                if (sibling && sibling->color) {
                    sibling->color = false;
                    node->parent->color = true;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling && !sibling->right->color && !sibling->left->color) {
                    sibling->color = true;
                    node = node->parent;
                }
                else {
                    if (sibling && !sibling->left->color) {
                        sibling->right->color = false;
                        sibling->color = true;
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }

                    if (sibling) {
                        sibling->color = node->parent->color;
                        sibling->left->color = false;
                    }
                    node->parent->color = false;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }

        node->color = false;
    }


public:
    // ���캯������ʼ�����ڵ�Ϊ��
    RBTree() : root(nullptr) {}

    // insert �������������в����µ�����
    void insert(int data) {
        RBNode* node = new RBNode(data);  // ����һ���µĺ�ɫ�ڵ�

        if (root == nullptr) {    // ������ڵ�Ϊ�գ���ֱ�ӽ��½ڵ���Ϊ���ڵ㣬������Ⱦ�ɺ�ɫ
            root = node;
            root->color = false;
        }
        else {
            RBNode* current = root;   // �Ӹ��ڵ㿪ʼ����
            RBNode* parent = nullptr; // ��¼��ǰ�ڵ�ĸ��ڵ�

            while (current != nullptr) {  // �ҵ����ʵĲ���λ��
                parent = current;
                if (data < current->data) {
                    current = current->left;
                }
                else if (data > current->data) {
                    current = current->right;
                }
                else {
                    return; // ��������Ѿ����ڣ���ֱ�ӷ��أ����ظ�����
                }
            }

            node->parent = parent;    // ���½ڵ�ĸ��ڵ�����Ϊ�ҵ��ĸ��ڵ�
            if (data < parent->data) {
                parent->left = node;  // ���½ڵ���Ϊ���ڵ�����ӽڵ�����ӽڵ�
            }
            else {
                parent->right = node;
            }

            fixInsert(node);  // �����޸��������ָ������������
        }
    }

    // deleteNode �������Ӻ������ɾ��һ������
    void deleteNode(int data) {
        RBNode* node = root;  // �Ӹ��ڵ㿪ʼ����
        RBNode* parent = nullptr; // ��¼��ǰ�ڵ�ĸ��ڵ�
        RBNode* target = nullptr; // ��¼Ҫɾ����Ŀ��ڵ�

        while (node != nullptr) {  // �ҵ�Ҫɾ����Ŀ��ڵ�
            if (data == node->data) {
                target = node;
                break;
            }
            else if (data < node->data) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        if (target == nullptr) {   // ���û���ҵ�Ŀ��ڵ㣬��ֱ�ӷ���
            return;
        }

        RBNode* x, * y;     // ���������������������ڼ�¼ɾ����������Ҫ�����Ľڵ����ɫ

        y = target;        // y ָ��Ҫɾ����Ŀ��ڵ�
        bool yOriginalColor = y->color;   // ��¼ y ��ԭʼ��ɫ

        if (target->left == nullptr) {    // ���һ��Ŀ��ڵ�ֻ�����ӽڵ��û���ӽڵ�
            x = target->right;            // x ָ��Ŀ��ڵ�����ӽڵ㣨��գ�
            transplant(target, target->right);    // �� x �滻�� y ��λ��
        }
        else if (target->right == nullptr) {  // �������Ŀ��ڵ�ֻ�����ӽڵ�
            x = target->left;             // x ָ��Ŀ��ڵ�����ӽڵ�
            transplant(target, target->left);     // �� x �滻�� y ��λ��
        }
        else {  // �������Ŀ��ڵ��������ӽڵ�
            y = findMinValueNode(target->right);  // y ָ��Ŀ��ڵ�ĺ�̣�����������Сֵ��
            yOriginalColor = y->color;   // ��¼ y ��ԭʼ��ɫ
            x = y->right;                // x ָ�� y �����ӽڣ���գ�

            if (y->parent == target) { // ��� y �ĸ�����Ŀ���
                if (x != nullptr) {
                    x->parent = y;
                }
            }
            else { // ������ x �滻�� y ��λ�ã�Ȼ�� y �����ӽ���ΪĿ��ڵ����ӽ�
                transplant(y, y->right);
                y->right = target->right;
                if (y->right != nullptr) { // ����nullptr���
                    y->right->parent = y;
                }
            }

            transplant(target, y);   // �� y �滻��Ŀ��ڵ�λ�ã�Ȼ�� y �����ӽ���ΪĿ��ڵ����ӽڣ��� y ����ɫ��ΪĿ��ڵ���ɫ
            y->left = target->left;
            y->left->parent = y;
            y->color = target->color;
        }

        delete target;    // ɾ��Ŀ���

        if (!yOriginalColor) {    // ��� y ��ԭʼ��ɫ�Ǻ�ɫ��������ƻ��˺�������ʣ���Ҫ�����޸�����
            fixDelete(x);
        }
    }

    // transplant ��������һ���ڵ��滻��һ���ڵ��λ��
    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == nullptr) {   // ��� u �ĸ��ڵ�Ϊ�գ��� u �Ǹ��ڵ㣬�� v ��Ϊ���ڵ�
            root = v;
        }
        else if (u == u->parent->left) {  // ��� u ���丸�ڵ�����ӣ��� v ��Ϊ�丸�ڵ������
            u->parent->left = v;
        }
        else {  // ��� u ���丸�ڵ���Һ��ӣ��� v ��Ϊ�丸�ڵ���Һ���
            u->parent->right = v;
        }

        if (v != nullptr) {  // �� v �ǿգ��� u �ĸ��ڵ���Ϊ v �ĸ��ڵ�
            v->parent = u->parent;
        }
    }

    // find �������ں�����в���һ�����ݣ����ض�Ӧ�Ľڵ�ָ�룬����������򷵻ؿ�ָ��
    RBNode* find(int data) {
        RBNode* current = root;   // �Ӹ��ڵ㿪ʼ����

        while (current != nullptr) {  // ѭ�����ң�ֱ���ҵ���������
            if (data == current->data) {
                return current;   // ����ҵ������ص�ǰ�ڵ�ָ��
            }
            else if (data < current->data) {
                current = current->left;   // ���С�ڵ�ǰ�ڵ㣬������������
            }
            else {
                current = current->right;  // ������ڵ�ǰ�ڵ㣬������������
            }
        }

        return nullptr;  // ���û���ҵ������ؿ�ָ��
    }

    // print ��������ӡ������Ľṹ�����ڲ��Ժ͵���
    void print() {
        printHelper(root, "", true);
    }

    // printHelper ������������ӡ���������õݹ�ķ�ʽ��ӡÿ���ڵ㼰���ӽڵ�
    void printHelper(RBNode* node, std::string indent, bool last) {
        if (node != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "     ";
            }
            else {
                std::cout << "L----";
                indent += "|    ";
            }

            std::string color = node->color ? "RED" : "BLACK";
            std::cout << node->data << "(" << color << ")" << std::endl;
            printHelper(node->left, indent, false);
            printHelper(node->right, indent, true);
        }
    }
};

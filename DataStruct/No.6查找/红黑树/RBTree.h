#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

// 定义一个 RBNode 类，用于表示红黑树的节点
class RBNode {
public:
    int data;           // 节点中存储的数据
    bool color;         // 节点的颜色，true 为红色，false 为黑色
    RBNode* left;       // 左子节点
    RBNode* right;      // 右子节点
    RBNode* parent;     // 父节点

    // 构造函数，根据输入的值初始化节点
    RBNode(int value) : data(value), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

// 定义一个 RBTree 类，用于表示红黑树的结构
class RBTree {
private:
    RBNode* root;       // 根节点
    
    // findMinValueNode 函数：在给定节点的子树中找到具有最小值的节点
    RBNode* findMinValueNode(RBNode* node) {
        RBNode* current = node;

        // 向左子树查找最小值的节点
        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }
    // leftRotate 函数：实现节点的左旋转操作
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;      // 将 x 的右子节点 y 作为新的根节点
        RBNode* T2 = y->left;      // 获取 y 的左子节点 T2

        y->left = x;               // 更新 y 的左子节点（原来的右子节点 x）
        x->right = T2;             // 更新 x 的右子节点（原来 y 的左子节点 T2）

        // 更新 x 和 y 的父节点
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

        // 不需要更新节点的高度，因为红黑树不依赖高度进行平衡
    }

    // rightRotate 函数：实现节点的右旋转操作
    void rightRotate(RBNode* y) {
        RBNode* x = y->left;       // 将 y 的左子节点 x 作为新的根节点
        RBNode* T2 = x->right;     // 获取 x 的右子节点 T2

        x->right = y;              // 更新 x 的右子节点（原来的左子节点 y）
        y->left = T2;              // 更新 y 的左子节点（原来 x 的右子节点 T2）

        // 更新 y 和 x 的父节点
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

        // 不需要更新节点的高度，因为红黑树不依赖高度进行平衡
    }

    // fixInsert 函数：修复插入操作后可能破坏红黑树性质的情况
    void fixInsert(RBNode* node) {
        RBNode* parent = nullptr;
        RBNode* grandparent = nullptr;

        while (node != root && node->color && node->parent->color) {
            parent = node->parent;
            grandparent = parent->parent;

            if (grandparent == nullptr) {
                break;
            }

            if (parent == grandparent->left) {   // 父节点是祖父节点的左孩子
                RBNode* uncle = grandparent->right;  // 叔叔节点是祖父节点的右孩子

                if (uncle != nullptr && uncle->color) {   // 情况三：叔叔节点也是红色
                    parent->color = false;                // 将父节点和叔叔节点染成黑色
                    uncle->color = false;
                    grandparent->color = true;            // 将祖父节点染成红色
                    node = grandparent;                   // 将祖父节点作为新的节点，继续向上调整
                }
                else {  // 叔叔节点是黑色或不存在
                    if (node == parent->right) {  // 情况四：节点是父节点的右孩子
                        leftRotate(parent);       // 对父节点进行左旋，转化为情况五
                        node = parent;            // 将父节点作为新的节点
                        parent = node->parent;
                    }
                    // 情况五：节点是父节点的左孩子
                    rightRotate(grandparent);     // 对祖父节点进行右旋，调整位置和颜色
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else {  // 父节点是祖父节点的右孩子，与上面的情况对称
                RBNode* uncle = grandparent->left;   // 叔叔节点是祖父节点的左孩子

                if (uncle != nullptr && uncle->color) {   // 情况三：叔叔节点也是红色
                    parent->color = false;                // 将父节点和叔叔节点染成黑色
                    uncle->color = false;
                    grandparent->color = true;            // 将祖父节点染成红色
                    node = grandparent;                   // 将祖父节点作为新的节点，继续向上调整
                }
                else {  // 叔叔节点是黑色或不存在
                    if (node == parent->left) {   // 情况四：节点是父节点的左孩子
                        rightRotate(parent);      // 对父节点进行右旋，转化为情况五
                        node = parent;            // 将父节点作为新的节点
                        parent = node->parent;
                    }
                    // 情况五：节点是父节点的右孩子
                    leftRotate(grandparent);      // 对祖父节点进行左旋，调整位置和颜色
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = false;  // 保证根节点始终是黑色
    }

    // fixDelete 函数：修复删除操作后可能破坏红黑树性质的情况
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
    // 构造函数，初始化根节点为空
    RBTree() : root(nullptr) {}

    // insert 函数：向红黑树中插入新的数据
    void insert(int data) {
        RBNode* node = new RBNode(data);  // 创建一个新的红色节点

        if (root == nullptr) {    // 如果根节点为空，则直接将新节点作为根节点，并将其染成黑色
            root = node;
            root->color = false;
        }
        else {
            RBNode* current = root;   // 从根节点开始遍历
            RBNode* parent = nullptr; // 记录当前节点的父节点

            while (current != nullptr) {  // 找到合适的插入位置
                parent = current;
                if (data < current->data) {
                    current = current->left;
                }
                else if (data > current->data) {
                    current = current->right;
                }
                else {
                    return; // 如果数据已经存在，则直接返回，不重复插入
                }
            }

            node->parent = parent;    // 将新节点的父节点设置为找到的父节点
            if (data < parent->data) {
                parent->left = node;  // 将新节点作为父节点的左子节点或右子节点
            }
            else {
                parent->right = node;
            }

            fixInsert(node);  // 调用修复函数，恢复红黑树的性质
        }
    }

    // deleteNode 函数：从红黑树中删除一个数据
    void deleteNode(int data) {
        RBNode* node = root;  // 从根节点开始遍历
        RBNode* parent = nullptr; // 记录当前节点的父节点
        RBNode* target = nullptr; // 记录要删除的目标节点

        while (node != nullptr) {  // 找到要删除的目标节点
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

        if (target == nullptr) {   // 如果没有找到目标节点，则直接返回
            return;
        }

        RBNode* x, * y;     // 定义两个辅助变量，用于记录删除操作后需要调整的节点和颜色

        y = target;        // y 指向要删除的目标节点
        bool yOriginalColor = y->color;   // 记录 y 的原始颜色

        if (target->left == nullptr) {    // 情况一：目标节点只有右子节点或没有子节点
            x = target->right;            // x 指向目标节点的右子节点（或空）
            transplant(target, target->right);    // 用 x 替换掉 y 的位置
        }
        else if (target->right == nullptr) {  // 情况二：目标节点只有左子节点
            x = target->left;             // x 指向目标节点的左子节点
            transplant(target, target->left);     // 用 x 替换掉 y 的位置
        }
        else {  // 情况三：目标节点有两个子节点
            y = findMinValueNode(target->right);  // y 指向目标节点的后继（右子树中最小值）
            yOriginalColor = y->color;   // 记录 y 的原始颜色
            x = y->right;                // x 指向 y 的右子节（或空）

            if (y->parent == target) { // 如果 y 的父节是目标节
                if (x != nullptr) {
                    x->parent = y;
                }
            }
            else { // 否则，用 x 替换掉 y 的位置，然后将 y 的右子节设为目标节的右子节
                transplant(y, y->right);
                y->right = target->right;
                if (y->right != nullptr) { // 增加nullptr检查
                    y->right->parent = y;
                }
            }

            transplant(target, y);   // 用 y 替换掉目标节的位置，然后将 y 的左子节设为目标节的左子节，将 y 的颜色设为目标节的颜色
            y->left = target->left;
            y->left->parent = y;
            y->color = target->color;
        }

        delete target;    // 删除目标节

        if (!yOriginalColor) {    // 如果 y 的原始颜色是黑色，则可能破坏了红黑树性质，需要调用修复函数
            fixDelete(x);
        }
    }

    // transplant 函数：用一个节点替换另一个节点的位置
    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == nullptr) {   // 如果 u 的父节点为空，则 u 是根节点，将 v 设为根节点
            root = v;
        }
        else if (u == u->parent->left) {  // 如果 u 是其父节点的左孩子，则将 v 设为其父节点的左孩子
            u->parent->left = v;
        }
        else {  // 如果 u 是其父节点的右孩子，则将 v 设为其父节点的右孩子
            u->parent->right = v;
        }

        if (v != nullptr) {  // 若 v 非空，将 u 的父节点设为 v 的父节点
            v->parent = u->parent;
        }
    }

    // find 函数：在红黑树中查找一个数据，返回对应的节点指针，如果不存在则返回空指针
    RBNode* find(int data) {
        RBNode* current = root;   // 从根节点开始遍历

        while (current != nullptr) {  // 循环查找，直到找到或遍历完毕
            if (data == current->data) {
                return current;   // 如果找到，返回当前节点指针
            }
            else if (data < current->data) {
                current = current->left;   // 如果小于当前节点，向左子树查找
            }
            else {
                current = current->right;  // 如果大于当前节点，向右子树查找
            }
        }

        return nullptr;  // 如果没有找到，返回空指针
    }

    // print 函数：打印红黑树的结构，用于测试和调试
    void print() {
        printHelper(root, "", true);
    }

    // printHelper 函数：辅助打印函数，采用递归的方式打印每个节点及其子节点
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

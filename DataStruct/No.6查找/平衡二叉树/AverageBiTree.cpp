#include <iostream>
#include <vector>
#include <algorithm>

// 定义一个 AVLNode 类，用于表示 AVL 树的节点
class AVLNode {
public:
    int data;           // 节点中存储的数据
    int height;         // 节点的高度
    AVLNode* left;      // 左子节点
    AVLNode* right;     // 右子节点

    // 构造函数，根据输入的值初始化节点
    AVLNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

// height 函数：获取节点的高度
int height(AVLNode* node) {
    return (node == nullptr) ? 0 : node->height;
}

// balance 函数：计算节点的平衡因子，即左子树高度与右子树高度之差
int balance(AVLNode* node) {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

// leftRotate 函数：实现节点的左旋转操作
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;      // 将 x 的右子节点 y 作为新的根节点
    AVLNode* T2 = y->left;      // 获取 y 的左子节点 T2

    y->left = x;                // 更新 y 的左子节点（原来的右子节点 x）
    x->right = T2;              // 更新 x 的右子节点（原来 y 的左子节点 T2）

    // 更新节点 x 和 y 的高度
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;                   // 返回新的根节点 y
}

// rightRotate 函数：实现节点的右旋转操作
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;       // 将 y 的左子节点 x 作为新的根节点
    AVLNode* T2 = x->right;     // 获取 x 的右子节点 T2

    x->right = y;               // 更新 x 的右子节点（原来的左子节点 y）
    y->left = T2;               // 更新 y 的左子节点（原来 x 的右子节点 T2）

    // 更新节点 y 和 x 的高度
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;                   // 返回新的根节点 x
}

// insert 函数：向 AVL 树中插入新的数据
AVLNode* insert(AVLNode* root, int data) {
    // 如果根节点为空，则创建一个新的节点并返回
    if (root == nullptr) {
        return new AVLNode(data);
    }

    // 递归插入数据到左子树或右子树
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    else {
        return root;
    }

    // 更新根节点的高度(当前需要检查平衡的子树的根节点。)
    root->height = 1 + std::max(height(root->left), height(root->right));

    // 计算根节点的平衡因子
    int balanceFactor = balance(root);

    // 如果平衡因子大于 1，需要进行旋转操作以恢复平衡
    if (balanceFactor > 1) {
        // 左左情况：右旋
        if (data < root->left->data) {
            return rightRotate(root);
        }
        // 左右情况：左旋+右旋
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    // 如果平衡因子小于 -1，需要进行旋转操作以恢复平衡
    if (balanceFactor < -1) {
        // 右右情况：左旋
        if (data > root->right->data) {
            return leftRotate(root);
        }
        // 右左情况：右旋+左旋
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// findMinValueNode 函数：找到以当前节点为根的子树中具有最小值的节点
AVLNode* findMinValueNode(AVLNode* root) {
    AVLNode* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// deleteNode 函数：从 AVL 树中删除一个节点
AVLNode* deleteNode(AVLNode* root, int data) {
    // 如果根节点为空，则直接返回
    if (root == nullptr) {
        return root;
    }

    // 递归删除左子树或右子树中的节点
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        // 当找到待删除节点时
        // 情况1：节点只有一个或没有子节点
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }

            delete temp;
        }
        // 情况2：节点有两个子节点
        else {
            AVLNode* temp = findMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // 节点已被删除，返回空
    if (root == nullptr) {
        return root;
    }

    // 更新根节点的高度
    root->height = 1 + std::max(height(root->left), height(root->right));

    // 计算根节点的平衡因子
    int balanceFactor = balance(root);

    // 如果平衡因子大于 1，需要进行旋转操作以恢复平衡
    if (balanceFactor > 1) {
        // 左左情况：右旋
        if (balance(root->left) >= 0) {
            return rightRotate(root);
        }
        // 左右情况：左旋+右旋
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    // 如果平衡因子小于 -1，需要进行旋转操作以恢复平衡
    if (balanceFactor < -1) {
        // 右右情况：左旋
        if (balance(root->right) <= 0) {
            return leftRotate(root);
        }
        // 右左情况：右旋+左旋
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// 以递归方式进行中序遍历，并将节点的数据打印出来
void inOrderTraversalRecursively(AVLNode* node) {
    if (node != nullptr) {
        inOrderTraversalRecursively(node->left);
        std::cout << node->data << " ";
        inOrderTraversalRecursively(node->right);
    }
}

int main() {
    std::vector<int> arr = { 9, 5, 3, 7, 12, 10, 14 };
    AVLNode* root = nullptr;

    // 向 AVL 树中插入值
    for (int value : arr) {
        root = insert(root, value);
    }

    // 打印中序遍历的结果
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    // 插入新值并打印中序遍历的结果
    root = insert(root, 15);
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    // 删除一个节点并打印中序遍历的结果
    root = deleteNode(root, 10);
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    return 0;
}

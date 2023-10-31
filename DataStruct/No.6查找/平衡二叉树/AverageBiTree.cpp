#include <iostream>
#include <vector>
#include <algorithm>

// ����һ�� AVLNode �࣬���ڱ�ʾ AVL ���Ľڵ�
class AVLNode {
public:
    int data;           // �ڵ��д洢������
    int height;         // �ڵ�ĸ߶�
    AVLNode* left;      // ���ӽڵ�
    AVLNode* right;     // ���ӽڵ�

    // ���캯�������������ֵ��ʼ���ڵ�
    AVLNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

// height ��������ȡ�ڵ�ĸ߶�
int height(AVLNode* node) {
    return (node == nullptr) ? 0 : node->height;
}

// balance ����������ڵ��ƽ�����ӣ����������߶����������߶�֮��
int balance(AVLNode* node) {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

// leftRotate ������ʵ�ֽڵ������ת����
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;      // �� x �����ӽڵ� y ��Ϊ�µĸ��ڵ�
    AVLNode* T2 = y->left;      // ��ȡ y �����ӽڵ� T2

    y->left = x;                // ���� y �����ӽڵ㣨ԭ�������ӽڵ� x��
    x->right = T2;              // ���� x �����ӽڵ㣨ԭ�� y �����ӽڵ� T2��

    // ���½ڵ� x �� y �ĸ߶�
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;                   // �����µĸ��ڵ� y
}

// rightRotate ������ʵ�ֽڵ������ת����
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;       // �� y �����ӽڵ� x ��Ϊ�µĸ��ڵ�
    AVLNode* T2 = x->right;     // ��ȡ x �����ӽڵ� T2

    x->right = y;               // ���� x �����ӽڵ㣨ԭ�������ӽڵ� y��
    y->left = T2;               // ���� y �����ӽڵ㣨ԭ�� x �����ӽڵ� T2��

    // ���½ڵ� y �� x �ĸ߶�
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;                   // �����µĸ��ڵ� x
}

// insert �������� AVL ���в����µ�����
AVLNode* insert(AVLNode* root, int data) {
    // ������ڵ�Ϊ�գ��򴴽�һ���µĽڵ㲢����
    if (root == nullptr) {
        return new AVLNode(data);
    }

    // �ݹ�������ݵ���������������
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    else {
        return root;
    }

    // ���¸��ڵ�ĸ߶�(��ǰ��Ҫ���ƽ��������ĸ��ڵ㡣)
    root->height = 1 + std::max(height(root->left), height(root->right));

    // ������ڵ��ƽ������
    int balanceFactor = balance(root);

    // ���ƽ�����Ӵ��� 1����Ҫ������ת�����Իָ�ƽ��
    if (balanceFactor > 1) {
        // �������������
        if (data < root->left->data) {
            return rightRotate(root);
        }
        // �������������+����
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    // ���ƽ������С�� -1����Ҫ������ת�����Իָ�ƽ��
    if (balanceFactor < -1) {
        // �������������
        if (data > root->right->data) {
            return leftRotate(root);
        }
        // �������������+����
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// findMinValueNode �������ҵ��Ե�ǰ�ڵ�Ϊ���������о�����Сֵ�Ľڵ�
AVLNode* findMinValueNode(AVLNode* root) {
    AVLNode* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// deleteNode �������� AVL ����ɾ��һ���ڵ�
AVLNode* deleteNode(AVLNode* root, int data) {
    // ������ڵ�Ϊ�գ���ֱ�ӷ���
    if (root == nullptr) {
        return root;
    }

    // �ݹ�ɾ�����������������еĽڵ�
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        // ���ҵ���ɾ���ڵ�ʱ
        // ���1���ڵ�ֻ��һ����û���ӽڵ�
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
        // ���2���ڵ��������ӽڵ�
        else {
            AVLNode* temp = findMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // �ڵ��ѱ�ɾ�������ؿ�
    if (root == nullptr) {
        return root;
    }

    // ���¸��ڵ�ĸ߶�
    root->height = 1 + std::max(height(root->left), height(root->right));

    // ������ڵ��ƽ������
    int balanceFactor = balance(root);

    // ���ƽ�����Ӵ��� 1����Ҫ������ת�����Իָ�ƽ��
    if (balanceFactor > 1) {
        // �������������
        if (balance(root->left) >= 0) {
            return rightRotate(root);
        }
        // �������������+����
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    // ���ƽ������С�� -1����Ҫ������ת�����Իָ�ƽ��
    if (balanceFactor < -1) {
        // �������������
        if (balance(root->right) <= 0) {
            return leftRotate(root);
        }
        // �������������+����
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// �Եݹ鷽ʽ������������������ڵ�����ݴ�ӡ����
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

    // �� AVL ���в���ֵ
    for (int value : arr) {
        root = insert(root, value);
    }

    // ��ӡ��������Ľ��
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    // ������ֵ����ӡ��������Ľ��
    root = insert(root, 15);
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    // ɾ��һ���ڵ㲢��ӡ��������Ľ��
    root = deleteNode(root, 10);
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    return 0;
}

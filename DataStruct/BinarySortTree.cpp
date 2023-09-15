#include <iostream>
#include <vector>

// ��������������ڵ���
class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;

    // ���캯��
    BSTNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// ������ֵ�������������
BSTNode* insert(BSTNode* root, int data) {
    // ������ڵ�Ϊ�գ��½�һ���ڵ㲢����
    if (root == nullptr) {
        return new BSTNode(data);
    }
    else if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    else {
        std::cout << "The data " << data << " already exists in the tree." << std::endl;
    }
    return root;
}

// �ڶ����������в���ֵ������ӡ�����Ľ��
BSTNode* search(BSTNode* root, int data) {
    if (root == nullptr || root->data == data) {
        return root;
    }

    std::cout << "Visited node with data: " << root->data << std::endl;

    if (data < root->data) {
        return search(root->left, data);
    }
    else {
        return search(root->right, data);
    }
}

// Ѱ�Ҿ�����Сֵ�Ľڵ�
BSTNode* findMinValueNode(BSTNode* root) {
    BSTNode* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// �Ӷ�����������ɾ��ָ��ֵ
BSTNode* deleteNode(BSTNode* root, int data) {
    if (root == nullptr) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        if (root->left == nullptr) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        BSTNode* temp = findMinValueNode(root->right);  //�ҵ�����ɾ���ڵ���������������µĽڵ㲢�滻(������ҵ��������������½���滻)
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// ����������Զ������������еݹ����
void inOrderTraversalRecursively(BSTNode* node) {
    if (node != nullptr) {
        inOrderTraversalRecursively(node->left);
        std::cout << node->data << " ";
        inOrderTraversalRecursively(node->right);
    }
}

// ���������鹹������������
BSTNode* buildTreeFromIntArray(std::vector<int>& arr) {
    BSTNode* root = nullptr;

    for (int value : arr) {
        root = insert(root, value);
    }

    return root;
}

int main() {
    std::vector<int> arr = { 9, 5, 3, 7, 12, 10, 14 };

    BSTNode* root = buildTreeFromIntArray(arr);
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    std::cout << "Search for 10:" << std::endl;
    BSTNode* result = search(root, 10);
    if (result) {
        std::cout << "The data " << result->data << " is found in the tree." << std::endl;
    }
    else {
        std::cout << "The data is not found in the tree." << std::endl;
    }
    std::cout << std::endl;

    root = insert(root, 6);
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    root = deleteNode(root, 7);
    inOrderTraversalRecursively(root);
    std::cout << std::endl;

    return 0;
}

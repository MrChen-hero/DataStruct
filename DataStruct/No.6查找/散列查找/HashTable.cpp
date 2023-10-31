#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// ����ɢ�б�Ĵ�С
const int TABLE_SIZE = 13;

// ����ɢ�к���������
enum HashFuncType {
    MOD, // ����������
    DIRECT, // ֱ�Ӷ�ַ��
    DIGIT, // ���ַ�����
    SQUARE // ƽ��ȡ�з�
};

// �����ͻ���������
enum CollisionType {
    CHAINING, // ������
    LINEAR, // ����̽�ⷨ
    QUADRATIC, // ƽ��̽�ⷨ
    RANDOM, // α������з�
    REHASH // ��ɢ�з�
};

// ����ɢ�б�ڵ�Ľṹ��
struct HashNode {
    int key; // �ؼ���
    int value; // ֵ
    HashNode* next; // ָ����һ���ڵ��ָ�룬����������
    HashNode(int k = 0, int v = 0, HashNode* n = NULL) : key(k), value(v), next(n) {} // ���캯��
};

// ����ɢ�б����
class HashTable {
private:
    vector<HashNode*> table; // ɢ�б����飬ÿ��Ԫ����һ��ָ�룬ָ��һ���ڵ����NULL
    HashFuncType hashFuncType; // ɢ�к���������
    CollisionType collisionType; // ��ͻ���������

public:
    // ���캯������ʼ��һ���յ�ɢ�б���ָ��ɢ�к����ͳ�ͻ���������
    HashTable(HashFuncType hft = MOD, CollisionType ct = CHAINING) {
        table.resize(TABLE_SIZE); // ����ɢ�б��С�Ŀռ�
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL; // ��ʼ��ÿ��Ԫ��ΪNULL
        }
        hashFuncType = hft; // ����ɢ�к���������
        collisionType = ct; // ���ó�ͻ���������
    }

    // �����������ͷ�ɢ�б�ռ�õ��ڴ�ռ�
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* p = table[i]; // ��ȡÿ��Ԫ��ָ��Ľڵ�
            while (p != NULL) { // �����ýڵ������������ͷ�ÿ���ڵ�Ŀռ�
                HashNode* q = p->next;
                delete p;
                p = q;
            }
        }
    }

    // ���ݸ����Ĺؼ��֣�������ɢ�е�ַ������һ������ֵ��ʾ��ַ����
    int hashFunc(int key) {
        int index;
        switch (hashFuncType) { // ���ݲ�ͬ��ɢ�к������ͣ����ò�ͬ�ļ��㷽��
        case MOD: // �������������ùؼ��ֳ���ɢ�б��Сȡ������Ϊ��ַ����
            index = key % TABLE_SIZE;
            break;
        case DIRECT: // ֱ�Ӷ�ַ�����ùؼ��ֳ���һ��������Ϊ��ַ����
            index = key * 2;
            break;
        case DIGIT: // ���ַ��������ùؼ�����ĳ��λ������Ϊ��ַ�������������ȡ����λ����
            index = key % 100;
            break;
        case SQUARE: // ƽ��ȡ�з����ùؼ���ƽ�����м伸λ������Ϊ��ַ�������������ȡ�м���λ����
            index = (key * key / 100) % 100;
            break;
        default: // �������������-1��ʾ��Ч��ַ
            index = -1;
            break;
        }
        return index;
    }

    // ���ݸ����Ĺؼ��ֺ�ɢ�е�ַ�������ͻ������һ������ֵ��ʾ���յĵ�ַ����
    int collision(int key, int index) {
        int i = index; // ��¼��ʼ��ַ����
        int j = 0; // ��¼̽�����
        switch (collisionType) { // ���ݲ�ͬ�ĳ�ͻ�������ͣ����ò�ͬ�ķ���
        case CHAINING: // ������������Ҫ�����ͻ��ֱ�ӷ��س�ʼ��ַ����
            break;
        case LINEAR: // ����̽�ⷨ���ó�ʼ��ַ��������̽�������ɢ�б��Сȡ������Ϊ�µĵ�ַ������ֱ���ҵ���λ���߻ص���ʼ��ַ
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = (index + j) % TABLE_SIZE;
                if (i == index) { // ����ص���ʼ��ַ��˵��ɢ�б�����������-1��ʾ��Ч��ַ
                    i = -1;
                    break;
                }
            }
            break;
        case QUADRATIC: // ƽ��̽�ⷨ���ó�ʼ��ַ��������̽�������ƽ����ɢ�б��Сȡ������Ϊ�µĵ�ַ������ֱ���ҵ���λ���߻ص���ʼ��ַ
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = (index + j * j) % TABLE_SIZE;
                if (i == index) { // ����ص���ʼ��ַ��˵��ɢ�б�����������-1��ʾ��Ч��ַ
                    i = -1;
                    break;
                }
            }
            break;
        case RANDOM: // α������з����ó�ʼ��ַ��������һ���������ɢ�б��Сȡ������Ϊ�µĵ�ַ������ֱ���ҵ���λ���߻ص���ʼ��ַ
            srand(time(NULL)); // ��ʼ���������
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = (index + rand()) % TABLE_SIZE;
                if (i == index) { // ����ص���ʼ��ַ��˵��ɢ�б�����������-1��ʾ��Ч��ַ
                    i = -1;
                    break;
                }
            }
            break;
        case REHASH: // ��ɢ�з�������һ��ɢ�к��������µĵ�ַ������ֱ���ҵ���λ���߻ص���ʼ��ַ
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = rehashFunc(key); // ������һ��ɢ�к���
                if (i == index) { // ����ص���ʼ��ַ��˵��ɢ�б�����������-1��ʾ��Ч��ַ
                    i = -1;
                    break;
                }
            }
            break;
        default: // �������������-1��ʾ��Ч��ַ
            i = -1;
            break;
        }
        return i;
    }

    // ������һ��ɢ�к�����������ɢ�з�����������ùؼ��ֳ���һ������ȡ������Ϊ�µĵ�ַ����
    int rehashFunc(int key) {
        return key % 7; // 7��һ��С��ɢ�б��С������
    }

    // ��ɢ�б��в�������Ĺؼ��ֺ�ֵ��������һ������ֵ��ʾ�Ƿ����ɹ���
    bool insert(int key, int value) {
        int index = hashFunc(key); // ����ɢ�е�ַ
        if (index == -1) { // �����Ч������false��ʾ����ʧ��
            return false;
        }
        index = collision(key, index); // �����ͻ
        if (index == -1) { // �����Ч������false��ʾ����ʧ��
            return false;
        }
        if (table[index] == NULL) { // �����λ��Ϊ�գ�����һ���µĽڵ㲢����
            table[index] = new HashNode(key, value);
            return true;
        }
        else if (table[index]->key == key) { // �����λ���Ѿ�����ͬ�Ĺؼ��֣�����ֵ������false��ʾ����ʧ��
            table[index]->value = value;
            return false;
        }
        else { // �����λ���в�ͬ�Ĺؼ��֣�˵���������������µĽڵ���뵽����ͷ��
            HashNode* p = new HashNode(key, value, table[index]);
            table[index] = p;
            return true;
        }
    }

    // ��ɢ�б��в��Ҹ����Ĺؼ��֣������ع�����ֵ���߿�ֵ��
    int search(int key) {
        int index = hashFunc(key); // ����ɢ�е�ַ
        if (index == -1) { // �����Ч�����ؿ�ֵ
            return 0;
        }
        index = collision(key, index); // �����ͻ
        if (index == -1) { // �����Ч�����ؿ�ֵ
            return 0;
        }
        if (table[index] == NULL) { // �����λ��Ϊ�գ����ؿ�ֵ
            return 0;
        }
        else if (table[index]->key == key) { // �����λ������ͬ�Ĺؼ��֣����ض�Ӧ��ֵ
            return table[index]->value;
        }
        else { // �����λ���в�ͬ�Ĺؼ��֣�˵�����������������������ƥ��Ľڵ㲢���ض�Ӧ��ֵ
            HashNode* p = table[index];
            while (p != NULL && p->key != key) {
                p = p->next;
            }
            if (p != NULL) {
                return p->value;
            }
            else {
                return 0;
            }
        }
    }

    // ��ɢ�б���ɾ�������Ĺؼ��֣������ر�ɾ����ֵ���߿�ֵ��
    int remove(int key) {
        int index = hashFunc(key); // ����ɢ�е�ַ
        if (index == -1) { // �����Ч�����ؿ�ֵ
            return 0;
        }
        index = collision(key, index); // �����ͻ
        if (index == -1) { // �����Ч�����ؿ�ֵ
            return 0;
        }
        if (table[index] == NULL) { // �����λ��Ϊ�գ����ؿ�ֵ
            return 0;
        }
        else if (table[index]->key == key) { // �����λ������ͬ�Ĺؼ��֣�ɾ���ڵ㲢���ض�Ӧ��ֵ
            int value = table[index]->value;
            HashNode* p = table[index];
            table[index] = p->next; // ����̽ڵ��ƶ�����λ��
            delete p; // �ͷű�ɾ���ڵ�Ŀռ�
            return value;
        }
        else { // �����λ���в�ͬ�Ĺؼ��֣�˵�����������������������ƥ��Ľڵ㲢ɾ�������ض�Ӧ��ֵ
            HashNode* p = table[index];
            HashNode* q = NULL; // ��¼ǰ���ڵ�
            while (p != NULL && p->key != key) {
                q = p;
                p = p->next;
            }
            if (p != NULL) {
                int value = p->value;
                q->next = p->next; // ��ǰ���ڵ�ָ���̽ڵ�
                delete p; // �ͷű�ɾ���ڵ�Ŀռ�
                return value;
            }
            else {
                return 0;
            }
        }
    }

    // ��ӡɢ�б������е�Ԫ�ء�
    void print() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            HashNode* p = table[i];
            while (p != NULL) {
                cout << "(" << p->key << ", " << p->value << ") -> ";
                p = p->next;
            }
            cout << "NULL" << endl;
        }
    }
};

// �������������
int main() {
    // ����ɢ�б����ָ��ɢ�к����ͳ�ͻ���������
    HashTable ht(MOD, LINEAR);
    // ����ؼ�������
    int keys[] = { 19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79 };
    // ����ֵ����
    int values[] = { 65, 22, 24, 12, 13, 67, 34, 90, 56, 42, 31, 44 };
    // ��ɢ�б��в���Ԫ��
    for (int i = 0; i < sizeof(keys) / sizeof(int); i++) {
        ht.insert(keys[i], values[i]);
    }
    // ��ӡɢ�б��е�Ԫ��
    ht.print();
    // ����ɢ�б��е�Ԫ��
    cout << "Search key = 23: value = " << ht.search(23) << endl;
    cout << "Search key = 79: value = " << ht.search(79) << endl;
    cout << "Search key = 100: value = " << ht.search(100) << endl;
    // ɾ��ɢ�б��е�Ԫ��
    cout << "Remove key = 23: value = " << ht.remove(23) << endl;
    cout << "Remove key = 79: value = " << ht.remove(79) << endl;
    cout << "Remove key = 100: value = " << ht.remove(100) << endl;
    // �ٴδ�ӡɢ�б��е�Ԫ��
    ht.print();
    return 0;
}

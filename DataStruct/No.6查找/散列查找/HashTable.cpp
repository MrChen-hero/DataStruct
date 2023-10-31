#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// 定义散列表的大小
const int TABLE_SIZE = 13;

// 定义散列函数的类型
enum HashFuncType {
    MOD, // 除留余数法
    DIRECT, // 直接定址法
    DIGIT, // 数字分析法
    SQUARE // 平方取中法
};

// 定义冲突处理的类型
enum CollisionType {
    CHAINING, // 拉链法
    LINEAR, // 线性探测法
    QUADRATIC, // 平方探测法
    RANDOM, // 伪随机序列法
    REHASH // 再散列法
};

// 定义散列表节点的结构体
struct HashNode {
    int key; // 关键字
    int value; // 值
    HashNode* next; // 指向下一个节点的指针，用于拉链法
    HashNode(int k = 0, int v = 0, HashNode* n = NULL) : key(k), value(v), next(n) {} // 构造函数
};

// 定义散列表的类
class HashTable {
private:
    vector<HashNode*> table; // 散列表数组，每个元素是一个指针，指向一个节点或者NULL
    HashFuncType hashFuncType; // 散列函数的类型
    CollisionType collisionType; // 冲突处理的类型

public:
    // 构造函数，初始化一个空的散列表，并指定散列函数和冲突处理的类型
    HashTable(HashFuncType hft = MOD, CollisionType ct = CHAINING) {
        table.resize(TABLE_SIZE); // 分配散列表大小的空间
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL; // 初始化每个元素为NULL
        }
        hashFuncType = hft; // 设置散列函数的类型
        collisionType = ct; // 设置冲突处理的类型
    }

    // 析构函数，释放散列表占用的内存空间
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* p = table[i]; // 获取每个元素指向的节点
            while (p != NULL) { // 遍历该节点后面的链表，并释放每个节点的空间
                HashNode* q = p->next;
                delete p;
                p = q;
            }
        }
    }

    // 根据给定的关键字，计算其散列地址，返回一个整型值表示地址索引
    int hashFunc(int key) {
        int index;
        switch (hashFuncType) { // 根据不同的散列函数类型，采用不同的计算方法
        case MOD: // 除留余数法，用关键字除以散列表大小取余数作为地址索引
            index = key % TABLE_SIZE;
            break;
        case DIRECT: // 直接定址法，用关键字乘以一个常数作为地址索引
            index = key * 2;
            break;
        case DIGIT: // 数字分析法，用关键字中某几位数字作为地址索引，这里假设取后两位数字
            index = key % 100;
            break;
        case SQUARE: // 平方取中法，用关键字平方后中间几位数字作为地址索引，这里假设取中间两位数字
            index = (key * key / 100) % 100;
            break;
        default: // 其他情况，返回-1表示无效地址
            index = -1;
            break;
        }
        return index;
    }

    // 根据给定的关键字和散列地址，处理冲突，返回一个整型值表示最终的地址索引
    int collision(int key, int index) {
        int i = index; // 记录初始地址索引
        int j = 0; // 记录探测次数
        switch (collisionType) { // 根据不同的冲突处理类型，采用不同的方法
        case CHAINING: // 拉链法，不需要处理冲突，直接返回初始地址索引
            break;
        case LINEAR: // 线性探测法，用初始地址索引加上探测次数对散列表大小取余数作为新的地址索引，直到找到空位或者回到初始地址
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = (index + j) % TABLE_SIZE;
                if (i == index) { // 如果回到初始地址，说明散列表已满，返回-1表示无效地址
                    i = -1;
                    break;
                }
            }
            break;
        case QUADRATIC: // 平方探测法，用初始地址索引加上探测次数的平方对散列表大小取余数作为新的地址索引，直到找到空位或者回到初始地址
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = (index + j * j) % TABLE_SIZE;
                if (i == index) { // 如果回到初始地址，说明散列表已满，返回-1表示无效地址
                    i = -1;
                    break;
                }
            }
            break;
        case RANDOM: // 伪随机序列法，用初始地址索引加上一个随机数对散列表大小取余数作为新的地址索引，直到找到空位或者回到初始地址
            srand(time(NULL)); // 初始化随机种子
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = (index + rand()) % TABLE_SIZE;
                if (i == index) { // 如果回到初始地址，说明散列表已满，返回-1表示无效地址
                    i = -1;
                    break;
                }
            }
            break;
        case REHASH: // 再散列法，用另一个散列函数计算新的地址索引，直到找到空位或者回到初始地址
            while (table[i] != NULL && table[i]->key != key) {
                j++;
                i = rehashFunc(key); // 调用另一个散列函数
                if (i == index) { // 如果回到初始地址，说明散列表已满，返回-1表示无效地址
                    i = -1;
                    break;
                }
            }
            break;
        default: // 其他情况，返回-1表示无效地址
            i = -1;
            break;
        }
        return i;
    }

    // 定义另一个散列函数，用于再散列法，这里假设用关键字除以一个质数取余数作为新的地址索引
    int rehashFunc(int key) {
        return key % 7; // 7是一个小于散列表大小的质数
    }

    // 在散列表中插入给定的关键字和值，并返回一个布尔值表示是否插入成功。
    bool insert(int key, int value) {
        int index = hashFunc(key); // 计算散列地址
        if (index == -1) { // 如果无效，返回false表示插入失败
            return false;
        }
        index = collision(key, index); // 处理冲突
        if (index == -1) { // 如果无效，返回false表示插入失败
            return false;
        }
        if (table[index] == NULL) { // 如果该位置为空，创建一个新的节点并插入
            table[index] = new HashNode(key, value);
            return true;
        }
        else if (table[index]->key == key) { // 如果该位置已经有相同的关键字，更新值并返回false表示插入失败
            table[index]->value = value;
            return false;
        }
        else { // 如果该位置有不同的关键字，说明是拉链法，将新的节点插入到链表头部
            HashNode* p = new HashNode(key, value, table[index]);
            table[index] = p;
            return true;
        }
    }

    // 在散列表中查找给定的关键字，并返回关联的值或者空值。
    int search(int key) {
        int index = hashFunc(key); // 计算散列地址
        if (index == -1) { // 如果无效，返回空值
            return 0;
        }
        index = collision(key, index); // 处理冲突
        if (index == -1) { // 如果无效，返回空值
            return 0;
        }
        if (table[index] == NULL) { // 如果该位置为空，返回空值
            return 0;
        }
        else if (table[index]->key == key) { // 如果该位置有相同的关键字，返回对应的值
            return table[index]->value;
        }
        else { // 如果该位置有不同的关键字，说明是拉链法，遍历链表查找匹配的节点并返回对应的值
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

    // 在散列表中删除给定的关键字，并返回被删除的值或者空值。
    int remove(int key) {
        int index = hashFunc(key); // 计算散列地址
        if (index == -1) { // 如果无效，返回空值
            return 0;
        }
        index = collision(key, index); // 处理冲突
        if (index == -1) { // 如果无效，返回空值
            return 0;
        }
        if (table[index] == NULL) { // 如果该位置为空，返回空值
            return 0;
        }
        else if (table[index]->key == key) { // 如果该位置有相同的关键字，删除节点并返回对应的值
            int value = table[index]->value;
            HashNode* p = table[index];
            table[index] = p->next; // 将后继节点移动到该位置
            delete p; // 释放被删除节点的空间
            return value;
        }
        else { // 如果该位置有不同的关键字，说明是拉链法，遍历链表查找匹配的节点并删除并返回对应的值
            HashNode* p = table[index];
            HashNode* q = NULL; // 记录前驱节点
            while (p != NULL && p->key != key) {
                q = p;
                p = p->next;
            }
            if (p != NULL) {
                int value = p->value;
                q->next = p->next; // 将前驱节点指向后继节点
                delete p; // 释放被删除节点的空间
                return value;
            }
            else {
                return 0;
            }
        }
    }

    // 打印散列表中所有的元素。
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

// 定义测试主函数
int main() {
    // 定义散列表对象，指定散列函数和冲突处理的类型
    HashTable ht(MOD, LINEAR);
    // 定义关键字数组
    int keys[] = { 19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79 };
    // 定义值数组
    int values[] = { 65, 22, 24, 12, 13, 67, 34, 90, 56, 42, 31, 44 };
    // 向散列表中插入元素
    for (int i = 0; i < sizeof(keys) / sizeof(int); i++) {
        ht.insert(keys[i], values[i]);
    }
    // 打印散列表中的元素
    ht.print();
    // 查找散列表中的元素
    cout << "Search key = 23: value = " << ht.search(23) << endl;
    cout << "Search key = 79: value = " << ht.search(79) << endl;
    cout << "Search key = 100: value = " << ht.search(100) << endl;
    // 删除散列表中的元素
    cout << "Remove key = 23: value = " << ht.remove(23) << endl;
    cout << "Remove key = 79: value = " << ht.remove(79) << endl;
    cout << "Remove key = 100: value = " << ht.remove(100) << endl;
    // 再次打印散列表中的元素
    ht.print();
    return 0;
}

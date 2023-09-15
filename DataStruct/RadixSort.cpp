#include <iostream>
#include <queue>
using namespace std;

// 获取一个整数的第d位数字，d从1开始，个位为1，十位为2，依次类推
int GetDigit(int x, int d) {
    int base = 1; // 基数，初始为1
    while (d > 1) { // 循环d-1次，将基数乘以10
        base *= 10;
        d--;
    }
    return (x / base) % 10; // 返回x除以基数后的余数
}

// 基数排序
void RadixSort(int a[], int n) {
    int max = a[0]; // 记录数组中的最大值
    for (int i = 1; i < n; i++) { // 遍历数组，找到最大值
        if (a[i] > max) {
            max = a[i];
        }
    }
    int d = 0; // 记录最大值的位数
    while (max > 0) { // 循环除以10，直到最大值为0
        max /= 10;
        d++;
    }
    queue<int> q[10]; // 定义一个队列数组，用于存放每一位数字的桶
    for (int i = 1; i <= d; i++) { // 对每一位数字进行分配和收集
        for (int j = 0; j < n; j++) { // 遍历数组，将每个元素按照第i位的数字放入对应的桶中
            int k = GetDigit(a[j], i); // 获取第i位的数字
            q[k].push(a[j]); // 将元素放入第k个桶中
        }
        int index = 0; // 记录数组的下标
        for (int j = 0; j < 10; j++) { // 遍历每个桶，将桶中的元素依次放回数组中
            while (!q[j].empty()) { // 当桶不为空时，循环出队并赋值给数组
                a[index++] = q[j].front(); // 将队首元素赋值给数组，并将下标加一
                q[j].pop(); // 将队首元素出队
            }
        }
    }
}

// 测试主函数
int main() {
    int a[] = { 49, 38, 65, 97, 76, 13, 27, 49 }; // 定义一个数组
    int n = sizeof(a) / sizeof(a[0]); // 计算数组长度

    cout << "原始数组为：" << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "基数排序后的数组为：" << endl;
    RadixSort(a, n); // 调用基数排序函数
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

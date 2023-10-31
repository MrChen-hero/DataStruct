#include <iostream>
using namespace std;

// 交换两个元素的值
void Swap(int& a, int& b) {
    int temp = a; // 用一个临时变量保存a的值
    a = b; // 将b的值赋给a
    b = temp; // 将临时变量的值赋给b
}

// 简单选择排序
void SelectSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) { // 外层循环控制排序的趟数，最多n-1趟
        int min = i; // 记录当前最小元素的下标，初始为i
        for (int j = i + 1; j < n; j++) { // 内层循环控制每一趟的比较次数，从i+1开始比较n-i-1次
            if (a[j] < a[min]) { // 如果找到一个元素小于当前最小元素，则更新最小元素的下标为j
                min = j;
            }
        }
        if (min != i) { // 如果最小元素的下标发生了变化，则交换它们的位置
            Swap(a[i], a[min]);
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

    cout << "简单选择排序后的数组为：" << endl;
    SelectSort(a, n); // 调用简单选择排序函数
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

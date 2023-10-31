#include <iostream>
using namespace std;

// 交换两个元素的值
void Swap(int& a, int& b) {
    int temp = a; // 用一个临时变量保存a的值
    a = b; // 将b的值赋给a
    b = temp; // 将临时变量的值赋给b
}

// 冒泡排序
void BubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) { // 外层循环控制排序的趟数，最多n-1趟
        bool flag = false; // 定义一个标志变量，用于判断是否发生了交换
        for (int j = 0; j < n - i - 1; j++) { // 内层循环控制每一趟的比较次数，每趟比较n-i-1次
            if (a[j] > a[j + 1]) { // 如果相邻的两个元素逆序，则交换它们的位置
                Swap(a[j], a[j + 1]);
                flag = true; // 将标志变量设为true，表示发生了交换
            }
        }
        if (!flag) { // 如果一趟比较中没有发生交换，说明数组已经有序，可以提前结束排序
            break;
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

    cout << "冒泡排序后的数组为：" << endl;
    BubbleSort(a, n); // 调用冒泡排序函数
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

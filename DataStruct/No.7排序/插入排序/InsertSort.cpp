#include <iostream>
using namespace std;

// 直接插入排序
void InsertSort(int a[], int n) {
    for (int i = 1; i < n; i++) { // 从第二个元素开始
        int temp = a[i]; // 保存待插入元素
        int j = i - 1; // 指向已排序序列的最后一个元素
        while (j >= 0 && temp < a[j]) { // 在已排序序列中从后往前查找插入位置
            a[j + 1] = a[j]; // 将大于temp的元素后移
            j--; // 继续向前比较
        }
        a[j + 1] = temp; // 将temp插入到合适的位置
    }
}

// 折半插入排序
void BinaryInsertSort(int a[], int n) {
    for (int i = 1; i < n; i++) { // 从第二个元素开始
        int temp = a[i]; // 保存待插入元素
        int low = 0, high = i - 1; // 定义折半查找的范围
        while (low <= high) { // 在范围内进行折半查找
            int mid = (low + high) / 2; // 计算中间位置
            if (temp < a[mid]) { // 如果待插入元素小于中间元素，则在左半部分查找
                high = mid - 1;
            }
            else { // 否则在右半部分查找
                low = mid + 1;
            }
        }
        for (int j = i - 1; j >= low; j--) { // 将low到i-1之间的元素后移一位
            a[j + 1] = a[j];
        }
        a[low] = temp; // 将temp插入到low位置
    }
}

// 希尔排序
void ShellSort(int a[], int n) {
    int gap = n / 2; // 初始增量为n/2
    while (gap > 0) { // 当增量大于0时进行排序
        for (int i = gap; i < n; i++) { // 对每个子序列进行直接插入排序
            int temp = a[i]; // 保存待插入元素
            int j = i - gap; // 指向已排序序列的最后一个元素
            while (j >= 0 && temp < a[j]) { // 在已排序序列中从后往前查找插入位置
                a[j + gap] = a[j]; // 将大于temp的元素后移gap位
                j -= gap; // 继续向前比较，间隔为gap
            }
            a[j + gap] = temp; // 将temp插入到合适的位置
        }
        gap /= 2; // 减小增量，继续进行排序
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

    cout << "直接插入排序后的数组为：" << endl;
    InsertSort(a, n); // 调用直接插入排序函数
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "折半插入排序后的数组为：" << endl;
    BinaryInsertSort(a, n); // 调用折半插入排序函数
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "希尔排序后的数组为：" << endl;
    ShellSort(a, n); // 调用希尔排序函数
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

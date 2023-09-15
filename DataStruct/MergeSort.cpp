#include <iostream>
using namespace std;

// 归并两个有序数组
void Merge(int a[], int low, int mid, int high) {
    int i = low, j = mid + 1; // 定义两个指针分别指向两个数组的起始位置
    int k = 0; // 定义一个临时数组的下标
    int* temp = new int[high - low + 1]; // 动态分配一个临时数组，用于存放合并后的结果
    while (i <= mid && j <= high) { // 当两个数组都有元素时，比较大小并放入临时数组
        if (a[i] <= a[j]) { // 如果左边数组的元素小于等于右边数组的元素，则将左边元素放入临时数组
            temp[k++] = a[i++];
        }
        else { // 否则将右边元素放入临时数组
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) { // 如果左边数组还有剩余元素，则将其全部放入临时数组
        temp[k++] = a[i++];
    }
    while (j <= high) { // 如果右边数组还有剩余元素，则将其全部放入临时数组
        temp[k++] = a[j++];
    }
    for (int i = low; i <= high; i++) { // 将临时数组中的元素复制回原数组
        a[i] = temp[i - low];
    }
    delete[] temp; // 释放临时数组的空间
}

// 归并排序
void MergeSort(int a[], int low, int high) {
    if (low < high) { // 如果待排序序列长度大于1，则进行分治递归
        int mid = (low + high) / 2; // 计算中间位置
        MergeSort(a, low, mid); // 对左半部分进行归并排序
        MergeSort(a, mid + 1, high); // 对右半部分进行归并排序
        Merge(a, low, mid, high); // 将两个有序子序列合并为一个有序序列
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

    cout << "归并排序后的数组为：" << endl;
    MergeSort(a, 0, n - 1); // 调用归并排序函数，传入起始和终止下标
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

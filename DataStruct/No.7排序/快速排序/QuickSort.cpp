#include <iostream>
using namespace std;

// 交换两个元素的值
void Swap(int& a, int& b) {
    int temp = a; // 用一个临时变量保存a的值
    a = b; // 将b的值赋给a
    b = temp; // 将临时变量的值赋给b
}

// 划分函数，传入待排序数组a，起始下标low，终止下标high
int Partition(int a[], int low, int high) {
    int pivot = a[low]; // 选择第一个元素作为基准元素
    while (low < high) { // 当low和high没有相遇时，循环进行划分
        while (low < high && a[high] >= pivot) { // 从右向左找到第一个小于基准元素的元素
            high--; // 将high减一
        }
        Swap(a[low], a[high]); // 将该元素与基准元素交换位置
        while (low < high && a[low] <= pivot) { // 从左向右找到第一个大于基准元素的元素
            low++; // 将low加一
        }
        Swap(a[low], a[high]); // 将该元素与基准元素交换位置
    }
    return low; // 返回基准元素的最终位置
}

// 快速排序
void QuickSort(int a[], int low, int high) {
    if (low < high) { // 如果待排序序列长度大于1，则进行分治递归
        int pivotpos = Partition(a, low, high); // 调用划分函数，返回基准元素的位置
        QuickSort(a, low, pivotpos - 1); // 对左半部分进行快速排序
        QuickSort(a, pivotpos + 1, high); // 对右半部分进行快速排序
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

    cout << "快速排序后的数组为：" << endl;
    QuickSort(a, 0, n - 1); // 调用快速排序函数，传入起始和终止下标
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

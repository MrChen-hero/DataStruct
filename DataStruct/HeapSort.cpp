#include <iostream>
using namespace std;

// 交换两个元素的值
void Swap(int& a, int& b) {
    int temp = a; // 用一个临时变量保存a的值
    a = b; // 将b的值赋给a
    b = temp; // 将临时变量的值赋给b
}

// 调整堆，传入待排序数组a，当前结点编号i，堆的大小n
void AdjustHeap(int a[], int i, int n) {
    int temp = a[i]; // 保存当前结点的值
    int j = 2 * i + 1; // 计算当前结点的左孩子在数组中的位置
    while (j < n) { // 当左孩子存在时，循环进行调整
        if (j + 1 < n && a[j + 1] > a[j]) { // 如果右孩子也存在，并且右孩子的值大于左孩子的值，则将j指向右孩子
            j++;
        }
        if (a[j] > temp) { // 如果孩子结点的值大于当前结点的值，则将孩子结点的值赋给当前结点，并将当前结点下沉到孩子结点
            a[i] = a[j];
            i = j;
            j = 2 * i + 1;
        }
        else { // 否则说明当前结点已经满足大顶堆的性质，可以结束调整
            break;
        }
    }
    a[i] = temp; // 将原来的当前结点的值放到最终的位置上
}

// 堆排序
void HeapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) { // 从最后一个非叶子结点开始，从下往上，从右往左，依次调整每个结点，建立初始大顶堆
        AdjustHeap(a, i, n);
    }
    for (int i = n - 1; i > 0; i--) { // 循环n-1次，每次将堆顶元素与最后一个元素交换位置，并重新调整堆
        Swap(a[0], a[i]); // 将堆顶元素与最后一个元素交换位置
        AdjustHeap(a, 0, i); // 将剩余的元素重新调整为大顶堆
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

    cout << "堆排序后的数组为：" << endl;
    HeapSort(a, n); // 调用堆排序函数
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

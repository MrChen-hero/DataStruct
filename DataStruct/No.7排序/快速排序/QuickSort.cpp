#include <iostream>
using namespace std;

// ��������Ԫ�ص�ֵ
void Swap(int& a, int& b) {
    int temp = a; // ��һ����ʱ��������a��ֵ
    a = b; // ��b��ֵ����a
    b = temp; // ����ʱ������ֵ����b
}

// ���ֺ������������������a����ʼ�±�low����ֹ�±�high
int Partition(int a[], int low, int high) {
    int pivot = a[low]; // ѡ���һ��Ԫ����Ϊ��׼Ԫ��
    while (low < high) { // ��low��highû������ʱ��ѭ�����л���
        while (low < high && a[high] >= pivot) { // ���������ҵ���һ��С�ڻ�׼Ԫ�ص�Ԫ��
            high--; // ��high��һ
        }
        Swap(a[low], a[high]); // ����Ԫ�����׼Ԫ�ؽ���λ��
        while (low < high && a[low] <= pivot) { // ���������ҵ���һ�����ڻ�׼Ԫ�ص�Ԫ��
            low++; // ��low��һ
        }
        Swap(a[low], a[high]); // ����Ԫ�����׼Ԫ�ؽ���λ��
    }
    return low; // ���ػ�׼Ԫ�ص�����λ��
}

// ��������
void QuickSort(int a[], int low, int high) {
    if (low < high) { // ������������г��ȴ���1������з��εݹ�
        int pivotpos = Partition(a, low, high); // ���û��ֺ��������ػ�׼Ԫ�ص�λ��
        QuickSort(a, low, pivotpos - 1); // ����벿�ֽ��п�������
        QuickSort(a, pivotpos + 1, high); // ���Ұ벿�ֽ��п�������
    }
}

// ����������
int main() {
    int a[] = { 49, 38, 65, 97, 76, 13, 27, 49 }; // ����һ������
    int n = sizeof(a) / sizeof(a[0]); // �������鳤��

    cout << "ԭʼ����Ϊ��" << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "��������������Ϊ��" << endl;
    QuickSort(a, 0, n - 1); // ���ÿ�����������������ʼ����ֹ�±�
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

#include <iostream>
using namespace std;

// �鲢������������
void Merge(int a[], int low, int mid, int high) {
    int i = low, j = mid + 1; // ��������ָ��ֱ�ָ�������������ʼλ��
    int k = 0; // ����һ����ʱ������±�
    int* temp = new int[high - low + 1]; // ��̬����һ����ʱ���飬���ڴ�źϲ���Ľ��
    while (i <= mid && j <= high) { // ���������鶼��Ԫ��ʱ���Ƚϴ�С��������ʱ����
        if (a[i] <= a[j]) { // �����������Ԫ��С�ڵ����ұ������Ԫ�أ������Ԫ�ط�����ʱ����
            temp[k++] = a[i++];
        }
        else { // �����ұ�Ԫ�ط�����ʱ����
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) { // ���������黹��ʣ��Ԫ�أ�����ȫ��������ʱ����
        temp[k++] = a[i++];
    }
    while (j <= high) { // ����ұ����黹��ʣ��Ԫ�أ�����ȫ��������ʱ����
        temp[k++] = a[j++];
    }
    for (int i = low; i <= high; i++) { // ����ʱ�����е�Ԫ�ظ��ƻ�ԭ����
        a[i] = temp[i - low];
    }
    delete[] temp; // �ͷ���ʱ����Ŀռ�
}

// �鲢����
void MergeSort(int a[], int low, int high) {
    if (low < high) { // ������������г��ȴ���1������з��εݹ�
        int mid = (low + high) / 2; // �����м�λ��
        MergeSort(a, low, mid); // ����벿�ֽ��й鲢����
        MergeSort(a, mid + 1, high); // ���Ұ벿�ֽ��й鲢����
        Merge(a, low, mid, high); // ���������������кϲ�Ϊһ����������
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

    cout << "�鲢����������Ϊ��" << endl;
    MergeSort(a, 0, n - 1); // ���ù鲢��������������ʼ����ֹ�±�
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

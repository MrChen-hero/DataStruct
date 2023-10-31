#include <iostream>
using namespace std;

// ֱ�Ӳ�������
void InsertSort(int a[], int n) {
    for (int i = 1; i < n; i++) { // �ӵڶ���Ԫ�ؿ�ʼ
        int temp = a[i]; // ���������Ԫ��
        int j = i - 1; // ָ�����������е����һ��Ԫ��
        while (j >= 0 && temp < a[j]) { // �������������дӺ���ǰ���Ҳ���λ��
            a[j + 1] = a[j]; // ������temp��Ԫ�غ���
            j--; // ������ǰ�Ƚ�
        }
        a[j + 1] = temp; // ��temp���뵽���ʵ�λ��
    }
}

// �۰��������
void BinaryInsertSort(int a[], int n) {
    for (int i = 1; i < n; i++) { // �ӵڶ���Ԫ�ؿ�ʼ
        int temp = a[i]; // ���������Ԫ��
        int low = 0, high = i - 1; // �����۰���ҵķ�Χ
        while (low <= high) { // �ڷ�Χ�ڽ����۰����
            int mid = (low + high) / 2; // �����м�λ��
            if (temp < a[mid]) { // ���������Ԫ��С���м�Ԫ�أ�������벿�ֲ���
                high = mid - 1;
            }
            else { // �������Ұ벿�ֲ���
                low = mid + 1;
            }
        }
        for (int j = i - 1; j >= low; j--) { // ��low��i-1֮���Ԫ�غ���һλ
            a[j + 1] = a[j];
        }
        a[low] = temp; // ��temp���뵽lowλ��
    }
}

// ϣ������
void ShellSort(int a[], int n) {
    int gap = n / 2; // ��ʼ����Ϊn/2
    while (gap > 0) { // ����������0ʱ��������
        for (int i = gap; i < n; i++) { // ��ÿ�������н���ֱ�Ӳ�������
            int temp = a[i]; // ���������Ԫ��
            int j = i - gap; // ָ�����������е����һ��Ԫ��
            while (j >= 0 && temp < a[j]) { // �������������дӺ���ǰ���Ҳ���λ��
                a[j + gap] = a[j]; // ������temp��Ԫ�غ���gapλ
                j -= gap; // ������ǰ�Ƚϣ����Ϊgap
            }
            a[j + gap] = temp; // ��temp���뵽���ʵ�λ��
        }
        gap /= 2; // ��С������������������
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

    cout << "ֱ�Ӳ�������������Ϊ��" << endl;
    InsertSort(a, n); // ����ֱ�Ӳ���������
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "�۰��������������Ϊ��" << endl;
    BinaryInsertSort(a, n); // �����۰����������
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "ϣ������������Ϊ��" << endl;
    ShellSort(a, n); // ����ϣ��������
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

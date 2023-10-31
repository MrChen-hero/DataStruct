#include <iostream>
#include <queue>
using namespace std;

// ��ȡһ�������ĵ�dλ���֣�d��1��ʼ����λΪ1��ʮλΪ2����������
int GetDigit(int x, int d) {
    int base = 1; // ��������ʼΪ1
    while (d > 1) { // ѭ��d-1�Σ�����������10
        base *= 10;
        d--;
    }
    return (x / base) % 10; // ����x���Ի����������
}

// ��������
void RadixSort(int a[], int n) {
    int max = a[0]; // ��¼�����е����ֵ
    for (int i = 1; i < n; i++) { // �������飬�ҵ����ֵ
        if (a[i] > max) {
            max = a[i];
        }
    }
    int d = 0; // ��¼���ֵ��λ��
    while (max > 0) { // ѭ������10��ֱ�����ֵΪ0
        max /= 10;
        d++;
    }
    queue<int> q[10]; // ����һ���������飬���ڴ��ÿһλ���ֵ�Ͱ
    for (int i = 1; i <= d; i++) { // ��ÿһλ���ֽ��з�����ռ�
        for (int j = 0; j < n; j++) { // �������飬��ÿ��Ԫ�ذ��յ�iλ�����ַ����Ӧ��Ͱ��
            int k = GetDigit(a[j], i); // ��ȡ��iλ������
            q[k].push(a[j]); // ��Ԫ�ط����k��Ͱ��
        }
        int index = 0; // ��¼������±�
        for (int j = 0; j < 10; j++) { // ����ÿ��Ͱ����Ͱ�е�Ԫ�����ηŻ�������
            while (!q[j].empty()) { // ��Ͱ��Ϊ��ʱ��ѭ�����Ӳ���ֵ������
                a[index++] = q[j].front(); // ������Ԫ�ظ�ֵ�����飬�����±��һ
                q[j].pop(); // ������Ԫ�س���
            }
        }
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
    RadixSort(a, n); // ���û���������
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

#include <iostream>
using namespace std;

// ��������Ԫ�ص�ֵ
void Swap(int& a, int& b) {
    int temp = a; // ��һ����ʱ��������a��ֵ
    a = b; // ��b��ֵ����a
    b = temp; // ����ʱ������ֵ����b
}

// ð������
void BubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) { // ���ѭ��������������������n-1��
        bool flag = false; // ����һ����־�����������ж��Ƿ����˽���
        for (int j = 0; j < n - i - 1; j++) { // �ڲ�ѭ������ÿһ�˵ıȽϴ�����ÿ�˱Ƚ�n-i-1��
            if (a[j] > a[j + 1]) { // ������ڵ�����Ԫ�������򽻻����ǵ�λ��
                Swap(a[j], a[j + 1]);
                flag = true; // ����־������Ϊtrue����ʾ�����˽���
            }
        }
        if (!flag) { // ���һ�˱Ƚ���û�з���������˵�������Ѿ����򣬿�����ǰ��������
            break;
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

    cout << "ð������������Ϊ��" << endl;
    BubbleSort(a, n); // ����ð��������
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

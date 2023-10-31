#include <iostream>
using namespace std;

// ��������Ԫ�ص�ֵ
void Swap(int& a, int& b) {
    int temp = a; // ��һ����ʱ��������a��ֵ
    a = b; // ��b��ֵ����a
    b = temp; // ����ʱ������ֵ����b
}

// ��ѡ������
void SelectSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) { // ���ѭ��������������������n-1��
        int min = i; // ��¼��ǰ��СԪ�ص��±꣬��ʼΪi
        for (int j = i + 1; j < n; j++) { // �ڲ�ѭ������ÿһ�˵ıȽϴ�������i+1��ʼ�Ƚ�n-i-1��
            if (a[j] < a[min]) { // ����ҵ�һ��Ԫ��С�ڵ�ǰ��СԪ�أ��������СԪ�ص��±�Ϊj
                min = j;
            }
        }
        if (min != i) { // �����СԪ�ص��±귢���˱仯���򽻻����ǵ�λ��
            Swap(a[i], a[min]);
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

    cout << "��ѡ������������Ϊ��" << endl;
    SelectSort(a, n); // ���ü�ѡ��������
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

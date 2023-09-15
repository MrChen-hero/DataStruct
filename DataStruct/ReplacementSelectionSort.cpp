//author:Mitchell
//date:6.8
#include<iostream>
using namespace std;

template<class T>
class MinHeap {
public:
	T* heapArray;//��Ŷ����ݵ�����
	int currentSize;//��ǰ���е�Ԫ�ظ���
	int maxSize;//�ѵĴ�С

	//����λ��x��λ��y��Ԫ��
	void swap(int x, int y) {
		T pas = heapArray[x];
		heapArray[x] = heapArray[y];
		heapArray[y] = pas;
	}
	//���캯��������mΪ�ѵĴ�С������nΪ����Ĵ�С
	MinHeap(T Array[], const int m, const int n) {
		if (n <= 0) {
			currentSize = 0;
			maxSize = 0;
			heapArray = new T;
			return;
		}
		maxSize = m;
		currentSize = n;
		heapArray = new T[maxSize];
		for (int i = 0; i < currentSize; i++) {
			heapArray[i] = Array[i];
		}
		for (int i = currentSize / 2 - 1; i >= 0; i--) {
			SiftDown(i);
		}
	}
	//����������
	virtual ~MinHeap() {
		delete[]heapArray;
	}
	//�ж��Ƿ�ΪҶ���
	bool isLeaf(int pos)const {
		return (pos >= currentSize / 2) && (pos < currentSize);
	}
	//�������ӵ�λ��
	int LeftChild(int pos)const {
		return 2 * pos + 1;
	}
	//�����Һ��ӵ�λ��
	int RightChild(int pos)const {
		return 2 * pos + 2;
	}
	//���ظ�����λ��
	int Parent(int pos)const {
		return (pos - 1) / 2;
	}
	//����в�����Ԫ��
	bool Insert(const T& newNode) {
		if (currentSize == maxSize) {
			return false;
		}
		heapArray[currentSize] = newNode;
		SiftUp(currentSize++);
		return true;
	}
	//�ӶѶ�ɾ����Сֵ
	T RemoveMin() {
		if (currentSize == 0) {
			cout << "Can't Delete!";
			exit(1);
		}
		else {
			swap(0, --currentSize);
			if (currentSize > 1) {
				SiftDown(0);
			}
			return heapArray[currentSize];
		}
	}
	//��pos��ʼ���ϵ���
	void SiftUp(int pos) {
		int temppos = pos;
		T temp = heapArray[temppos];
		while ((temppos > 0) && (heapArray[Parent(temppos)] > temp)) {
			heapArray[temppos] = heapArray[Parent(temppos)];
			temppos = Parent(temppos);
		}
		heapArray[temppos] = temp;
	}
	//��pos��ʼ����ɸѡ
	void SiftDown(int pos) {
		int i = pos;
		int j = LeftChild(i);
		T temp = heapArray[i];
		while (j < currentSize) {
			if ((j < currentSize - 1) && (heapArray[j] > heapArray[j + 1])) {
				j++;
			}
			if (temp > heapArray[j]) {
				heapArray[i] = heapArray[j];
				i = j;
				j = LeftChild(j);
			}
			else {
				break;
			}
		}
		heapArray[i] = temp;
	}
};




template<class T>
void replacementSelection(T Array[], int ArraySize, int size) {
	MinHeap<T> H(Array, size, size);
	int remain = size;//ʣ�������Ԫ������
	int count = 1;//��������
	cout << endl << "��" << count << "�飺 ";
	while (remain < ArraySize) {
		cout << H.heapArray[0] << " ";
		if (Array[remain] >= H.heapArray[0]) {
			H.heapArray[0] = Array[remain++];
		}
		else {
			H.heapArray[0] = H.heapArray[--H.currentSize];
			H.heapArray[H.currentSize] = Array[remain++];
		}
		if (H.currentSize > 0) {
			H.SiftDown(0);
		}
		else {
			//���½���
			H.currentSize = H.maxSize;
			for (int i = H.currentSize / 2 - 1; i >= 0; i--) {
				H.SiftDown(i);
			}
			cout << endl << "��" << ++count << "�飺 ";
		}
	}
	//���ʣ��Ķ���Ԫ��
	if (H.currentSize == H.maxSize) {
		while (H.currentSize > 0) {
			cout << H.heapArray[0] << " ";
			H.RemoveMin();
		}
	}
	else {
		int leftover = H.maxSize - H.currentSize;
		//������е�Ԫ��
		while (H.currentSize > 0) {
			cout << H.heapArray[0] << " ";
			H.RemoveMin();
		}
		//��ʣ�µ�Ԫ����������
		H.currentSize = leftover;
		for (int i = 0; i < H.currentSize; i++) {
			H.heapArray[i] = H.heapArray[H.maxSize - leftover + i];
		}
		//���¹�����
		for (int i = H.currentSize / 2 - 1; i >= 0; i--) {
			H.SiftDown(i);
		}
		cout << endl << "��" << ++count << "�飺 ";
		while (H.currentSize > 0) {
			cout << H.heapArray[0] << " ";
			H.RemoveMin();
		}
	}
}


int main() {
	int ArraySize, size;
	cout << "���г��ȣ�";//9
	cin >> ArraySize;
	int* Array = new int[ArraySize];
	cout << "�ؼ������У�";//50 49 35 45 30 25 15 60 27
	for (int i = 0; i < ArraySize; i++) {
		cin >> Array[i];
	}
	cout << "�ڴ��С��";
	cin >> size;//3
	replacementSelection(Array, ArraySize, size);
}
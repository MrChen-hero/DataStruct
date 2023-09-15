//author:Mitchell
//date:6.8
#include<iostream>
using namespace std;

template<class T>
class MinHeap {
public:
	T* heapArray;//存放堆数据的数组
	int currentSize;//当前堆中的元素个数
	int maxSize;//堆的大小

	//交换位置x和位置y的元素
	void swap(int x, int y) {
		T pas = heapArray[x];
		heapArray[x] = heapArray[y];
		heapArray[y] = pas;
	}
	//构造函数，参数m为堆的大小，参数n为数组的大小
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
	//虚析构函数
	virtual ~MinHeap() {
		delete[]heapArray;
	}
	//判断是否为叶结点
	bool isLeaf(int pos)const {
		return (pos >= currentSize / 2) && (pos < currentSize);
	}
	//返回左孩子的位置
	int LeftChild(int pos)const {
		return 2 * pos + 1;
	}
	//返回右孩子的位置
	int RightChild(int pos)const {
		return 2 * pos + 2;
	}
	//返回父结点的位置
	int Parent(int pos)const {
		return (pos - 1) / 2;
	}
	//向堆中插入新元素
	bool Insert(const T& newNode) {
		if (currentSize == maxSize) {
			return false;
		}
		heapArray[currentSize] = newNode;
		SiftUp(currentSize++);
		return true;
	}
	//从堆顶删除最小值
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
	//从pos开始向上调整
	void SiftUp(int pos) {
		int temppos = pos;
		T temp = heapArray[temppos];
		while ((temppos > 0) && (heapArray[Parent(temppos)] > temp)) {
			heapArray[temppos] = heapArray[Parent(temppos)];
			temppos = Parent(temppos);
		}
		heapArray[temppos] = temp;
	}
	//从pos开始向下筛选
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
	int remain = size;//剩余的数组元素索引
	int count = 1;//计数变量
	cout << endl << "第" << count << "组： ";
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
			//重新建堆
			H.currentSize = H.maxSize;
			for (int i = H.currentSize / 2 - 1; i >= 0; i--) {
				H.SiftDown(i);
			}
			cout << endl << "第" << ++count << "组： ";
		}
	}
	//输出剩余的堆内元素
	if (H.currentSize == H.maxSize) {
		while (H.currentSize > 0) {
			cout << H.heapArray[0] << " ";
			H.RemoveMin();
		}
	}
	else {
		int leftover = H.maxSize - H.currentSize;
		//输出堆中的元素
		while (H.currentSize > 0) {
			cout << H.heapArray[0] << " ";
			H.RemoveMin();
		}
		//把剩下的元素重新排序
		H.currentSize = leftover;
		for (int i = 0; i < H.currentSize; i++) {
			H.heapArray[i] = H.heapArray[H.maxSize - leftover + i];
		}
		//重新构建树
		for (int i = H.currentSize / 2 - 1; i >= 0; i--) {
			H.SiftDown(i);
		}
		cout << endl << "第" << ++count << "组： ";
		while (H.currentSize > 0) {
			cout << H.heapArray[0] << " ";
			H.RemoveMin();
		}
	}
}


int main() {
	int ArraySize, size;
	cout << "序列长度：";//9
	cin >> ArraySize;
	int* Array = new int[ArraySize];
	cout << "关键码序列：";//50 49 35 45 30 25 15 60 27
	for (int i = 0; i < ArraySize; i++) {
		cin >> Array[i];
	}
	cout << "内存大小：";
	cin >> size;//3
	replacementSelection(Array, ArraySize, size);
}
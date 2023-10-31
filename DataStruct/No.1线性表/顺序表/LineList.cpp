#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10
#define EXTAND 10

typedef struct LineList {
	int* data;
	int length;
}LList;

void InitLineList(LList& L);	//初始化
void PrintList(LList& L);	//打印
void AddLineList(LList& L);	//扩容
void DestoryList(LList& L);	//销毁
bool InsertList(LList& L, int i, int e);	//按位序插入
bool DeleteList(LList& L, int i, int& e);	//按位序删除
//算法
bool Reverse(LList& L, int i, int e);	//反转元素
bool DeleteValue_1(LList& L, int x);	//删除值为x的元素
bool DeleteValue_2(LList& L, int x);	
bool Merge(LList L1, LList L2, LList& L3);	//合并表



//初始化
void InitLineList(LList &L){
	L.data = (int *)malloc(sizeof(int) * MAXSIZE);
	if (L.data == NULL) {
		printf("申请空间失败");
	}
	L.length = 0;
}

//扩容
void AddLineList(LList& L) {
	int* temp = L.data;
	int i;
	L.data = (int*)malloc(sizeof(int) * (MAXSIZE + EXTAND));
	if (L.data == NULL) {
		printf("申请内存失败");
		exit(0);
	}
	//将原表中数据复制到新表中
	for (i = 0; i < L.length; i++) {
		L.data[i] = temp[i];
	}
	free(temp);
	return ;
}

//销毁
void DestoryList(LList& L) {
	int* temp = L.data;
	L.data = NULL;
	free(temp);
	L.length = 0;
	return;
}

//打印
void PrintList(LList& L) {
	int i;
	for (i = 0; i < L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	return ;
}

//插入
bool InsertList(LList& L, int i,int e) {
	int j;
	if (i > L.length + 1 || i < 1) {
		return false;
	}
	//插入的重要操作 j >= i，找到第i-1个节点，将第i个及之后的节点后移
	for (j = L.length; j >= i; j--) {
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}

//删除
bool DeleteList(LList& L, int i,int &e) {
	int j;
	if (i > L.length || i < 0) {
		return false;
	}
	e = L.data[i - 1];
	//删除的重要操作  j < L.length，将第i个节点及之后的节点前移
	for (j = i; j < L.length; j++)
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return true;
}

int main() {
	LList list1;
	LList list2;
	LList list3;
	int e = 0;
	InitLineList(list1);
	InitLineList(list2);
	InitLineList(list3);
	//插入
	InsertList(list1, 1, 1);
	InsertList(list1, 2, 3);
	InsertList(list1, 3, 5);
	InsertList(list1, 4, 7);
	InsertList(list1, 5, 9);
	PrintList(list1);
	printf("\n");
	InsertList(list2, 1, 2);
	InsertList(list2, 2, 4);
	InsertList(list2, 3, 6);
	InsertList(list2, 4, 8);
	InsertList(list2, 5, 10);
	PrintList(list2);
	printf("\n");
	//删除
	/*
	DeleteList(list, 2, e);
	PrintList(list);
	printf("\n%d", e);
	*/
	//逆置
	/*
	Reverse(list, 4, 5);
	Reverse(list, 1, 3);
	Reverse(list, 1, 5);
	printf("\n");
	PrintList(list);
	*/
	//删除值为x的元素
	/*
	DeleteValue_1(list, 2);
	DeleteValue_2(list, 2);
	printf("\n");
	PrintList(list);
	*/
	//有序表合并
	Merge(list1, list2, list3);
	printf("\n");
	PrintList(list3);


	DestoryList(list1);
	DestoryList(list2);
	return 0;
}

//逆置表中的元素
bool Reverse(LList& L, int left, int right) {
	int j, mid, temp;
	//二分法逆置
	mid = (left + right) / 2;
	//此处应注意，j <= mid - left，是起到当left不为1时的循环次数问题
	//可以如此理解，当执行逆置时需考虑到left-mid中的元素与right-mid之间的元素交换
	for (j = 0; j <= mid - left; j++) {
		temp = L.data[left - 1 + j];
		L.data[left - 1 + j] = L.data[right - 1 - j];
		L.data[right - 1 - j] = temp;
	}
	return true;
}
//删除值为x的元素
bool DeleteValue_1(LList& L, int x) {
	
	/*
		当第一次j = x值时，j++，k不变，此时k会停留在值为x的下标处
		执行下一循环时，若j != x值，则j处数值会前移到k处
		这样，每次遇到j = x值时，k与j就会拉开一格距离，
		当执行到j != x值时，j处的值就会前移至k处
	*/
	int j, k = 0;
	for (j = 0; j < L.length; j++) {
		if (L.data[j] != x) {
			L.data[k] = L.data[j];
			k++;
		}
	}
	L.length = k;

	return true;
}

bool DeleteValue_2(LList& L, int x) {
	int j = 0, count = 0;
	while (j<L.length)
	{
		if (L.data[j] == x)
		{
			count++;
		}
		else
		{
			L.data[j - count] = L.data[j];
		}
		j++;
	}
	L.length -= count;

	return true;
}

//有序表合并
bool Merge(LList L1, LList L2, LList &L3) {
	int i = 0, j = 0, k = 0;
	//加入数据长度超出L3判断条件
	//两两比较，小者存入L3
	while (i < L1.length && j < L2.length) 
	{
		if (L1.data[i] <= L2.data[j]) 
		{
			L3.data[k++] = L1.data[i++];
		}
		else
		{
			L3.data[k++] = L2.data[j++];
		}
	}
	//将剩余一表中的元素顺序插入尾部
	while(i < L1.length)
		L3.data[k++] = L1.data[i++];
	while(j < L2.length)
		L3.data[k++] = L2.data[j++];

	L3.length = k;

	return true;
}
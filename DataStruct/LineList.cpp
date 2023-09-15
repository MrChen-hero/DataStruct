#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10
#define EXTAND 10

typedef struct LineList {
	int* data;
	int length;
}LList;

void InitLineList(LList& L);	//��ʼ��
void PrintList(LList& L);	//��ӡ
void AddLineList(LList& L);	//����
void DestoryList(LList& L);	//����
bool InsertList(LList& L, int i, int e);	//��λ�����
bool DeleteList(LList& L, int i, int& e);	//��λ��ɾ��
//�㷨
bool Reverse(LList& L, int i, int e);	//��תԪ��
bool DeleteValue_1(LList& L, int x);	//ɾ��ֵΪx��Ԫ��
bool DeleteValue_2(LList& L, int x);	
bool Merge(LList L1, LList L2, LList& L3);	//�ϲ���



//��ʼ��
void InitLineList(LList &L){
	L.data = (int *)malloc(sizeof(int) * MAXSIZE);
	if (L.data == NULL) {
		printf("����ռ�ʧ��");
	}
	L.length = 0;
}

//����
void AddLineList(LList& L) {
	int* temp = L.data;
	int i;
	L.data = (int*)malloc(sizeof(int) * (MAXSIZE + EXTAND));
	if (L.data == NULL) {
		printf("�����ڴ�ʧ��");
		exit(0);
	}
	//��ԭ�������ݸ��Ƶ��±���
	for (i = 0; i < L.length; i++) {
		L.data[i] = temp[i];
	}
	free(temp);
	return ;
}

//����
void DestoryList(LList& L) {
	int* temp = L.data;
	L.data = NULL;
	free(temp);
	L.length = 0;
	return;
}

//��ӡ
void PrintList(LList& L) {
	int i;
	for (i = 0; i < L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	return ;
}

//����
bool InsertList(LList& L, int i,int e) {
	int j;
	if (i > L.length + 1 || i < 1) {
		return false;
	}
	//�������Ҫ���� j >= i���ҵ���i-1���ڵ㣬����i����֮��Ľڵ����
	for (j = L.length; j >= i; j--) {
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}

//ɾ��
bool DeleteList(LList& L, int i,int &e) {
	int j;
	if (i > L.length || i < 0) {
		return false;
	}
	e = L.data[i - 1];
	//ɾ������Ҫ����  j < L.length������i���ڵ㼰֮��Ľڵ�ǰ��
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
	//����
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
	//ɾ��
	/*
	DeleteList(list, 2, e);
	PrintList(list);
	printf("\n%d", e);
	*/
	//����
	/*
	Reverse(list, 4, 5);
	Reverse(list, 1, 3);
	Reverse(list, 1, 5);
	printf("\n");
	PrintList(list);
	*/
	//ɾ��ֵΪx��Ԫ��
	/*
	DeleteValue_1(list, 2);
	DeleteValue_2(list, 2);
	printf("\n");
	PrintList(list);
	*/
	//�����ϲ�
	Merge(list1, list2, list3);
	printf("\n");
	PrintList(list3);


	DestoryList(list1);
	DestoryList(list2);
	return 0;
}

//���ñ��е�Ԫ��
bool Reverse(LList& L, int left, int right) {
	int j, mid, temp;
	//���ַ�����
	mid = (left + right) / 2;
	//�˴�Ӧע�⣬j <= mid - left�����𵽵�left��Ϊ1ʱ��ѭ����������
	//���������⣬��ִ������ʱ�迼�ǵ�left-mid�е�Ԫ����right-mid֮���Ԫ�ؽ���
	for (j = 0; j <= mid - left; j++) {
		temp = L.data[left - 1 + j];
		L.data[left - 1 + j] = L.data[right - 1 - j];
		L.data[right - 1 - j] = temp;
	}
	return true;
}
//ɾ��ֵΪx��Ԫ��
bool DeleteValue_1(LList& L, int x) {
	
	/*
		����һ��j = xֵʱ��j++��k���䣬��ʱk��ͣ����ֵΪx���±괦
		ִ����һѭ��ʱ����j != xֵ����j����ֵ��ǰ�Ƶ�k��
		������ÿ������j = xֵʱ��k��j�ͻ�����һ����룬
		��ִ�е�j != xֵʱ��j����ֵ�ͻ�ǰ����k��
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

//�����ϲ�
bool Merge(LList L1, LList L2, LList &L3) {
	int i = 0, j = 0, k = 0;
	//�������ݳ��ȳ���L3�ж�����
	//�����Ƚϣ�С�ߴ���L3
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
	//��ʣ��һ���е�Ԫ��˳�����β��
	while(i < L1.length)
		L3.data[k++] = L1.data[i++];
	while(j < L2.length)
		L3.data[k++] = L2.data[j++];

	L3.length = k;

	return true;
}
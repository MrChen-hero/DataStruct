#include<stdio.h>
#include<stdlib.h>


bool BFmatch(char S[], char T[]);
bool KMPmatch(char S[], char T[]);
void get_Next(char T[], int* next);

/*
* ����ģʽƥ���㷨
* ģʽ�������������Ƚ�
* �����ʱ����ָ����ݺ���һλ����ƥ��
*/
bool BFmatch(char S[], char T[]) {
	int i = 1;//����ָ��
	int	j = 1;//�ִ�ָ��
	while (i <= S[0]-48 && j <= T[0]-48) {
		if (S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 2;//����һ��
			j = 1;
		}
	}
	if (j > T[0] - 48) {
		printf("�ִ�λ�ڵ�%dλ\n", i - (T[0] - 48));
		return true;
	}
	else
		return false;
}
/*
* KMPƥ���㷨
* ƥ��ʧ��i���䣬j�ص�next[j];
*/
bool KMPmatch(char S[], char T[]) {
	int i = 1;
	int j = 1;
	int next[255];
	get_Next(T, next);//��ȡnext����
	while (i <= S[0] - 48 && j <= T[0] - 48) {
		if (j == 0 || S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j > T[0] - 48) {
		printf("�ִ�λ�ڵ�%dλ\n", i - (T[0] - 48));
		return true;
	}
	else
		return false;
}

/*
* �ڲ�ƥ��λ��ǰ���ֽ��ޣ�ģʽ��һ�������ˣ�ֱ���ֽ���֮ǰ��ƥ�䣬��ģʽ������ֽ��ߣ���ʱjֵΪnextֵ
* aaaab
* 01234
* �Ż�����T[j] = T[next[j]],��next[j] = next[next[j]]
*/
void get_Next(char T[],int next[]) {
	int j = 0; // j��ʾǰ׺
	int i = 1; // i��ʾ��׺
	next[1] = 0; // next����ĳ�ʼֵΪ0

	while (i < T[0]-48) // ѭ������
	{
		if (0 == j || T[i] == T[j]) // ���ǰ׺�ͺ�׺���
		{
			i++; // ��׺����ƶ�һλ
			j++; // ǰ׺����ƶ�һλ
			if (T[i] != T[j]) // �����׺��ǰ׺�����
			{
				next[i] = j; // next[i]��ֵΪj
			}
			else // �����׺��ǰ׺���
			{
				next[i] = next[j]; // next[i]��ֵΪnext[j]
			}
		}
		else // ���ǰ׺�ͺ�׺�����
		{
			j = next[j]; // ��j����Ϊnext[j]
		}
	}
}
int main()
{
	char S[20] = "9abaabaabc";//����
	char T[10] = "6abaabc";	//ģʽ��
/*abaabc
* 010213
*/
	BFmatch(S, T);
	KMPmatch(S, T);
	return 0;
}
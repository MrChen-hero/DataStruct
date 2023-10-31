#include<stdio.h>
#include<stdlib.h>


bool BFmatch(char S[], char T[]);
bool KMPmatch(char S[], char T[]);
void get_Next(char T[], int* next);

/*
* 朴素模式匹配算法
* 模式串依次与主串比较
* 不相等时主串指针回溯后移一位继续匹配
*/
bool BFmatch(char S[], char T[]) {
	int i = 1;//主串指针
	int	j = 1;//字串指针
	while (i <= S[0]-48 && j <= T[0]-48) {
		if (S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 2;//后移一格
			j = 1;
		}
	}
	if (j > T[0] - 48) {
		printf("字串位于第%d位\n", i - (T[0] - 48));
		return true;
	}
	else
		return false;
}
/*
* KMP匹配算法
* 匹配失败i不变，j回到next[j];
*/
bool KMPmatch(char S[], char T[]) {
	int i = 1;
	int j = 1;
	int next[255];
	get_Next(T, next);//获取next数组
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
		printf("字串位于第%d位\n", i - (T[0] - 48));
		return true;
	}
	else
		return false;
}

/*
* 在不匹配位置前划分界限，模式串一步步后退，直到分界线之前能匹配，或模式串跨过分界线，此时j值为next值
* aaaab
* 01234
* 优化：若T[j] = T[next[j]],则next[j] = next[next[j]]
*/
void get_Next(char T[],int next[]) {
	int j = 0; // j表示前缀
	int i = 1; // i表示后缀
	next[1] = 0; // next数组的初始值为0

	while (i < T[0]-48) // 循环条件
	{
		if (0 == j || T[i] == T[j]) // 如果前缀和后缀相等
		{
			i++; // 后缀向后移动一位
			j++; // 前缀向后移动一位
			if (T[i] != T[j]) // 如果后缀和前缀不相等
			{
				next[i] = j; // next[i]的值为j
			}
			else // 如果后缀和前缀相等
			{
				next[i] = next[j]; // next[i]的值为next[j]
			}
		}
		else // 如果前缀和后缀不相等
		{
			j = next[j]; // 将j更新为next[j]
		}
	}
}
int main()
{
	char S[20] = "9abaabaabc";//主串
	char T[10] = "6abaabc";	//模式串
/*abaabc
* 010213
*/
	BFmatch(S, T);
	KMPmatch(S, T);
	return 0;
}
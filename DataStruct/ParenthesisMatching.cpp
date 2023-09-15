/*����ƥ��*/
#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool ParenthesisMatching(string &str);

bool ParenthesisMatching(string &str) {
	stack<char> S;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
			//ɨ�赽�����ţ�������ջ
			S.push(str[i]);
		}
		else {
			//ɨ�赽������
			if (S.empty())//��ջ������������δƥ����ʱ��Ϊƥ��ʧ��
				return false;

			char e = S.top();//����ջ��Ԫ��
			S.pop();
			//�����Ų�ƥ����ʧ��
			if (str[i] == ')' && e != '(')
				return false;
			if (str[i] == ']' && e != '[')
				return false;
			if (str[i] == '}' && e != '{')
				return false;
		}
		cout << "��" << i << "��" << endl;
	}
	cout << "�ɹ���" << endl;
	return true;
}

int main()
{
	string s = "{(())([])}";
	ParenthesisMatching(s);
	return 0;
}
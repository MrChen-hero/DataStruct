/*¿®∫≈∆•≈‰*/
#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool ParenthesisMatching(string &str);

bool ParenthesisMatching(string &str) {
	stack<char> S;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
			//…®√ËµΩ◊Û¿®∫≈£¨Ω´∆‰»Î’ª
			S.push(str[i]);
		}
		else {
			//…®√ËµΩ”“¿®∫≈
			if (S.empty())//»Ù’ªø’«“«“”“¿®∫≈Œ¥∆•≈‰ÕÍ ±‘ÚŒ™∆•≈‰ ß∞‹
				return false;

			char e = S.top();//¥¢¥Ê’ª∂•‘™Àÿ
			S.pop();
			//»Ù¿®∫≈≤ª∆•≈‰‘Ú ß∞‹
			if (str[i] == ')' && e != '(')
				return false;
			if (str[i] == ']' && e != '[')
				return false;
			if (str[i] == '}' && e != '{')
				return false;
		}
		cout << "µ⁄" << i << "≤Ω" << endl;
	}
	cout << "≥…π¶£°" << endl;
	return true;
}

int main()
{
	string s = "{(())([])}";
	ParenthesisMatching(s);
	return 0;
}
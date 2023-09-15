/*��׺���ʽת��Ϊǰ׺���ʽ���׺���ʽ*/
/*	
��׺���ʽתΪ��׺���ʽ
	1��������ԭ��
	2��ȷ�����������˳��
	3����[������� �Ҳ����� �����]����²�����
	4���ظ�3	
	����ʱ����������ɨ���������ջ���ȳ�ջ��Ϊ�Ҳ�����	
��׺���ʽתΪǰ׺���ʽ
	1��������ԭ��
	2��ȷ�������˳��
	3����[����� ������� �Ҳ�����]����²�����
	4���ظ�3
	����ʱ����������ɨ���������ջ���ȳ�ջ��Ϊ�������
*/
#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool Postfix(string s);

// �ж��Ƿ��ǲ�����
bool isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	return false; // ���򷵻�false
}
int getOpertor(char ch, int a, int b) {
    int result = 0;

    switch (ch) {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        result = a / b;
        break;
    default:
        cout << "Invalid operator:" << ch <<" ";
        break;
    }
    return result;
}
// ��ȡ���ȼ�
int getPriority(char ch) {
    int level = 0; // ���ȼ�

    switch (ch) {
    case '(':
        level = 1;
        break;
    case '+':
    case '-':
        level = 2;
        break;
    case '*':
    case '/':
        level = 3;
        break;
    default:
        break;
    }
    return level;
}

/*
1��������������ֱ�ӳ�ջ
2���������޷�'('ֱ����ջ������')'��һ�ε���ջ��������������׺���ʽ��ֱ������')'Ϊֹ
3����������������ε���ջ�����ȼ����ڻ���ڵ�ǰ�����������������������׺���ʽ��֮���ٰѵ�ǰ�������ջ��������'('��ջ����ֹͣ
4�������������ַ���ջ��ʣ����������ε����������׺���ʽ
*/
bool Postfix(string str) {
    stack<int> DataStack;//��Ų�����
    stack<char> OperatorStack;//��������
    int leftdata, rightdata; //������Ҳ�����
    
    for (int i = 0 ; i < str.size() ; ) {
        //��ȡ��׺���ʽ
        //��������֣��������ȡ��ֱ������������Ϊֹ
        if (isdigit(str[i])) {
            int num = 0;
            do {
                num = num * 10 + (str[i] - '0');//��ÿһλ�ַ�ת��Ϊ����
                i++;
            } while (isdigit(str[i]));
            DataStack.push(num);    //ѹ������ջ
            cout << num << " "; //���
        }

        //��Ϊ'���޷�'('����ֱ����ջ
        else if (str[i] == '(') {
            OperatorStack.push(str[i]); //ѹ�������ջ
            i++;
        }

        //��Ϊ�����
        else if (isOperator(str[i])) {
            if (OperatorStack.empty()) {
                //��ջ����ֱ����ջ
                OperatorStack.push(str[i]);
                i++;
            }
            else {
                //��ջ�ǿգ���Ƚ����ȼ������ȼ�������ջ�������Ƴ�ջ�������ֱ��С��ch���ȼ�
                while (!OperatorStack.empty()) {
                    char op = OperatorStack.top();
                    if (getPriority(str[i]) <= getPriority(op)) {
                        //����ǰ��������ȼ�<=ջ�����������ջ���������ջ
                        cout << OperatorStack.top() << " ";
                        OperatorStack.pop();

                        /*ÿ��ջһ�����������Ҫ����������������*/
                        rightdata = DataStack.top(); //�ȳ�ջ��Ϊ�Ҳ�����
                        DataStack.pop();
                        leftdata = DataStack.top();
                        DataStack.pop();
                        //����������²�������ջ
                        DataStack.push(getOpertor(op, leftdata, rightdata));
                    }
                    else
                        break;
                }//ֱ��ջ�ջ�ǰ��������ȼ�����ջ�������
                OperatorStack.push(str[i]);
                i++;
            }
        }
        
        //������')'���������ջ�Ƴ���ֱ����������޷�
        else if (str[i] == ')') {
            while (OperatorStack.top() != '(') {
                cout << OperatorStack.top() << " ";
                char op = OperatorStack.top();
                OperatorStack.pop();

                /*ÿ��ջһ�����������Ҫ����������������*/
                rightdata = DataStack.top(); //�ȳ�ջ��Ϊ�Ҳ�����
                DataStack.pop();
                leftdata = DataStack.top();
                DataStack.pop();
                //����������²�������ջ
                DataStack.push(getOpertor(op,leftdata,rightdata));
            }
            OperatorStack.pop();//��'('��ջ
            i++;
        }
    }
    while (!OperatorStack.empty()) {
        //��ջ��ʣ���������ջ
        char op = OperatorStack.top();
        cout << OperatorStack.top() << " ";
        OperatorStack.pop();

        /*ÿ��ջһ�����������Ҫ����������������*/
        rightdata = DataStack.top(); //�ȳ�ջ��Ϊ�Ҳ�����
        DataStack.pop();
        leftdata = DataStack.top();
        DataStack.pop();
        //����������²�������ջ
        DataStack.push(getOpertor(op, leftdata, rightdata));
    }
    cout << "\n" << "���Ϊ" << DataStack.top() << endl;
    flush(cout);
    return true;
}

int main() 
{
	string str = "((15/(7-(1+1)))*3)-(2+(1+1))";
    Postfix(str);
	return 0;
}
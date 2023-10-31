/*中缀表达式转换为前缀表达式与后缀表达式*/
/*	
中缀表达式转为后缀表达式
	1、左优先原则
	2、确定运算符运算顺序
	3、按[左操作数 右操作数 运算符]组成新操作数
	4、重复3	
	运算时，从左往右扫描操作数入栈，先出栈的为右操作数	
中缀表达式转为前缀表达式
	1、右优先原则
	2、确定运算符顺序
	3、按[运算符 左操作数 右操作数]组成新操作数
	4、重复3
	运算时，从右往左扫描操作数入栈，先出栈的为左操作数
*/
#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool Postfix(string s);

// 判断是否是操作符
bool isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	return false; // 否则返回false
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
// 获取优先级
int getPriority(char ch) {
    int level = 0; // 优先级

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
1、遇到操作数，直接出栈
2、遇到界限符'('直接入栈，遇到')'测一次弹出栈内运算符并加入后缀表达式，直到弹出')'为止
3、遇到运算符。依次弹出栈内优先级高于或等于当前运算符的所有运算符，加入后缀表达式，之后再把当前运算符入栈，若碰到'('或栈空则停止
4、处理完所有字符后将栈内剩余运算符依次弹出，加入后缀表达式
*/
bool Postfix(string str) {
    stack<int> DataStack;//存放操作数
    stack<char> OperatorStack;//存放运算符
    int leftdata, rightdata; //存放左右操作数
    
    for (int i = 0 ; i < str.size() ; ) {
        //读取中缀表达式
        //如果是数字，则继续读取，直到读到操作数为止
        if (isdigit(str[i])) {
            int num = 0;
            do {
                num = num * 10 + (str[i] - '0');//将每一位字符转换为数字
                i++;
            } while (isdigit(str[i]));
            DataStack.push(num);    //压入数据栈
            cout << num << " "; //输出
        }

        //若为'界限符'('，则直接入栈
        else if (str[i] == '(') {
            OperatorStack.push(str[i]); //压入运算符栈
            i++;
        }

        //若为运算符
        else if (isOperator(str[i])) {
            if (OperatorStack.empty()) {
                //若栈空则直接入栈
                OperatorStack.push(str[i]);
                i++;
            }
            else {
                //若栈非空，则比较优先级，优先级高则入栈，否则推出栈内运算符直到小于ch优先级
                while (!OperatorStack.empty()) {
                    char op = OperatorStack.top();
                    if (getPriority(str[i]) <= getPriority(op)) {
                        //若当前运算符优先级<=栈顶运算符，则将栈顶运算符出栈
                        cout << OperatorStack.top() << " ";
                        OperatorStack.pop();

                        /*每出栈一个运算符，需要两个操作数来运算*/
                        rightdata = DataStack.top(); //先出栈的为右操作数
                        DataStack.pop();
                        leftdata = DataStack.top();
                        DataStack.pop();
                        //将计算出的新操作数入栈
                        DataStack.push(getOpertor(op, leftdata, rightdata));
                    }
                    else
                        break;
                }//直到栈空或当前运算符优先级大于栈顶运算符
                OperatorStack.push(str[i]);
                i++;
            }
        }
        
        //若遇到')'，将运算符栈推出，直至遇见左界限符
        else if (str[i] == ')') {
            while (OperatorStack.top() != '(') {
                cout << OperatorStack.top() << " ";
                char op = OperatorStack.top();
                OperatorStack.pop();

                /*每出栈一个运算符，需要两个操作数来运算*/
                rightdata = DataStack.top(); //先出栈的为右操作数
                DataStack.pop();
                leftdata = DataStack.top();
                DataStack.pop();
                //将计算出的新操作数入栈
                DataStack.push(getOpertor(op,leftdata,rightdata));
            }
            OperatorStack.pop();//将'('出栈
            i++;
        }
    }
    while (!OperatorStack.empty()) {
        //将栈内剩余运算符出栈
        char op = OperatorStack.top();
        cout << OperatorStack.top() << " ";
        OperatorStack.pop();

        /*每出栈一个运算符，需要两个操作数来运算*/
        rightdata = DataStack.top(); //先出栈的为右操作数
        DataStack.pop();
        leftdata = DataStack.top();
        DataStack.pop();
        //将计算出的新操作数入栈
        DataStack.push(getOpertor(op, leftdata, rightdata));
    }
    cout << "\n" << "结果为" << DataStack.top() << endl;
    flush(cout);
    return true;
}

int main() 
{
	string str = "((15/(7-(1+1)))*3)-(2+(1+1))";
    Postfix(str);
	return 0;
}
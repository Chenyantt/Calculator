#include "calculator.h"

#include <string>
#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

string Calculator(string equation) {
	vector <string> vec(50, "");
	if (equation == "") return "表达式不能为空！！！";
	if (isLegal(equation)) {
		if (BracketMatch(equation)) {
			if (isBlankLegal(equation)) {
				Operand(equation, vec);
				int output = isOperatorNext(vec);
				if (output == 1) {
					output = isNumberLegal(vec);
					if (output == 1) {
						if (isAddLegal(vec)) {
							NegativeDeal(vec);
							vec = ReverseNotation(vec);
							vector <string> error = Eval(vec);
							if (error[0] == "除数不能为零！") return error[0];
							if (error[0] == "操作符误用！") return error[0];
							if (error[0] == "表达式出错!") return error[0];
							if (vec[0] == "-") return "操作符误用";
							return vec_to_str(vec);
						}
						else return "不允许单目的 '+'或者'*'或者'/' 运算符";
					}
					else if (output == 0) return "数字格式有误";
					else return "小数精度错误";
				}
				else if (output == 0) return "操作符误用";
				else return "算式中不允许出现空的括号";
			}
			else return "数字内部不允许有空格";
		}
		else return "圆括号不匹配";
	}
	else return "含有不合法字符";
}

int isLegal(string equation) {
	int length = equation.length();
	for (int i = 0; i < length; ++i) {
		char ch = equation[i];
		if ((ch >= 45 && ch <= 57) ||
			(ch >= 40 && ch <= 43) ||
			ch == 32)  continue;
		else return 0;
	}
	return 1;
}

int BracketMatch(string equation) {
	stack<char> st;
	int length = equation.length();
	for (int i = 0; i < length; ++i) {
		char ch = equation[i];
		if (ch == '(')  st.push(ch);
		else if (ch == ')') {
			if (st.empty() || st.top() != '(') return 0;
			else st.pop();
		}
	}
	if (st.empty()) return 1;
	else return 0;
}

int isBlankLegal(string& equation) {
	while (equation[0] == ' ') equation = equation.substr(1);
	int i = 1;
	while (i < (int)equation.length() - 1) {
		if (equation[i] == ' ') {
			if (((equation[i - 1] >= '0' && equation[i - 1] <= '9') || equation[i - 1] == '.') &&
				((equation[i + 1] >= '0' && equation[i + 1] <= '9') || equation[i + 1] == '.')) {
				return 0;
			}
			else {
				equation = equation.substr(0, i) + equation.substr(i + 1);
			}
		}
		else ++i;
	}
	if (equation[i] == ' ') equation = equation.substr(0, equation.length() - 1);
	return 1;
}

void Operand(string equation, vector<string>& vec) {
	int index = 0;
	for (int i = 0; i < (int)equation.length(); ++i) {
		if ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == '.') {
			vec[index] += equation[i];
		}
		else {
			if (vec[index] == "") {
				vec[index] = equation[i];
			}
			else {
				index++;
				vec[index] = equation[i];
			}
			index++;
		}
	}
}

int isOperatorNext(vector<string> vec) {
	for (int i = 1; vec[i] != ""; ++i) {
		char first = vec[i - 1][0], second = vec[i][0];
		if ((first == '+' || first == '-' || first == '*' || first == '/') &&
			(second == '+' || second == '-' || second == '*' || second == '/')) {
			return 0;
		}
		else if (first == '(' && second == ')') return -1;
	}
	return 1;
}

int isAddLegal(vector<string> vec) {
	if (vec[0] == "+" || vec[0] == "*" || vec[0] == "/") return 0;
	for (int i = 1; vec[i] != ""; ++i) {
		if (vec[i] == "+" || vec[i] == "*" || vec[i] == "/") {
			if (((vec[i - 1][0] < '0' || vec[i - 1][0] > '9') && vec[i - 1][0] != ')')
				|| ((vec[i + 1][0] < '0' || vec[i + 1][0] > '9') && vec[i + 1][0] != '('))
				return 0;
		}
	}
	return 1;
}

int isNumberLegal(vector<string> vec) {
	for (int i = 0; vec[i] != ""; ++i) {
		if (vec[i][0] == '.' || vec[i][vec[i].length() - 1] == '.' ||
			count(vec[i].begin(), vec[i].end(), '.') > 1) {
			return 0;
		}
		else if (vec[i].find('.') != -1 &&
			vec[i].length() > vec[i].find('.') + 2) {
			return -1;
		}
	}
	return 1;
}

void NegativeDeal(vector<string>& vec) {
	if (vec[0][0] == '-') {
		if (vec[1][0] >= '0' && vec[1][0] <= '9') {
			vec.insert(vec.begin(), "0");
			vec.insert(vec.begin(), "(");
			vec.insert(vec.begin() + 4, ")");
		}
		else if (vec[1][0] == '(') {
			stack <string> st;
			int i;
			for (i = 1; vec[i] != ""; ++i) {
				if (vec[i] == "(") st.push("(");
				else if (vec[i] == ")") {
					st.pop();
					if (st.empty()) break;
				}
			}
			vec.insert(vec.begin() + i + 1, ")");
			vec.insert(vec.begin(), "0");
			vec.insert(vec.begin(), "(");
		}
	}
	for (int i = 1; vec[i] != ""; ++i) {
		if (vec[i - 1] == "(" && vec[i] == "-") {
			if (vec[i + 1][0] >= '0' && vec[i + 1][0] <= '9') {
				vec.insert(vec.begin() + i, "0");
				vec.insert(vec.begin() + i, "(");
				vec.insert(vec.begin() + 4 + i, ")");
			}
			else if (vec[i + 1][0] == '(') {
				stack <string> st;
				int j;
				for (j = i + 1; vec[j] != ""; ++j) {
					if (vec[j] == "(") st.push("(");
					else if (vec[j] == ")") {
						st.pop();
						if (st.empty()) break;
					}
				}
				vec.insert(vec.begin() + 1 + j, ")");
				vec.insert(vec.begin() + i, "0");
				vec.insert(vec.begin() + i, "(");
			}
		}
	}
	return;
}

vector<string> ReverseNotation(vector<string> vec) {
	stack<string> st;
	vector<string> output;
	map<string, int> operators;
	operators.insert(pair<string, int>("*", 2));
	operators.insert(pair<string, int>("/", 2));
	operators.insert(pair<string, int>("+", 1));
	operators.insert(pair<string, int>("-", 1));
	for (int i = 0; vec[i] != ""; ++i) {
		string str = vec[i];
		if (str == " ") continue;
		else if (str[0] >= '0' && str[0] <= '9') output.push_back(str);
		else if (str == ")") {
			while (st.top() != "(")
			{
				output.push_back(st.top());
				st.pop();
			}
			st.pop();
		}
		else if (str == "(")
		{
			st.push(str);
		}
		else {
		back:
			if (st.empty() || st.top() == "(" ||
				operators.find(str)->second > operators.find(st.top())->second) {
				st.push(str);
			}
			else
			{
				output.push_back(st.top());
				st.pop();
				goto back;
			}
		}
	}
	while (!st.empty())
	{
		output.push_back(st.top());
		st.pop();
	}
	return output;
}

vector<string> Eval(vector<string>& vec) {
	vector<string> error1 = { "除数不能为零！" };
	vector<string> error2 = { "操作符误用！" };
	vector<string> error3 = { "表达式出错!" };
	if (vec.size() == 1) return vec;
	if (((vec[0][0] >= '0' && vec[0][0] <= '9') || vec[0][0] == '-') && ((vec[1][0] < '0' || vec[1][0]>'9') && (vec[1][0] != '-' || vec[1].length() == 1)))
		return error2;
	int i;
	for (i = 0; i < (int)vec.size(); ++i) {
		if (vec[i] == "+" || vec[i] == "-" || vec[i] == "*" || vec[i] == "/") break;
	}
	if (i == vec.size()) return error3;
	char ch = vec[i][0];
	string str;
	switch (ch)
	{
	case '+':
		str = to_string(stod(vec[i - 1]) + stod(vec[i - 2]));
		break;
	case '-':
		str = to_string(stod(vec[i - 2]) - stod(vec[i - 1]));
		break;
	case '*':
		str = to_string(stod(vec[i - 1]) * stod(vec[i - 2]));
		break;
	case '/':
		if (stod(vec[i - 1]) == 0) {
			return error1;
		}
		str = to_string(stod(vec[i - 2]) / stod(vec[i - 1]));
		break;
	default:
		break;
	}
	vec.insert(vec.begin() + i + 1, str);
	vec.erase(vec.begin() + i);
	vec.erase(vec.begin() + i - 1);
	vec.erase(vec.begin() + i - 2);
	return Eval(vec);
}

string vec_to_str(vector<string> vec) {
	stringstream ss;
	double d = round(stod(vec[0]) * 10);
	ss << setprecision(1) << fixed << d / 10;
	string str = ss.str();
	if (str[str.find('.') + 1] == '0') return str.substr(0, str.length() - 2);
	return str;
}
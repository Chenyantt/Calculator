#include <iostream>
#include <string>

#include "calculator.h"

using namespace std;

int main() {
	string s;
	cout << "请输入表达式：" << endl;
	getline(cin,s);
	cout << Calculator(s)<< endl;
	return 0;
}
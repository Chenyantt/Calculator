#include <iostream>
#include <string>

#include "calculator.h"

using namespace std;

int main() {
	string s;
	cout << "��������ʽ��" << endl;
	getline(cin,s);
	cout << Calculator(s)<< endl;
	return 0;
}
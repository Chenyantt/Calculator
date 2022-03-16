#ifndef _CALCULATOR_
#define _CALCULATOR_

#include <string>
#include <stack>
#include <vector>

using namespace std;

string Calculator(string equation);
int isLegal(string equation);
int BracketMatch(string equation);
int isBlankLegal(string &equation);
void Operand(string equation,vector<string> &vec);
int isOperatorNext(vector<string> vec);
int isAddLegal(vector<string> vec);
int isNumberLegal(vector<string> vec);
void NegativeDeal(vector<string> &vec);
vector<string> ReverseNotation(vector<string> vec);
vector<string> Eval(vector<string> &vec);
string vec_to_str(vector<string> vec);

#endif 


#include "parser.h"
#include <vector>

int isVar(char c)
{
	return ((c >= 'a') && (c <= 'z') /*&& (c != 'v')*/);
}
char Str2Pol::NextChar()
{
	if (i <= (int)instr.length())
		return c = instr[i++];
	return c = '\0';
}

void Str2Pol::ParseExpression()
{
	ParseSymbol();
	while (/*c == 'v' ||*/ c == '&' || c == '>') {
		char temp = c;
		NextChar();
		ParseSymbol();
		outstr.push_back(temp);
	}
}

void Str2Pol::ParseSymbol()
{
	while (c == '!')
	{
		char temp = c;
		NextChar();
		ParseSymbol();
		outstr.push_back(temp);
	}
	if (c == '(')
	{
		NextChar();
		ParseExpression();
		NextChar(); //may set a check for ')'
	}
	else
		if (isVar(c)) 
		{
			outstr.push_back(c);
			NextChar();
			/*outstr.push_back(c);
			NextChar();*/
		}
}

void Str2Pol::Start(string &str) {
	SetString(str);
	NextChar();
	ParseExpression();
}

int GetVarNum(string str)
{
	int counter_var = 0, i = 0;
	string var;
	vector <int> flags(26);
	while (str[i] != '\0')
	{
		if (isVar(str[i]) && (flags[str[i] - 'a'] == 0))
		{
			counter_var++;
			flags[str[i] - 'a'] = 1;
		}
		i++;
	}
	return counter_var;
}

string Parser(FILE *fin)
{
	string in;
	char c;
	while (fscanf(fin, "%c", &c) != -1)
	{
		if (c == '=')
			continue;
		if (c == '\n')
			break;
		if (c != EOF)
			in.push_back(c);
	}
	Str2Pol expression;
	expression.Start(in);
	return expression.GetOutstr();
}

bool Eval(string str, vector <bool> bin) {
	stack <bool> st_var;
	int i = 0, j = 0;
	int size = bin.size();
	bool res;
	for (i = 1; i < size; i++)
	{
		while (str[j] != '\0')
		{
			if (str[j] == 'a' + i - 1)
			{
				if (bin[i] == false)
					str[j] = '0';
				else
					str[j] = '1';
			}
			j++;
		}
		j = 0;
	}
	j = 0; i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '!')
		{
			bool x = st_var.top(); st_var.pop();
			st_var.push(!x);
			i++;
			continue;
		}
		if (/*str[i] == 'v' ||*/ str[i] == '&' || str[i] == '>')
		{
			bool x1 = st_var.top(); st_var.pop();
			bool x2 = st_var.top(); st_var.pop();
			if (str[i] == '&')
				st_var.push(x1 & x2);
			/*else if (str[i] == 'v')
				st_var.push(x1 | x2);*/
			else
				st_var.push((!x2) | x1);
		}
		else
		{
			if (str[i] == '0')
				st_var.push(0);
			else
				st_var.push(1);
		}
		++i;
	}
	res = st_var.top();
	return res;
}

vector <bool> Num2Bin(int number, const int count)
{
	vector <bool> bin(count + 1);
	for (int i = 0; i < count; i++)
	{
		if (number % 2 == 1)
			bin[count - i] = 1;
		else
			bin[count - i] = 0;
		number = number / 2;
	}
	return bin;
}



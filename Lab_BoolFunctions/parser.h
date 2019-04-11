#pragma once
#include <iostream>
#include <stack>
#include <vector>
#pragma warning (disable: 4996)
using namespace std;

class Str2Pol {
	string instr, outstr;     //input & output strings
	char c;                    //the current character
	int i;                      //the index of the input string

	char NextChar();              //get the next character
	void ParseExpression();                 //handle plus & minus       
	void ParseSymbol();                //handle characters & brackets

public:
	Str2Pol() {
		i = 0;
		//outstr = new string;
	}
	void SetString(string &s) {
		instr = s;
	}
	string GetOutstr() {
		return outstr;
	}
	void Start(string &str);
};

int GetVarNum(string str);

string Parser(FILE *fin);

bool Eval(string str, vector <bool> bin);

vector <bool> Num2Bin(int number, const int count);
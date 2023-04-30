#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<fstream>
#include<conio.h>
#include<Windows.h>
#include "globalFile.h"
using namespace std;

// class
class PassWord
{
public:
	PassWord(int n);
	string inputPwd(int id);
	// void changePassWord(string type);
protected:
	int msize;
	string str;
	string getPwd(int n, string s);
	string convert(string s, int numRows);
};
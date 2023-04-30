#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<Windows.h>
#include "globalFile.h"
#include "Identity.h"
#include "Student.h"
#include "Teacher.h"
#include "computerRoom.h"
#include "passWord.h"


class Guess
{
public:
	Guess();
	Guess(string name, string pwd);
	void applyNewCount();
	void checkStatus();
	virtual void subMenu();
	int g_select;
	int g_status;
	int g_id;
	string g_name;
	string g_pwd;
	vector<Student> vStu;
	vector<Teacher> vTea;
	bool checkRepeatID(int id, int type);	// check repeat ID
	void initVector();
protected:
	virtual void addPerson();
	int maxPwdSize;
};
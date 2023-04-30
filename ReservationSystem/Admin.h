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
#include "computerRoom.h"
#include "passWord.h"
#include "Guess.h"
#include "Student.h"
#include "Teacher.h"

using namespace std;


// Administrator Class
class Admin :public Identity
{
public:
	Admin();
	Admin(string name, string pwd, int n);
	virtual void subMenu();
	void showPerson();	// show all users' info.
	virtual void addPerson();	// add new account
	void showCpRmInfo();	// show computer rooms' info.
	void clearFile();	// clear booking records
	void initVector();	// init a vector
	vector<Student> vStu;
	vector<Teacher> vTea;
	vector<ComputerRoom> vCom;
	bool checkRepeatID(int id, int type);	// check repeat ID
	void validNewPerson();
	vector<Guess> vGue;
	void deleteCount();
	void changeAdmPwd();	// change admin password
protected:
	int maxPwdSize;
};


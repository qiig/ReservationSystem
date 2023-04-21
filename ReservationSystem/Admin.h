#pragma once
#include<iostream>
#include<string>
#include "Identity.h"
using namespace std;

// Administrator Class
class Admin :public Identity
{
public:
	Admin();
	Admin(string name, string pwd);
	void subMenu();
	void showPerson();	// show all users' info.
	void addPerson();	// add new account
	void showCpRmInfo();	// show computer rooms' info.
	void clearFile();	// clear booking records
};


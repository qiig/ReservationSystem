#pragma once
#include<iostream>
#include<string>
#include "Identity.h"
using namespace std;

// Teacher Class
class Teacher :public Identity
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);
	void subMenu();
	void showAllOrder();	// show all applications
	void validOrder();		// check applications
protected:
	int t_ID;
};
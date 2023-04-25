#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Identity.h"
#include "orderFile.h"
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
	int t_ID;
};
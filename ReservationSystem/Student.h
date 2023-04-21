#pragma once
#include<iostream>
#include<string>
#include "Identity.h"
using namespace std;

// Student Class
class Student :public Identity
{
public:
	Student();		// construction
	Student(int id, string name, string pwd);
	virtual void subMenu();
	void applyOrder();		// booking
	void showMyOrder();		// show my applications
	void showAllOrder();	// show all users' applications
	void cancelOrder();		// cancel my applications
protected:
	int s_ID;	// student ID
};
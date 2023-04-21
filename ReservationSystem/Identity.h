#pragma once
#include<iostream>
using namespace std;

// Abstract Class of Identity
class Identity
{
public:
	virtual void subMenu() = 0;		// subMenu
protected:
	string i_name;	// user name
	string i_pwd;	// user's password
};
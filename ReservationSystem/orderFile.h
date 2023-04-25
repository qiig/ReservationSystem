#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include "globalFile.h"
using namespace std;

class OrderFile
{
public:
	OrderFile();
	void updateOrder();		// update
	map<int, map<string, string> > o_orderData;
	int o_size;
protected:
	void insertMapm(string a);
	map<string, string> m;
};
#include "Teacher.h"

Teacher::Teacher()
{

}

Teacher::Teacher(int id, string name, string pwd)
{
	this->t_ID = id;
	this->i_name = name;
	this->i_pwd = pwd;
}

void Teacher::subMenu()
{
	cout << "欢迎教师" << this->i_name << "登录！" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. 所有预约            |\n";
	cout << "\t\t|       2. 审核预约            |\n";
	cout << "\t\t|       0. 注销登录            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "请选择操作代码：";
}

void Teacher::showAllOrder()	// show all applications
{
	OrderFile of;
	if (of.o_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.o_size; i++)
	{
		cout << "学生学号：" << of.o_orderData[i]["stuId"];
		cout << " 学生姓名：" << of.o_orderData[i]["stuName"];
		cout << " 预约日期：周 " << of.o_orderData[i]["date"];
		cout << "   时段  ：" << (of.o_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << "   机房  ：" << of.o_orderData[i]["roomId"];
		string status = "   状态  ：";
		if (of.o_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.o_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.o_orderData[i]["status"] == "-1")
		{
			status += "审核未通过";
		}
		else if (of.o_orderData[i]["status"] == "0")
		{
			status += "预约已取消";
		}
		else
		{
			status += "error ";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Teacher::validOrder()		// check applications
{
	OrderFile of;
	if (of.o_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约：" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.o_size; i++)
	{
		if (of.o_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index++ << "、";
			cout << " 预约日期：周 " << of.o_orderData[i]["date"];
			cout << "   时段  ：" << (of.o_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << "   机房  ：" << of.o_orderData[i]["roomId"];
			string status = "   状态  ：";
			if (of.o_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.o_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			cout << status << endl;
		}
	}
	if (v.size() == 0)
	{
		cout << "无待审核记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入需要操作的记录，0代表返回" << endl;
	int select = 0;
	int res = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核操作：" << endl;
				cout << "| 1 通过 | 2 不通过 |" << endl;
				while (true)
				{
					cin >> res;
					if (res == 1 || res == 2)
					{
						break;
					}
					else
					{
						cout << "错误的操作，请重新输入：" << endl;
					}
				}
				if (res == 1)	// passed
				{
					of.o_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.o_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "操作成功" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	system("pause");
	system("cls");
}

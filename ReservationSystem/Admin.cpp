#include "Admin.h"

void Admin::subMenu()
{
	cout << "欢迎管理员" << this->i_name << "登录！" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. 添加账号            |\n";
	cout << "\t\t|       2. 查看账号            |\n";
	cout << "\t\t|       3. 查看机房            |\n";
	cout << "\t\t|       4. 清空预约            |\n";
	cout << "\t\t|       5. 注销登录            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "请选择操作代码：";
}

void Admin::showPerson()	// show all users' info.
{

}

void Admin::addPerson()	// add new account
{

}

void Admin::showCpRmInfo()	// show computer rooms' informations
{

}

void Admin::clearFile()	// clear booking records
{

}

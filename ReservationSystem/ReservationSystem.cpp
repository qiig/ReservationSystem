#include "ReservationSystem.h"

void showMainMenu();	// main menu
void LoginIn(string FileName, int type);	// sign in
void adminMenu(Identity*& person);		// admin submenu
void studentMenu(Identity*& student);	// student submenu
void teacherMenu(Identity*& teacher);	// teacher submenu
void guessMenu(Guess*& guess);
void quitMain();		// quit main function


int main()
{
	int select = -1;
	while (true)
	{
		showMainMenu();
		cin >> select;

		switch (select)
		{
		case 1:
			// Students
			LoginIn(Stu_F, 1);
			break;
		case 2:
			//Teachers
			LoginIn(Tea_F, 2);
			break;
		case 3:
			// Admin
			LoginIn(Admin_F, 3);
			break;
		case 4:
			// Guess
			LoginIn(Gue_F, 4);
			break;
		case 0:
			quitMain();		// Quit
			break;
		default:
			cout << "请输入正确的操作代码 " << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}

// Main Menu
void showMainMenu()
{
	cout << "\t ------------- 机房预约系统 2023 -------------" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    1. 学  生                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    2. 教  师                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    3. 管理员                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    4. 游  客                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    0. 退  出                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "请选择登录方式：";
}

void adminMenu(Identity*& person)		// admin submenu
{
	while (true)
	{
		person->subMenu();

		Admin* adm = (Admin*)person;
		int select = 0;
		cin >> select;
		
		if (select == 1)	// addPerson
		{
			adm->addPerson();
		}
		else if (select == 2)	// showPerson
		{
			adm->showPerson();
		}
		else if (select == 3)	// showRoom
		{
			adm->showCpRmInfo();
		}
		else if (select == 4)	// clear all records
		{
			adm->clearFile();
		}
		else if (select == 5)	// clear all records
		{
			adm->validNewPerson();
		}
		else if (select == 6)	// clear all records
		{
			adm->deleteCount();
		}
		else if (select == 7) {
			adm->changeAdmPwd();
		}
		else if (select == 0)	// quit
		{
			int a;
			cout << "正在注销，请确认 ... ... " << endl;
			cout << "| 0. 取消退出 | 1. 确认退出 |" << endl;
			cin >> a;
			if (a != 1)
			{
				cout << "已取消注销. " << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "正在注销";
				delete person;
				Sleep(30); cout << " "; Sleep(30); cout << "."; Sleep(25); cout << ".";
				Sleep(20); cout << "."; Sleep(15); cout << " "; Sleep(10); cout << ".";
				Sleep(15); cout << "."; Sleep(20); cout << "."; Sleep(25); cout << " ";
				cout << endl;
				cout << "已注销登录!" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "错误的操作！" << endl;
			system("pause");
			system("cls");
		}
	}
}

void studentMenu(Identity*& student)	// student submenu
{
	while (true)
	{
		student->subMenu();

		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1)	// booking
		{
			stu->applyOrder();
		}
		else if (select == 2)
		{
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			stu->cancelOrder();
		}
		else if (select == 5)
		{
			stu->changePwd();
		}
		else if (select == 0)	// sign out
		{
			int a;
			cout << "正在注销，请确认 ... ... " << endl;
			cout << "| 0. 取消退出 | 1. 确认退出 |" << endl;
			cin >> a;
			if (a != 1)
			{
				cout << "已取消注销. " << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "正在注销";
				delete student;
				Sleep(30); cout << " "; Sleep(30); cout << "."; Sleep(25); cout << ".";
				Sleep(20); cout << "."; Sleep(15); cout << " "; Sleep(10); cout << ".";
				Sleep(15); cout << "."; Sleep(20); cout << "."; Sleep(25); cout << " ";
				cout << endl;
				cout << "已注销登录!" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "错误的操作， 请重新选择：" << endl;
			system("pause");
			system("cls");
		}
	}
}

void teacherMenu(Identity*& teacher)	// teacher submenu
{
	while (true)
	{
		teacher->subMenu();

		Teacher* teac = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1)	// booking
		{
			teac->showAllOrder();
		}
		else if (select == 2)
		{
			teac->validOrder();
		}
		else if (select == 3)
		{
			teac->changePwd();
		}
		else if (select == 0)	// sign out
		{
			int a;
			cout << "正在注销，请确认 ... ... " << endl;
			cout << "| 0. 取消退出 | 1. 确认退出 |" << endl;
			cin >> a;
			if (a != 1)
			{
				cout << "已取消注销. " << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "正在注销";
				delete teacher;
				Sleep(30); cout << " "; Sleep(30); cout << "."; Sleep(25); cout << ".";
				Sleep(20); cout << "."; Sleep(15); cout << " "; Sleep(10); cout << ".";
				Sleep(15); cout << "."; Sleep(20); cout << "."; Sleep(25); cout << " ";
				cout << endl;
				cout << "已注销登录!" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "错误的操作， 请重新选择：" << endl;
			system("pause");
			system("cls");
		}
	}
}

void guessMenu(Guess*& guess) {
	while (true)
	{
		guess->subMenu();

		int select = 0;
		cin >> select;

		if (select == 1)	// addPerson
		{
			guess->applyNewCount();
		}
		else if (select == 2)	// showPerson
		{
			guess->checkStatus();
		}
		else if (select == 0)	// quit
		{
			int a;
			cout << "正在注销，请确认 ... ... " << endl;
			cout << "| 0. 取消退出 | 1. 确认退出 |" << endl;
			cin >> a;
			if (a != 1)
			{
				cout << "已取消注销. " << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "正在注销";
				delete guess;
				Sleep(30); cout << " "; Sleep(30); cout << "."; Sleep(25); cout << ".";
				Sleep(20); cout << "."; Sleep(15); cout << " "; Sleep(10); cout << ".";
				Sleep(15); cout << "."; Sleep(20); cout << "."; Sleep(25); cout << " ";
				cout << endl;
				cout << "已注销登录!" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "错误的操作！" << endl;
			system("pause");
			system("cls");
		}
	}
}

// Sign in
void LoginIn(string FileName, int type)
{
	Identity* person = NULL;

	ifstream ifs;	// read the file
	ifs.open(FileName, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在 " << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}

	int id = 0;
	string name;
	string pwd;		// password

	// check identity
	if (type == 1)	// Student
	{
		cout << "请输入学号：" << endl;
		cin >> id;
	}
	else if (type == 2)		// Teacher
	{
		cout << "请输入工号：" << endl;
		cin >> id;
	}
	else if (type == 3) {
		id = -1;
	}
	else if (type == 4) {
		id = 11;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;
	// cout << "请输入密码：" << endl;
	// cin >> pwd;
	PassWord nPwd(Max_Pwd_Num);
	pwd = nPwd.inputPwd(id);

	int fid;
	string fname, fpwd;
	if (type == 1)		// Student
	{
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (id == fid && fname == name && fpwd == pwd)
			{
				cout << "学生 " << name << " 登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (id == fid && fname == name && fpwd == pwd)
			{
				cout << "教师 " << name << " 登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		while (ifs >> fname && ifs >> fpwd)
		{
			// cout << "临时密码：";
			// cin >> pwd;
			if (fname == name && fpwd == pwd)
			{
				cout << "管理员 " << name << " 登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Admin(name, pwd, Max_Pwd_Num);	// maxPwdNum
				adminMenu(person);
				return;
			}
		}
	}
	else if (type == 4) {
		cout << "游客 " << name << " 登录成功！" << endl;
		// cout << "请牢记账号名与密码以查看申请状态！" << endl;
		system("pause");
		system("cls");
		Guess* guess;
		guess = new Guess(name, pwd);	// maxPwdNum
		guessMenu(guess);
		return;
	}

	cout << "验证失败！" << endl;
	system("pause");
	system("cls");

	return;
}

// Quit
void quitMain()
{
	int a;
	cout << "正在退出系统，请确认 ... ... " << endl;
	cout << "| 0. 取消退出 | 1. 确认退出 |" << endl;
	cin >> a;
	if (a != 1)
	{
		cout << "已取消退出. " << endl;
	}
	else
	{
		cout << "正在退出";
		Sleep(30); cout << " "; Sleep(30); cout << "."; Sleep(25); cout << ".";
		Sleep(20); cout << "."; Sleep(15); cout << " "; Sleep(10); cout << ".";
		Sleep(15); cout << "."; Sleep(20); cout << "."; Sleep(25); cout << " ";
		exit(0);
	}
	system("pause");
	system("cls");
}
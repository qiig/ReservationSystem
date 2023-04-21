#include "ReservationSystem.h"

void showMainMenu();	// main menu
void quitMain();		// quit main function

int main()
{
	int select = 0;
	while (true)
	{
		showMainMenu();
		cin >> select;

		switch (select)
		{
		case 1:
			// Students
			break;
		case 2:
			//Teachers
			break;
		case 3:
			// Admin
			break;
		case 4:
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
	cout << "\t\t|    4. 退  出                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "请选择登录方式：";
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
		Sleep(80); cout << " "; Sleep(80); cout << "."; Sleep(75); cout << ".";
		Sleep(70); cout << "."; Sleep(65); cout << " "; Sleep(60); cout << ".";
		Sleep(65); cout << "."; Sleep(70); cout << "."; Sleep(75); cout << " ";
		exit(0);
	}
	system("pause");
	system("cls");
}
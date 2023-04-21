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
			cout << "��������ȷ�Ĳ������� " << endl;
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
	cout << "\t ------------- ����ԤԼϵͳ 2023 -------------" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    1. ѧ  ��                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    2. ��  ʦ                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    3. ����Ա                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|    4. ��  ��                 |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "��ѡ���¼��ʽ��";
}

// Quit
void quitMain()
{
	int a;
	cout << "�����˳�ϵͳ����ȷ�� ... ... " << endl;
	cout << "| 0. ȡ���˳� | 1. ȷ���˳� |" << endl;
	cin >> a;
	if (a != 1)
	{
		cout << "��ȡ���˳�. " << endl;
	}
	else
	{
		cout << "�����˳�";
		Sleep(80); cout << " "; Sleep(80); cout << "."; Sleep(75); cout << ".";
		Sleep(70); cout << "."; Sleep(65); cout << " "; Sleep(60); cout << ".";
		Sleep(65); cout << "."; Sleep(70); cout << "."; Sleep(75); cout << " ";
		exit(0);
	}
	system("pause");
	system("cls");
}
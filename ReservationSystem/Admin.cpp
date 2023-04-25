#include "Admin.h"

Admin::Admin()
{

}

Admin::Admin(string name, string pwd)
{
	this->i_name = name;
	this->i_pwd = pwd;

	this->initVector();

	ifstream ifs;
	ifs.open(Cpt_F, ios::in);

	ComputerRoom cr;
	while (ifs >> cr.c_RoomID && ifs >> cr.c_MaxCapt)
	{
		vCom.push_back(cr);
	}
	cout << "��ǰ��������Ϊ��" << vCom.size() << endl;

	ifs.close();
}

void Admin::subMenu()
{
	cout << "��ӭ����Ա" << this->i_name << "��¼��" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. ����˺�            |\n";
	cout << "\t\t|       2. �鿴�˺�            |\n";
	cout << "\t\t|       3. �鿴����            |\n";
	cout << "\t\t|       4. ���ԤԼ            |\n";
	cout << "\t\t|       0. ע����¼            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "��ѡ��������룺";
}

void Admin::initVector()	// init vector_student & vector_teacher
{
	vStu.clear();
	vTea.clear();

	ifstream ifs;
	ifs.open(Stu_F, ios::in);
	if (!ifs.is_open())
	{
		cout << "ѧ���ļ������ڣ�" << endl;
		return;
	}

	Student s;
	while (ifs >> s.s_ID && ifs >> s.i_name && ifs >> s.i_pwd)
	{
		vStu.push_back(s);
	}
	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;

	ifs.close();

	ifs.open(Tea_F, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ʦ�ļ������ڣ�" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.t_ID && ifs >> t.i_name && ifs >> t.i_pwd)
	{
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;

	ifs.close();
}

bool Admin::checkRepeatID(int id, int type)	// check repeat ID
{
	if (type == 1)
	{
		vector<Student>::iterator it = vStu.begin();
		for (it; it != vStu.end(); it++)
		{
			if (id == it->s_ID)
			{
				return true;;
			}
		}
	}
	else
	{
		vector<Teacher>::iterator it = vTea.begin();
		for (it; it != vTea.end(); it++)
		{
			if (id == it->t_ID)
			{
				return true;
			}
		}
	}
	return false;
}

void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.s_ID << "\t������" << s.i_name << "\t���룺" << s.i_pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "���ţ�" << t.t_ID << "\t������" << t.i_name << "\t���룺" << t.i_pwd << endl;
}

void Admin::showPerson()	// show all users' info.
{
	int select = 0;
	cout << "��ѡ��Ҫ�鿴�����ݣ�" << endl;
	cout << "| 1 �鿴����ѧ�� | 2 �鿴���н�ʦ |" << endl;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			for_each(vStu.begin(), vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			for_each(vTea.begin(), vTea.end(), printTeacher);
			break;
		}
		else
		{
			cout << "�����ѡ����������룺" << endl;
		}
	}

	system("pause");
	system("cls");
}

void Admin::addPerson()	// add new account
{
	string filename;
	string tip, errtip;
	int select = 0;
	while (true)
	{
		cout << "����������˺ŵ����ͣ�" << endl;
		cout << "| 1 ���ѧ�� | 2 ��ӽ�ʦ |" << endl;
		cin >> select;
		if (select == 1)
		{
			filename = Stu_F;
			tip = "������ѧ�ţ�";
			errtip = "ѧ���ظ������������룺";
			break;
		}
		else if (select == 2)
		{
			filename = Tea_F;
			tip = "�����빤�ţ�";
			errtip = "�����ظ������������룺";
			break;
		}
		else
		{
			cout << "��������ȷ���˺����ͣ�" << endl;
		}
	}

	ofstream ofs;
	ofs.open(filename, ios::out | ios::app);	// write file & add only

	int id;
	string name, pwd;

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool rpt = this->checkRepeatID(id, select);
		if (rpt)	// ID repeated
		{
			cout << errtip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	ofs << endl << id << " " << name << " " << pwd << " ";
	ofs.close();

	if (select == 1)
	{
		Student s;
		s.s_ID = id; s.i_name = name; s.i_pwd = pwd;
		vStu.push_back(s);
	}
	else
	{
		Teacher t;
		t.t_ID = id; t.i_name = name; t.i_pwd = pwd;
		vTea.push_back(t);
	}

	cout << "��ӳɹ���" << endl;

	system("pause");
	system("cls");

	return;
}

void Admin::showCpRmInfo()	// show computer rooms' informations
{
	cout << "������Ϣ��" << endl;
	vector<ComputerRoom>::iterator it = vCom.begin(); 
	for (it; it != vCom.end(); it++)
	{
		cout << it->c_RoomID << " �Ż����������Ϊ��" << it->c_MaxCapt << endl;
	}
	system("pause");
	system("cls");
}

void Admin::clearFile()	// clear booking records
{
	int a;
	cout << "������գ���ȷ�� ... ... " << endl;
	cout << "| 0. ȡ����� | 1. ȷ����� |" << endl;
	cin >> a;
	if (a != 1)
	{
		cout << "��ȡ�����. " << endl;
	}
	else
	{
		cout << "�������";

		ofstream ofs(Ord_F, ios::trunc);
		ofs.close();

		Sleep(30); cout << " "; Sleep(30); cout << "."; Sleep(25); cout << ".";
		Sleep(20); cout << "."; Sleep(15); cout << " "; Sleep(10); cout << ".";
		Sleep(15); cout << "."; Sleep(20); cout << "."; Sleep(25); cout << " ";
		cout << endl;
		cout << "��ճɹ� " << endl;
	}

	system("pause");
	system("cls");
}

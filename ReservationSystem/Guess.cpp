#include "Guess.h"

Guess::Guess()
{

}

Guess::Guess(string name, string pwd) {
	this->g_name = name;
	this->g_pwd = pwd;
	this->maxPwdSize = 50;

	initVector();
}

void Guess::applyNewCount() {
	this->addPerson();
}

void Guess::subMenu() {
	cout << "��ӭ�ο�" << this->g_name << "��¼��" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. �����˺�            |\n";
	cout << "\t\t|       2. �鿴״̬            |\n";
	cout << "\t\t|       0. ע����¼            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "��ѡ��������룺";
}

void Guess::addPerson() {
	string filename;
	string tip, errtip;
	int select = 0;
	while (true)
	{
		cout << "�����������˺ŵ����ͣ�" << endl;
		cout << "| 1 ѧ�� | 2 ��ʦ |" << endl;
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

	ifstream ifs;
	ifs.open(filename, ios::in);	// 

	int id;
	string name, pwd;

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool rpt = this->checkRepeatID(id, select);
		if (id <= 0) {
			cout << "id ��Ϊ������ " << endl;
		}
		else if (rpt)	// ID repeated
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
	// cout << "���������룺" << endl;
	// cin >> pwd;

	// getPwd
	PassWord nPwd(this->maxPwdSize);
	pwd = nPwd.inputPwd(id);

	// 
	ifs.close();

	this->g_select = select;
	this->g_status = 1;
	this->g_id = id;
	this->g_name = name;
	this->g_pwd = pwd;

	ofstream ofs;
	ofs.open(Gue_F, ios::out | ios::app);	// write file & add only
	ofs << endl << g_select << " " << id << " " << name << " " << pwd << " " << this->g_status;
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

	cout << "����ɹ�����ȴ���� ... " << endl;

	system("pause");
	system("cls");

	return;
}

void Guess::checkStatus() {
	cout << "�ݲ�֧�ֲ鿴״̬ " << endl;
	system("pause");
	system("cls");
}

bool Guess::checkRepeatID(int id, int type)	// check repeat ID
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

void Guess::initVector()	// init vector_student & vector_teacher
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
	// cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;

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
	// cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;

	ifs.close();
}
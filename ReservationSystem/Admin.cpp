#include "Admin.h"

Admin::Admin()
{

}

Admin::Admin(string name, string pwd, int n)
{
	this->i_name = name;
	this->i_pwd = pwd;
	this->maxPwdSize = n;

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
	cout << "\t\t|       5. ����˺�            |\n";
	cout << "\t\t|       6. ɾ���˺�            |\n";
	cout << "\t\t|       7. �޸�����            |\n";
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
	cout << "ѧ�ţ�" << s.s_ID << "\t������" << s.i_name << "\t���룺" << "******" << endl;
}

void printTeacher(Teacher& t)
{
	cout << "���ţ�" << t.t_ID << "\t������" << t.i_name << "\t���룺" << "******" << endl;
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

	ofs << endl << id << " " << name << " " << pwd ;
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

void Admin::validNewPerson() {
	vGue.clear();
	ifstream ifs;
	ifs.open(Gue_F, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ο��ļ������ڣ�" << endl;
		return;
	}
	
	Guess g;
	while (ifs >> g.g_select && ifs >> g.g_id && ifs >> g.g_name && ifs >> g.g_pwd && ifs >> g.g_status)
	{
		if (g.g_status == 1) {
			vGue.push_back(g);
		}
	}
	cout << "�������¼��" << endl;
	int cnt = 1;
	vector<Guess>::iterator it = vGue.begin();
	while (it != vGue.end()) {
		g = *it;
		cout << cnt << "��";
		if (g.g_select == 1) {
			cout << "ѧ����";
		}
		else if (g.g_select == 2) {
			cout << "��ʦ��";
		}
		cout << "id: " << g.g_id << " ������" << g.g_name << endl;
		cnt++;
		it++;
	}
	cout << "��ѡ���¼��";
	int a;
	while (true) {
		cin >> a;
		if (a >= 0 && a < vGue.size()+1) {
			break;
		}
		cout << "����ļ�¼�����������룺";
	}
	cout << "�Ƿ�����ע�᣺" << endl;
	cout << "| 1 �� | 2 �� | 0 ȡ�� |" << endl;
	int b;
	while (true) {
		cin >> b;
		if (b >= 0 && b <= 2) {
			break;
		}
		cout << "����Ĳ��������������룺";
	}
	if (a == 0) {
		b = 0;
	}
	ifs.close();
	if (b == 1) {
		string filename;
		string tip, errtip;
		g = vGue[a - 1];
		int select = g.g_select;
		while (true)
		{
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
				break;
			}
		}

		ofstream ofs;
		ofs.open(filename, ios::out | ios::app);	// write file & add only

		ofs << endl << g.g_id << " " << g.g_name << " " << g.g_pwd;
		ofs.close();

		if (select == 1)
		{
			Student s;
			s.s_ID = g.g_id; s.i_name = g.g_name; s.i_pwd = g.g_pwd;
			vStu.push_back(s);
		}
		else if(select == 2)
		{
			Teacher t;
			t.t_ID = g.g_id; t.i_name = g.g_name; t.i_pwd = g.g_pwd;
			vTea.push_back(t);
		}

		ofs.open(Gue_F, ios::out | ios::trunc);
		it = vGue.begin();
		int cnt2 = 1;
		while (it != vGue.end()) {
			g = *it;
			if (cnt2 != a) {
				ofs << endl << g.g_select << " " << g.g_id << " " << g.g_name << " " << g.g_pwd << " " << g.g_status;
			}
			it++; cnt2++;
		}
		ofs.close();

		cout << "��ӳɹ���" << endl;

		system("pause");
		system("cls");

		return;
	}
	else if (b == 2) {
		ofstream ofs;
		ofs.open(Gue_F, ios::out|ios::trunc);
		it = vGue.begin();
		int cnt2 = 1;
		while (it != vGue.end()) {
			g = *it;
			if (cnt2 != a) {
				ofs << endl << g.g_select << " " << g.g_id << " " << g.g_name << " " << g.g_pwd << " " << g.g_status;
			}
			it++; cnt2++;
		}
		ofs.close();
		cout << "�����ɹ� " << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		cout << "������ȡ�� " << endl;
		system("pause");
		system("cls");
		return;
	}

}

void Admin::deleteCount() {
	vector<int> vecid;
	cout << "��ѡ��Ҫɾ�����˺����ͣ� " << endl;
	cout << "| 1 ѧ�� | 2 ��ʦ | 0 ȡ�� |" << endl;
	int a = 0;
	int b = 0;
	int ccnt = 0;
	cin >> a;
	if (a == 1) {
		// student
		vecid.clear();
		cout << "��ɾ���ļ�¼��" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
		cout << "�������ɾ���� id��0 ���� ���������" << endl;
		while (cin >> b && b > 0) {
			vecid.push_back(b);
		}
		vector<int>::iterator iit = vecid.begin();
		vector<Student>::iterator sit = vStu.begin();
		Student stu;
		bool isId = false;

		int id = -1;
		int c = 0;
		string pwd = "";
		cout << "ȷ��ɾ����" << endl;
		cout << "| 1 ȷ�� | 0 ȡ�� |" << endl;
		cin >> c;
		if (c != 1) {
			cout << "��ȡ�� " << endl;
			system("pause");
			system("cls");
			return;
		}
		else {
			cout << "ȷ��ɾ������������ ..." << endl;
			PassWord Pwd(Max_Pwd_Num);
			
			int cnt = 0;
			while (true) {
				if(cnt < 3) pwd = Pwd.inputPwd(id);
				
				if (cnt < 3 && pwd != this->i_pwd) {
					cout << "������󣬻�ʣ " << 2-cnt << " �λ��� ..." << endl;
					cnt++;
				}
				else if (cnt >= 3) {
					cout << "���볢�Դ������࣡" << endl;
					system("pause");
					system("cls");
					return;
				}
				else {
					break;
				}
			}
		}

		ofstream ofs;
		
		ofs.open(Stu_F, ios::out | ios::trunc);
		ccnt = 0;
		while (sit != vStu.end()) {
			stu = *sit;
			isId = false;
			iit = vecid.begin();
			while (iit != vecid.end()) {
				if (*iit == stu.s_ID) {
					isId = true;
					break;
				}
				iit++;
			}
			if (!isId) {
				ofs << endl << stu.s_ID << " " << stu.i_name << " " << stu.i_pwd;
			} else{
				ccnt++;
			}
			sit++;
		}
		ofs.close();
		this->initVector();
		cout << "ɾ���ɹ����ɹ�ɾ�� "  << ccnt << "����ɾ��ʧ�� " << vecid.size() - ccnt << " �� " << endl;
	}
	else if (a == 2) {
		// teacher
		vecid.clear();
		cout << "��ɾ���ļ�¼��" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
		cout << "�������ɾ���� id��0 ���� ���������" << endl;
		while (cin >> b && b > 0) {
			vecid.push_back(b);
		}
		vector<int>::iterator iit = vecid.begin();
		vector<Teacher>::iterator sit = vTea.begin();
		Teacher stu;
		bool isId = false;
		int id = -1;
		int c = 0;
		string pwd = "";
		cout << "ȷ��ɾ����" << endl;
		cout << "| 1 ȷ�� | 0 ȡ�� |" << endl;
		cin >> c;
		if (c != 1) {
			cout << "��ȡ�� " << endl;
			system("pause");
			system("cls");
			return;
		}
		else {
			cout << "ȷ��ɾ������������ ..." << endl;
			PassWord Pwd(Max_Pwd_Num);

			int cnt = 0;
			while (true) {
				if (cnt < 3) pwd = Pwd.inputPwd(id);

				if (cnt < 3 && pwd != this->i_pwd) {
					cout << "������󣬻�ʣ " << 2 - cnt << " �λ��� ..." << endl;
					cnt++;
				}
				else if (cnt >= 3) {
					cout << "���볢�Դ������࣡" << endl;
					system("pause");
					system("cls");
					return;
				}
				else {
					break;
				}
			}
		}

		ofstream ofs;
		ccnt = 0;
		ofs.open(Tea_F, ios::out | ios::trunc);
		while (sit != vTea.end()) {
			stu = *sit;
			isId = false;
			iit = vecid.begin();
			while (iit != vecid.end()) {
				if (*iit == stu.t_ID) {
					isId = true;
					break;
				}
				iit++;
			}
			if (!isId) {
				ofs << endl << stu.t_ID << " " << stu.i_name << " " << stu.i_pwd;
			}
			else {
				ccnt++;
			}
			sit++;
		}
		ofs.close();
		this->initVector();
		cout << "ɾ���ɹ����ɹ�ɾ�� " << ccnt << "����ɾ��ʧ�� " << vecid.size() - ccnt << " �� " << endl;
	}
	else {
		// cancel
		cout << "ȡ���ɹ� " << endl;
		system("pause");
		system("cls");

		return;
	}
	system("pause");
	system("cls");
}

void Admin::changeAdmPwd() {
	// admin id == 0
	int id = 0, fid = 0;
	string fname, fpwd;
	string name, pwd;

	ifstream ifs;
	ifs.open(Admin_F, ios::in);
	ofstream ofs;

	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		return;
	}

		id = -1;
		cout << "�������˻�����" << endl;
		cin >> name;
		PassWord nPwd(Max_Pwd_Num);
		pwd = nPwd.inputPwd(id);
		while (ifs >> fname && ifs >> fpwd)
		{
			// cout << "��ʱ���룺";
			// cin >> pwd;
			if (fname == name && fpwd == pwd)
			{
				cout << "������֤�ɹ�������� " << endl;
				Admin person;
				cout << "�����������ƣ�" << endl;
				cin >> person.i_name;
				cout << "���������������룺" << endl;
				while (true) {
					person.i_pwd = nPwd.inputPwd(id);
					pwd = nPwd.inputPwd(id);
					if (person.i_pwd == pwd) {
						break;
					}
					else {
						cout << "������������벻һ�£����������� ... " << endl;
					}
				}

				ifs.close();
				ofs.open(Admin_F, ios::out | ios::trunc);
				ofs << endl << person.i_name << " " << person.i_pwd;
				ofs.close();
				cout << "�����޸ĳɹ���" << endl;
				system("pause");
				system("cls");
				return;
			}
		}

		cout << "��֤ʧ�ܣ�" << endl;
		system("pause");
		system("cls");
		return;
}

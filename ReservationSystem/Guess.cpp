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
	cout << "欢迎游客" << this->g_name << "登录！" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. 申请账号            |\n";
	cout << "\t\t|       2. 查看状态            |\n";
	cout << "\t\t|       0. 注销登录            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "请选择操作代码：";
}

void Guess::addPerson() {
	string filename;
	string tip, errtip;
	int select = 0;
	while (true)
	{
		cout << "请输入申请账号的类型：" << endl;
		cout << "| 1 学生 | 2 教师 |" << endl;
		cin >> select;
		if (select == 1)
		{
			filename = Stu_F;
			tip = "请输入学号：";
			errtip = "学号重复，请重新输入：";
			break;
		}
		else if (select == 2)
		{
			filename = Tea_F;
			tip = "请输入工号：";
			errtip = "工号重复，请重新输入：";
			break;
		}
		else
		{
			cout << "请输入正确的账号类型！" << endl;
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
			cout << "id 须为正整数 " << endl;
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

	cout << "请输入姓名：" << endl;
	cin >> name;
	// cout << "请输入密码：" << endl;
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

	cout << "申请成功，请等待审核 ... " << endl;

	system("pause");
	system("cls");

	return;
}

void Guess::checkStatus() {
	cout << "暂不支持查看状态 " << endl;
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
		cout << "学生文件不存在！" << endl;
		return;
	}

	Student s;
	while (ifs >> s.s_ID && ifs >> s.i_name && ifs >> s.i_pwd)
	{
		vStu.push_back(s);
	}
	// cout << "当前学生人数为：" << vStu.size() << endl;

	ifs.close();

	ifs.open(Tea_F, ios::in);
	if (!ifs.is_open())
	{
		cout << "教师文件不存在！" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.t_ID && ifs >> t.i_name && ifs >> t.i_pwd)
	{
		vTea.push_back(t);
	}
	// cout << "当前教师人数为：" << vTea.size() << endl;

	ifs.close();
}
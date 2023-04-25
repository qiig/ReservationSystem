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
	cout << "当前机房数量为：" << vCom.size() << endl;

	ifs.close();
}

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
	cout << "\t\t|       0. 注销登录            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "请选择操作代码：";
}

void Admin::initVector()	// init vector_student & vector_teacher
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
	cout << "当前学生人数为：" << vStu.size() << endl;

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
	cout << "当前教师人数为：" << vTea.size() << endl;

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
	cout << "学号：" << s.s_ID << "\t姓名：" << s.i_name << "\t密码：" << s.i_pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "工号：" << t.t_ID << "\t姓名：" << t.i_name << "\t密码：" << t.i_pwd << endl;
}

void Admin::showPerson()	// show all users' info.
{
	int select = 0;
	cout << "请选择要查看的内容：" << endl;
	cout << "| 1 查看所有学生 | 2 查看所有教师 |" << endl;

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
			cout << "错误的选项，请重新输入：" << endl;
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
		cout << "请输入添加账号的类型：" << endl;
		cout << "| 1 添加学生 | 2 添加教师 |" << endl;
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

	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
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

	cout << "添加成功！" << endl;

	system("pause");
	system("cls");

	return;
}

void Admin::showCpRmInfo()	// show computer rooms' informations
{
	cout << "机房信息：" << endl;
	vector<ComputerRoom>::iterator it = vCom.begin(); 
	for (it; it != vCom.end(); it++)
	{
		cout << it->c_RoomID << " 号机房最大容量为：" << it->c_MaxCapt << endl;
	}
	system("pause");
	system("cls");
}

void Admin::clearFile()	// clear booking records
{
	int a;
	cout << "正在清空，请确认 ... ... " << endl;
	cout << "| 0. 取消清空 | 1. 确认清空 |" << endl;
	cin >> a;
	if (a != 1)
	{
		cout << "已取消清空. " << endl;
	}
	else
	{
		cout << "正在清空";

		ofstream ofs(Ord_F, ios::trunc);
		ofs.close();

		Sleep(30); cout << " "; Sleep(30); cout << "."; Sleep(25); cout << ".";
		Sleep(20); cout << "."; Sleep(15); cout << " "; Sleep(10); cout << ".";
		Sleep(15); cout << "."; Sleep(20); cout << "."; Sleep(25); cout << " ";
		cout << endl;
		cout << "清空成功 " << endl;
	}

	system("pause");
	system("cls");
}

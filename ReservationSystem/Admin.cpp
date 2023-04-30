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
	cout << "\t\t|       5. 审核账号            |\n";
	cout << "\t\t|       6. 删除账号            |\n";
	cout << "\t\t|       7. 修改密码            |\n";
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
	cout << "学号：" << s.s_ID << "\t姓名：" << s.i_name << "\t密码：" << "******" << endl;
}

void printTeacher(Teacher& t)
{
	cout << "工号：" << t.t_ID << "\t姓名：" << t.i_name << "\t密码：" << "******" << endl;
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

void Admin::validNewPerson() {
	vGue.clear();
	ifstream ifs;
	ifs.open(Gue_F, ios::in);
	if (!ifs.is_open())
	{
		cout << "游客文件不存在！" << endl;
		return;
	}
	
	Guess g;
	while (ifs >> g.g_select && ifs >> g.g_id && ifs >> g.g_name && ifs >> g.g_pwd && ifs >> g.g_status)
	{
		if (g.g_status == 1) {
			vGue.push_back(g);
		}
	}
	cout << "待处理记录：" << endl;
	int cnt = 1;
	vector<Guess>::iterator it = vGue.begin();
	while (it != vGue.end()) {
		g = *it;
		cout << cnt << "、";
		if (g.g_select == 1) {
			cout << "学生：";
		}
		else if (g.g_select == 2) {
			cout << "教师：";
		}
		cout << "id: " << g.g_id << " 姓名：" << g.g_name << endl;
		cnt++;
		it++;
	}
	cout << "请选择记录：";
	int a;
	while (true) {
		cin >> a;
		if (a >= 0 && a < vGue.size()+1) {
			break;
		}
		cout << "错误的记录，请重新输入：";
	}
	cout << "是否允许注册：" << endl;
	cout << "| 1 是 | 2 否 | 0 取消 |" << endl;
	int b;
	while (true) {
		cin >> b;
		if (b >= 0 && b <= 2) {
			break;
		}
		cout << "错误的操作，请重新输入：";
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

		cout << "添加成功！" << endl;

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
		cout << "操作成功 " << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		cout << "操作已取消 " << endl;
		system("pause");
		system("cls");
		return;
	}

}

void Admin::deleteCount() {
	vector<int> vecid;
	cout << "请选择要删除的账号类型： " << endl;
	cout << "| 1 学生 | 2 教师 | 0 取消 |" << endl;
	int a = 0;
	int b = 0;
	int ccnt = 0;
	cin >> a;
	if (a == 1) {
		// student
		vecid.clear();
		cout << "可删除的记录：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
		cout << "请输入待删除的 id，0 代表 输入结束：" << endl;
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
		cout << "确认删除：" << endl;
		cout << "| 1 确认 | 0 取消 |" << endl;
		cin >> c;
		if (c != 1) {
			cout << "已取消 " << endl;
			system("pause");
			system("cls");
			return;
		}
		else {
			cout << "确认删除请输入密码 ..." << endl;
			PassWord Pwd(Max_Pwd_Num);
			
			int cnt = 0;
			while (true) {
				if(cnt < 3) pwd = Pwd.inputPwd(id);
				
				if (cnt < 3 && pwd != this->i_pwd) {
					cout << "密码错误，还剩 " << 2-cnt << " 次机会 ..." << endl;
					cnt++;
				}
				else if (cnt >= 3) {
					cout << "密码尝试次数过多！" << endl;
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
		cout << "删除成功：成功删除 "  << ccnt << "个，删除失败 " << vecid.size() - ccnt << " 个 " << endl;
	}
	else if (a == 2) {
		// teacher
		vecid.clear();
		cout << "可删除的记录：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
		cout << "请输入待删除的 id，0 代表 输入结束：" << endl;
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
		cout << "确认删除：" << endl;
		cout << "| 1 确认 | 0 取消 |" << endl;
		cin >> c;
		if (c != 1) {
			cout << "已取消 " << endl;
			system("pause");
			system("cls");
			return;
		}
		else {
			cout << "确认删除请输入密码 ..." << endl;
			PassWord Pwd(Max_Pwd_Num);

			int cnt = 0;
			while (true) {
				if (cnt < 3) pwd = Pwd.inputPwd(id);

				if (cnt < 3 && pwd != this->i_pwd) {
					cout << "密码错误，还剩 " << 2 - cnt << " 次机会 ..." << endl;
					cnt++;
				}
				else if (cnt >= 3) {
					cout << "密码尝试次数过多！" << endl;
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
		cout << "删除成功：成功删除 " << ccnt << "个，删除失败 " << vecid.size() - ccnt << " 个 " << endl;
	}
	else {
		// cancel
		cout << "取消成功 " << endl;
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
		cout << "文件不存在！" << endl;
		return;
	}

		id = -1;
		cout << "请输入账户名：" << endl;
		cin >> name;
		PassWord nPwd(Max_Pwd_Num);
		pwd = nPwd.inputPwd(id);
		while (ifs >> fname && ifs >> fpwd)
		{
			// cout << "临时密码：";
			// cin >> pwd;
			if (fname == name && fpwd == pwd)
			{
				cout << "密码验证成功，请继续 " << endl;
				Admin person;
				cout << "请输入新名称：" << endl;
				cin >> person.i_name;
				cout << "请输入两次新密码：" << endl;
				while (true) {
					person.i_pwd = nPwd.inputPwd(id);
					pwd = nPwd.inputPwd(id);
					if (person.i_pwd == pwd) {
						break;
					}
					else {
						cout << "两次输入的密码不一致，请重新输入 ... " << endl;
					}
				}

				ifs.close();
				ofs.open(Admin_F, ios::out | ios::trunc);
				ofs << endl << person.i_name << " " << person.i_pwd;
				ofs.close();
				cout << "密码修改成功！" << endl;
				system("pause");
				system("cls");
				return;
			}
		}

		cout << "验证失败！" << endl;
		system("pause");
		system("cls");
		return;
}

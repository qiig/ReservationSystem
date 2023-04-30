#include "Student.h"

Student::Student()		// construction
{

}

Student::Student(int id, string name, string pwd)
{
	this->s_ID = id;
	this->i_name = name;
	this->i_pwd = pwd;

	ifstream ifs;
	ifs.open(Cpt_F, ios::in);

	ComputerRoom cr;
	while (ifs >> cr.c_RoomID && ifs >> cr.c_MaxCapt)
	{
		vCom.push_back(cr);
	}

	ifs.close();
}

void Student::subMenu()
{
	cout << "欢迎学生" << this->i_name << "登录！" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. 申请预约            |\n";
	cout << "\t\t|       2. 我的预约            |\n";
	cout << "\t\t|       3. 所有预约            |\n";
	cout << "\t\t|       4. 取消预约            |\n";
	cout << "\t\t|       5. 修改密码            |\n";
	cout << "\t\t|       0. 注销登录            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "请选择操作代码：";
}

void Student::applyOrder()		// booking
{
	cout << "开放时间：周一至周五" << endl;
	cout << "请选择申请预约的时间：" << endl;
	cout << "| 代码 | 时间 |" << endl;
	cout << "|   1  | 周一 |" << endl;
	cout << "|   2  | 周二 |" << endl;
	cout << "|   3  | 周三 |" << endl;
	cout << "|   4  | 周四 |" << endl;
	cout << "|   5  | 周五 |" << endl;

	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}

	cout << "请输入申请预约的时间：" << endl;
	cout << "| 1 上午 | 2 下午 |" << endl;

	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}

	cout << "请选择机房：" << endl;
	cout << "| 机房 | " << setfill(' ') << setw(10) << "最大容量 |" << endl;
	cout << "|   1  | " << setfill(' ') << setw(8) << vCom[0].c_MaxCapt << " |" << endl;
	cout << "|   2  | " << setfill(' ') << setw(8) << vCom[1].c_MaxCapt << " |" << endl;
	cout << "|   3  | " << setfill(' ') << setw(8) << vCom[2].c_MaxCapt << " |" << endl;

	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	cout << "预约成功，审核中 ... " << endl;

	ofstream ofs(Ord_F, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->s_ID << " ";
	ofs << "stuName:" << this->i_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;	// in review
	ofs.close();

	system("pause");
	system("cls");
}

void Student::showMyOrder()		// show my applications
{
	OrderFile of;
	if (of.o_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	int cnt = 0;
	for (int i = 0; i < of.o_size; i++)
	{
		if (atoi(of.o_orderData[i]["stuId"].c_str()) == this->s_ID)
		{
			cout << " 预约日期：周 " << of.o_orderData[i]["date"];
			cout << "   时段  ：" << (of.o_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << "   机房  ：" << of.o_orderData[i]["roomId"];
			string status = "   状态  ：";
			if (of.o_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.o_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.o_orderData[i]["status"] == "-1")
			{
				status += "审核未通过";
			}
			else if (of.o_orderData[i]["status"] == "0")
			{
				status += "预约已取消";
			}
			else
			{
				status += "error ";
			}
			cout << status << endl;
			cnt++;
		}
	}
	if (cnt == 0)
	{
		cout << "无预约记录" << endl;
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()	// show all users' applications
{
	OrderFile of;
	if (of.o_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.o_size; i++)
	{
		cout << "学生学号：" << of.o_orderData[i]["stuId"];
		cout << " 学生姓名：" << of.o_orderData[i]["stuName"];
		cout << " 预约日期：周 " << of.o_orderData[i]["date"];
		cout << "   时段  ：" << (of.o_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << "   机房  ：" << of.o_orderData[i]["roomId"];
		string status = "   状态  ：";
		if (of.o_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.o_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.o_orderData[i]["status"] == "-1")
		{
			status += "审核未通过";
		}
		else if (of.o_orderData[i]["status"] == "0")
		{
			status += "预约已取消";
		}
		else
		{
			status += "error ";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Student::cancelOrder()		// cancel my applications
{
	OrderFile of;
	if (of.o_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中 或 预约成功的记录可以取消，请输入要取消的记录" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.o_size; i++)
	{
		if (atoi(of.o_orderData[i]["stuId"].c_str()) == this->s_ID)
		{
			if (of.o_orderData[i]["status"] == "1" || of.o_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << " 预约日期：周 " << of.o_orderData[i]["date"];
				cout << "   时段  ：" << (of.o_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << "   机房  ：" << of.o_orderData[i]["roomId"];
				string status = "   状态  ：";
				if (of.o_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.o_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入需要取消的记录，0代表返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.o_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	system("pause");
	system("cls");
}

#if 1
void Student::changePwd() {
	// admin id == 0
	int id = 0, fid = 0;
	string fname, fpwd;
	string name, pwd;

	ifstream ifs;
	ifs.open(Stu_F, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		return;
	}

		// input vec
		Student person;
		vector<Student> vec;
		
		while (ifs >> person.s_ID && ifs >> person.i_name && ifs >> person.i_pwd) {
			vec.push_back(person);
		}
		ifs.close();
		// begin
		// cout << "请输入要修改的 id：" << endl;
		// cin >> id;
		id = this->s_ID;
		PassWord nPwd(Max_Pwd_Num);
		cout << "请输入要修改的用户名：" << endl;
		cin >> name;
		pwd = nPwd.inputPwd(id);
		vector<Student>::iterator it = vec.begin();
		while (it != vec.end())
		{
			person = *it;
			if (id == person.s_ID && name == person.i_name && person.i_pwd == pwd)
			{
				cout << "学生密码验证成功，请继续" << endl;
				cout << "请输入新名称：" << endl;
				cin >> name;
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
				ofstream ofs;
				ofs.open(Stu_F, ios::out | ios::trunc);
				while (it != vec.end()) {
					person = *it;
					if (person.s_ID == id) {
						ofs << endl << person.s_ID << " " << name << " " << pwd;
					}
					else {
						ofs << endl << person.s_ID << " " << person.i_name << " " << person.i_pwd;
					}
					it++;
				}

				ofs.close();
				cout << "密码修改成功！" << endl;
				system("pause");
				system("cls");
				vec.clear();
				return;
			}
			it++;
		}
		cout << "验证失败！" << endl;
		system("pause");
		system("cls");
		return;
}
#endif
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
	cout << "��ӭѧ��" << this->i_name << "��¼��" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. ����ԤԼ            |\n";
	cout << "\t\t|       2. �ҵ�ԤԼ            |\n";
	cout << "\t\t|       3. ����ԤԼ            |\n";
	cout << "\t\t|       4. ȡ��ԤԼ            |\n";
	cout << "\t\t|       5. �޸�����            |\n";
	cout << "\t\t|       0. ע����¼            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "��ѡ��������룺";
}

void Student::applyOrder()		// booking
{
	cout << "����ʱ�䣺��һ������" << endl;
	cout << "��ѡ������ԤԼ��ʱ�䣺" << endl;
	cout << "| ���� | ʱ�� |" << endl;
	cout << "|   1  | ��һ |" << endl;
	cout << "|   2  | �ܶ� |" << endl;
	cout << "|   3  | ���� |" << endl;
	cout << "|   4  | ���� |" << endl;
	cout << "|   5  | ���� |" << endl;

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
		cout << "�����������������룺" << endl;
	}

	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "| 1 ���� | 2 ���� |" << endl;

	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	cout << "��ѡ�������" << endl;
	cout << "| ���� | " << setfill(' ') << setw(10) << "������� |" << endl;
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
		cout << "�����������������룺" << endl;
	}
	cout << "ԤԼ�ɹ�������� ... " << endl;

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
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	int cnt = 0;
	for (int i = 0; i < of.o_size; i++)
	{
		if (atoi(of.o_orderData[i]["stuId"].c_str()) == this->s_ID)
		{
			cout << " ԤԼ���ڣ��� " << of.o_orderData[i]["date"];
			cout << "   ʱ��  ��" << (of.o_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << "   ����  ��" << of.o_orderData[i]["roomId"];
			string status = "   ״̬  ��";
			if (of.o_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.o_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.o_orderData[i]["status"] == "-1")
			{
				status += "���δͨ��";
			}
			else if (of.o_orderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
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
		cout << "��ԤԼ��¼" << endl;
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()	// show all users' applications
{
	OrderFile of;
	if (of.o_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.o_size; i++)
	{
		cout << "ѧ��ѧ�ţ�" << of.o_orderData[i]["stuId"];
		cout << " ѧ��������" << of.o_orderData[i]["stuName"];
		cout << " ԤԼ���ڣ��� " << of.o_orderData[i]["date"];
		cout << "   ʱ��  ��" << (of.o_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << "   ����  ��" << of.o_orderData[i]["roomId"];
		string status = "   ״̬  ��";
		if (of.o_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.o_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.o_orderData[i]["status"] == "-1")
		{
			status += "���δͨ��";
		}
		else if (of.o_orderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
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
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����� �� ԤԼ�ɹ��ļ�¼����ȡ����������Ҫȡ���ļ�¼" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.o_size; i++)
	{
		if (atoi(of.o_orderData[i]["stuId"].c_str()) == this->s_ID)
		{
			if (of.o_orderData[i]["status"] == "1" || of.o_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";
				cout << " ԤԼ���ڣ��� " << of.o_orderData[i]["date"];
				cout << "   ʱ��  ��" << (of.o_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << "   ����  ��" << of.o_orderData[i]["roomId"];
				string status = "   ״̬  ��";
				if (of.o_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.o_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}
	cout << "��������Ҫȡ���ļ�¼��0������" << endl;
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
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "�����������������룺" << endl;
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
		cout << "�ļ������ڣ�" << endl;
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
		// cout << "������Ҫ�޸ĵ� id��" << endl;
		// cin >> id;
		id = this->s_ID;
		PassWord nPwd(Max_Pwd_Num);
		cout << "������Ҫ�޸ĵ��û�����" << endl;
		cin >> name;
		pwd = nPwd.inputPwd(id);
		vector<Student>::iterator it = vec.begin();
		while (it != vec.end())
		{
			person = *it;
			if (id == person.s_ID && name == person.i_name && person.i_pwd == pwd)
			{
				cout << "ѧ��������֤�ɹ��������" << endl;
				cout << "�����������ƣ�" << endl;
				cin >> name;
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
				cout << "�����޸ĳɹ���" << endl;
				system("pause");
				system("cls");
				vec.clear();
				return;
			}
			it++;
		}
		cout << "��֤ʧ�ܣ�" << endl;
		system("pause");
		system("cls");
		return;
}
#endif
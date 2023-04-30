#include "Teacher.h"

Teacher::Teacher()
{

}

Teacher::Teacher(int id, string name, string pwd)
{
	this->t_ID = id;
	this->i_name = name;
	this->i_pwd = pwd;
}

void Teacher::subMenu()
{
	cout << "��ӭ��ʦ" << this->i_name << "��¼��" << endl;
	cout << endl;
	cout << "\t\t*------------------------------*\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|       1. ����ԤԼ            |\n";
	cout << "\t\t|       2. ���ԤԼ            |\n";
	cout << "\t\t|       3. �޸�����            |\n";
	cout << "\t\t|       0. ע����¼            |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t*------------------------------*\n";
	cout << endl << "��ѡ��������룺";
}

void Teacher::showAllOrder()	// show all applications
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

void Teacher::validOrder()		// check applications
{
	OrderFile of;
	if (of.o_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˵�ԤԼ��" << endl;

	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.o_size; i++)
	{
		if (of.o_orderData[i]["status"] == "1")
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
	if (v.size() == 0)
	{
		cout << "�޴���˼�¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��������Ҫ�����ļ�¼��0������" << endl;
	int select = 0;
	int res = 0;
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
				cout << "��������˲�����" << endl;
				cout << "| 1 ͨ�� | 2 ��ͨ�� |" << endl;
				while (true)
				{
					cin >> res;
					if (res == 1 || res == 2)
					{
						break;
					}
					else
					{
						cout << "����Ĳ��������������룺" << endl;
					}
				}
				if (res == 1)	// passed
				{
					of.o_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.o_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "�����ɹ�" << endl;
				break;
			}
		}
		cout << "�����������������룺" << endl;
	}
	system("pause");
	system("cls");
}

#if 1
void Teacher::changePwd() {
	// admin id == 0
	int id = 0, fid = 0;
	string fname, fpwd;
	string name, pwd;


	ifstream ifs;
	ifs.open(Tea_F, ios::in);
	

	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		return;
	}

	Teacher person;
	vector<Teacher> vec;
	
	while (ifs >> person.t_ID && ifs >> person.i_name && ifs >> person.i_pwd) {
		vec.push_back(person);
	}
	ifs.close();
	
	// begin
	// cout << "������Ҫ�޸ĵ� id��" << endl;
	// cin >> id;
	id = this->t_ID;
	PassWord nPwd(Max_Pwd_Num);
	cout << "������Ҫ�޸ĵ��û�����" << endl;
	cin >> name;
	pwd = nPwd.inputPwd(id);
	vector<Teacher>::iterator it = vec.begin();
	while (it != vec.end())
	{
		person = *it;
		if (id ==  person.t_ID && person.i_name == name && person.i_pwd == pwd)
		{
			cout << "��ʦ������֤�ɹ��������" << endl;
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
			ofs.open(Tea_F, ios::out | ios::trunc);
			while (it != vec.end()) {
				person = *it;
				if (person.t_ID == id) {
					ofs << endl << person.t_ID << " " << name << " " << pwd;
				}
				else {
					ofs << endl << person.t_ID << " " << person.i_name << " " << person.i_pwd;
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
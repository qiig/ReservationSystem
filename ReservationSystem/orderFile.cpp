#include "orderFile.h"

OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(Ord_F, ios::in);

	string date, interval, stuId, stuName, roomId, status;

	this->o_size = 0;

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
#if 0
		string key, val;

		int pos = date.find(":");
		if (pos != -1)
		{
			key = date.substr(0, pos);
			val = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, val));
		}

		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			val = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, val));
		}

		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			val = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, val));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			val = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, val));
		}

		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			val = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, val));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			val = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, val));
		}
#endif
#if 1
		m.clear();
		insertMapm(date);
		insertMapm(interval);
		insertMapm(stuId);
		insertMapm(stuName);
		insertMapm(roomId);
		insertMapm(status);
#endif
		this->o_orderData.insert(make_pair(this->o_size, m));
		this->o_size++;
	}
}

void OrderFile::insertMapm(string a)
{
	int pos = -1;
	string key, val;
	pos = a.find(":");
	if (pos != -1)
	{
		key = a.substr(0, pos);
		val = a.substr(pos + 1, a.size() - pos - 1);
		m.insert(make_pair(key, val));
	}
}

void OrderFile::updateOrder()		// update
{
	if (this->o_size == 0)
	{
		return;
	}

	ofstream ofs(Ord_F, ios::out | ios::trunc);
	for (int i = 0; i < this->o_size; i++)
	{
		ofs << "date:" << this->o_orderData[i]["date"] << " ";
		ofs << "interval:" << this->o_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->o_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->o_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->o_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->o_orderData[i]["status"] << endl;
	}
	ofs.close();
}
#include "passWord.h"

PassWord::PassWord(int n) {
    this->msize = n;
}

string PassWord::inputPwd(int id) {
    char c;
    int count = 0;
    char* password = new char[this->msize];
    cout << "请输入密码：" << endl;
    while ((c = _getch()) != '\r') {
        if (c == 8) {
            // backspace
            if (count == 0) {
                continue;
            }
            putchar('\b');
            putchar(' ');
            putchar('\b');
            count--;
        }
        if (count == this->msize - 1) {
            continue;
        }
        if (c >= 33 && c <= 126) {
            putchar('*');
            password[count] = c;
            count++;
        }
    }
    password[count] = '\0';
    this->str = password;
    delete[] password;
    cout << endl;
    return getPwd(id, str);
}

string PassWord::getPwd(int n, string s) {
    // n == -1
    string rrs = "$j*)6L%S;w2'x-i9se3+c{@f";
    if (n == -1) {
        string ssa = "";
        string ssb = "";
        for (int i = 0; i < s.length(); i++) {
            if (i % 3 == 0) {
                ssa += s[i];
            }
            else if (i % 3 == 1) {
                ssb += rrs[i % rrs.length()];
            }
            else {
                ssa += s[i];
            }
        }
        s = ssb + ssa;
        n = 14;
    }
    string nPwd = "";
    // transfer digit to ab
    int nr = 0;
    int len = s.length();
    // begin
    for (int i = 0; i < len; i++) {
        if (s[i] >= 48 && s[i] <= 57) {
            if (i % 3 == 0) {
                s[i] = s[i] - 14;
            }
            else if (i % 3 == 1) {
                s[i] = s[i] - 12;
            }
            else {
                s[i] = s[i] - 13;
            }
        }
        else if (s[i] >= 'a' && s[i] <= 'z') {
            if (i % 3 == 0) {
                s[i] = s[i] - 3;
            }
            else if (i % 3 == 1) {
                s[i] = s[i] + 2;
            }
            else {
                s[i] = s[i] - 2;
            }
        }
    }
    for (int i = 0; i < len; i++) {
        if (s[i] <= 35) {
            s[i] = s[i] + 42;
        }
        else if (s[i] >= 126) {
            s[i] = s[i] - 4;
        }
    }
    // end
    // len in [1,5]
    if (len >= 1 && len <= 5) {
        nr = 2 + n % 2;
    }
    else if (len >= 6 && len <= 8) {
        nr = len / 2 - n % (len / 2 - 1);
    }
    else if (len >= 9 && len <= 23) {
        nr = len / 3 - n % (len / 3 - 1);
    }
    else {
        nr = 4 + n % 3;
    }
    nPwd += convert(s, nr);
    nPwd += convert(s, n % 3 + 1);
    // new
    string nsa = "", nsb = "", nsc = "";
    for (int i = 0; i < nPwd.length(); i++) {
        if (i % 3 == 0) {
            nsa += rrs[i % rrs.length()];
        }
        else if (i % 3 == 1) {
            nsb += nPwd[i];
        }
        else {
            nsc += nPwd[i];
        }
    }
    nPwd = nsc + nsb + nsa;
    return nPwd;
}

string PassWord::convert(string s, int numRows) {
    // only a row
    if (numRows == 1) {
        int nnr = numRows + 1;
        return convert(s, nnr);
    }
    // len equal or less than numRows
    int len = s.length();
    if (len <= numRows) {
        string nns = s;
        nns += s;
        return convert(nns, numRows);
    }
    // normal status
    string ns = "";
    vector<int> nr;
    int nnr, c, cl;
    c = len / (2 * numRows - 2);
    cl = len % (2 * numRows - 2);
    // get len.s of each rows
    for (int i = 0; i < numRows; i++) {
        if (i == 0 || i == numRows - 1) {
            nnr = c;
            if (cl > 0) {
                nnr++; cl--;
            }
        }
        else {
            nnr = 2 * c;
            if (cl > 0 && i == 1) {
                nnr++; cl--;
            }
            else if (cl > 0 && i > 1 && i < numRows - 1) {
                if (cl == 2 * (numRows - i - 1) + 1) {
                    nnr += 2; cl -= 2;
                }
                else {
                    nnr++; cl--;
                }
            }
        }
        nr.push_back(nnr);
    }
    // get new string
    int cnt = 0;
    int ind1, ind2, pnum, nnum;
    pnum = 2 * numRows - 2;
    vector<int>::iterator it = nr.begin();
    while (it != nr.end() && cnt < numRows) {
        // front & rear
        if (cnt == 0 || cnt == numRows - 1) {
            for (int i = 0; i < *it; i++) {
                ind1 = cnt + i * pnum;
                ns += s[ind1];
            }
        }
        else {
            // ind2 - ind1 is nnum
            nnum = (numRows - cnt - 1) * 2;
            for (int i = 0; i < *it / 2; i++) {
                ind1 = cnt + i * pnum;
                ind2 = ind1 + nnum;
                ns += s[ind1]; ns += s[ind2];
            }
            if (*it % 2 == 1) {  // odd
                ind1 = cnt + pnum * (*it / 2);
                ns += s[ind1];
            }
        }
        // next row
        it++; cnt++;
    }
    // clear vector
    nr.clear();
    return ns;
}

#if 0
void PassWord::changePassWord(string type) {
    // admin id == 0
    int id = 0, fid = 0;
    string fname, fpwd;
    string name, pwd;
    string FileName = "";
    if (type == "Admin") {
        FileName = "Admin_F";
    }
    else if (type == "Student") {
        FileName = "Stu_F";
    }
    else if (type == "Teacher") {
        FileName = "Tea_F";
    }
    else {
        cout << "错误的类型 " << endl;
        system("pause");
        system("cls");
        return;
    }

    ifstream ifs;
    ifs.open(FileName, ios::in);
    ofstream ofs;

    if (!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        return;
    }

    if (type == "Admin") {
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
                    person.i_pwd = inputPwd(id);
                    pwd = inputPwd(id);
                    if (person.i_pwd == pwd) {
                        break;
                    }
                    else {
                        cout << "两次输入的密码不一致，请重新输入 ... " << endl;
                    }
                }
                
                ifs.close();
                ofs.open(FileName, ios::out | ios::trunc);
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
    else if (type == "Student") {
        // input vec
        Student person;
        vector<Student> vec;
        vector<Student>::iterator it = vec.begin();
        while (ifs >> person.s_ID && ifs >> person.i_name && ifs >> person.i_pwd) {
            vec.push_back(person);
        }
        // begin
        cout << "请输入要修改的 id：" << endl;
        cin >> id;
        cout << "请输入要修改的用户名：" << endl;
        cin >> name;
        pwd = inputPwd(id);
        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {
            if (id == fid && fname == name && fpwd == pwd)
            {
                cout << "学生密码验证成功，请继续" << endl;
                cout << "请输入新名称：" << endl;
                cin >> name;
                cout << "请输入两次新密码：" << endl;
                while (true) {
                    person.i_pwd = inputPwd(id);
                    pwd = inputPwd(id);
                    if (person.i_pwd == pwd) {
                        break;
                    }
                    else {
                        cout << "两次输入的密码不一致，请重新输入 ... " << endl;
                    }
                }
                ifs.close();
                ofs.open(FileName, ios::out | ios::trunc);
                while (it != vec.end()) {
                    person = *it;
                    if (person.s_ID == id) {
                        ofs << endl << person.s_ID << " " << name << " " << pwd;
                    }
                    else {
                        ofs << endl << person.s_ID << " " << person.i_name << " " << person.i_pwd;
                    }
                }

                ofs.close();
                cout << "密码修改成功！" << endl;
                system("pause");
                system("cls");
                vec.clear();
                return;
            }
        }
        cout << "验证失败！" << endl;
        system("pause");
        system("cls");
        return; 
    }
    else if (type == "Teacher") {
        Teacher person;
        vector<Teacher> vec;
        vector<Teacher>::iterator it = vec.begin();
        while (ifs >> person.t_ID && ifs >> person.i_name && ifs >> person.i_pwd) {
            vec.push_back(person);
        }
        // begin
        cout << "请输入要修改的 id：" << endl;
        cin >> id;
        cout << "请输入要修改的用户名：" << endl;
        cin >> name;
        pwd = inputPwd(id);
        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {
            if (id == fid && fname == name && fpwd == pwd)
            {
                cout << "教师密码验证成功，请继续" << endl;
                cout << "请输入新名称：" << endl;
                cin >> name;
                cout << "请输入两次新密码：" << endl;
                while (true) {
                    person.i_pwd = inputPwd(id);
                    pwd = inputPwd(id);
                    if (person.i_pwd == pwd) {
                        break;
                    }
                    else {
                        cout << "两次输入的密码不一致，请重新输入 ... " << endl;
                    }
                }
                ifs.close();
                ofs.open(FileName, ios::out | ios::trunc);
                while (it != vec.end()) {
                    person = *it;
                    if (person.t_ID == id) {
                        ofs << endl << person.t_ID << " " << name << " " << pwd;
                    }
                    else {
                        ofs << endl << person.t_ID << " " << person.i_name << " " << person.i_pwd;
                    }
                }

                ofs.close();
                cout << "密码修改成功！" << endl;
                system("pause");
                system("cls");
                vec.clear();
                return;
            }
        }
        cout << "验证失败！" << endl;
        system("pause");
        system("cls");
        return;
    }
}
#endif
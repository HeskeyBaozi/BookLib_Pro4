#include "baseSystem.h"
#define PATH "./file/"
using namespace std;

baseSystem::baseSystem()
{
	cout << "\n============ ���, ��ӭʹ�� ============" << endl;
	ifstream fin_book, fin_user;
	string path = PATH;
	fin_book.open(path + "Books-f.json", ios::in);
	fin_user.open(path + "Users-f.json", ios::in);
	if (fin_book&&fin_user)
	{
		Json::Reader reader;

		string str_Books, str_Users;
		getline(fin_book, str_Books, '\n');
		getline(fin_user, str_Users, '\n');

		Json::Value BooksObj, UsersObj;
		reader.parse(str_Books, BooksObj);
		reader.parse(str_Users, UsersObj);

		load(BooksObj, UsersObj);		
	}
	fin_book.close();
	fin_user.close();
}


baseSystem::~baseSystem()
{
	save();
}

void baseSystem::Login()
{
	cout << "�����������û�ID: (����ԱΪ:admin)" << endl;
	string userID = getInput();
	while (userDataBase.find(userID) == userDataBase.end())
	{
		cout << "[��ʾ]�û���������, ����������!" << endl;
		userID = getInput();
	}
	const User& thisUser = userDataBase.at(userID);
	cout << "����������: " << endl;
	string password = getInput();
	while (toPassWord(password) != thisUser.getBadPassword())
	{
		cout << "[��ʾ]�Բ���, �����������, ����������!" << endl;
		password = getInput();
	}
	this->Current_User_ID = userID;
	cout << "[�ɹ���½] ��ӭ, " << userDataBase.at(Current_User_ID).getUserName() << endl;
}

void baseSystem::Register()
{
	cout << "��ӭע��" << endl;
	cout << "����������ID(������ѧ��): " << endl;
	string myUserID = getInput();
	cout << "�������û���: " << endl;
	string myUserName = getInput();

	string password_1 = "1", password_2 = "2";
	while(password_1 != password_2)
	{
		cout << "����������: " << endl;
		password_1 = getInput();
		cout << "���ٴ�����һ������: " << endl;
		password_2 = getInput();
		if (password_1 != password_2)
		{
			cout << "[��ʾ]�Բ���, �����������벻һ��, ����������" << endl;
		}
	}
	cout << "��ȷ��������Ϣ:" << endl;
	cout << "ID: " << myUserID << endl;
	cout << "�û���: " << myUserName << endl;
	cout << "����λ��: " << password_1.size() << " λ" << endl;
	cout << "\n������Ϣ���ȷ��������[ok], �����������������" << endl;
	string check = getInput();
	if (check == "ok")
	{
		User newUser(myUserID, myUserName, password_1);
		userDataBase.emplace(newUser.getUserID(), newUser);
		cout << "[��ʾ]�ѳɹ�������û�: " << myUserName << endl;
	}
	cout << "[��ʾ]: ���ѷ���ע�����!" << endl;
}

string baseSystem::getInput(string message)
{
	cout << message << ">>> ";
	string result;
	getline(cin, result, '\n');
	return result;
}

void baseSystem::switchor()
{
	cout << "����������: " << endl;
	cout << "    log  = ��½" << endl;
	cout << "    reg  = ע��" << endl;
	cout << "    quit = �˳�" << endl;
	string myChoice = getInput();
	if (myChoice == "log")
	{
		Login();
		return;
	}
	if (myChoice == "reg")
	{
		Register();
	}
	if (myChoice == "quit")return;
}

Json::Value baseSystem::toJson_Books() const
{
	Json::Value LibObj;
	for (const pair<string, _Book>& item : Lib)
	{
		LibObj[item.first] = item.second.toJson();
	}
	return LibObj;
}

Json::Value baseSystem::toJson_Users() const
{
	Json::Value UsersObj;
	for (const pair<string, User>& item : userDataBase)
	{
		UsersObj[item.first] = item.second.toJson();
	}
	return UsersObj;
}

void baseSystem::load(const Json::Value& Books, const Json::Value& Users)
{
	for (const auto& Book_Obj : Books)
	{
		Lib.emplace(Book_Obj["ISBN"].asString(), _Book(Book_Obj));
	}
	for (const auto& User_Obj : Users)
	{
		userDataBase.emplace(User_Obj["UserID"].asString(), User(User_Obj));
	}
}

void baseSystem::save() const
{
	ofstream fout_book, fout_user;
	string path = PATH;

	fout_book.open(path + "Books-f.json", ios::out);
	fout_user.open(path + "Users-f.json", ios::out);
	if (fout_book&&fout_user)
	{
		Json::FastWriter writer;
		fout_book << writer.write(toJson_Books());
		fout_user << writer.write(toJson_Users());
	}
	fout_book.close();
	fout_user.close();

	fout_book.open(path + "Books-sty.json", ios::out);
	fout_user.open(path + "Users-sty.json", ios::out);
	if(fout_book)
	{
		Json::StyledWriter writer;
		fout_book << writer.write(toJson_Books());
		fout_user << writer.write(toJson_Users());
	}
	fout_book.close();
	fout_user.close();
}

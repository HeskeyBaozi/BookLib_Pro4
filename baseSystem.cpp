#include "baseSystem.h"
#define PATH "./file/"
using namespace std;

baseSystem::baseSystem()
{
	cout << "\n============ 你好, 欢迎使用 ============" << endl;
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
	cout << "请输入您的用户ID: (管理员为:admin)" << endl;
	string userID = getInput();
	while (userDataBase.find(userID) == userDataBase.end())
	{
		cout << "[提示]用户名不存在, 请重新输入!" << endl;
		userID = getInput();
	}
	const User& thisUser = userDataBase.at(userID);
	cout << "请输入密码: " << endl;
	string password = getInput();
	while (toPassWord(password) != thisUser.getBadPassword())
	{
		cout << "[提示]对不起, 密码输入错误, 请重新输入!" << endl;
		password = getInput();
	}
	this->Current_User_ID = userID;
	cout << "[成功登陆] 欢迎, " << userDataBase.at(Current_User_ID).getUserName() << endl;
}

void baseSystem::Register()
{
	cout << "欢迎注册" << endl;
	cout << "请输入您的ID(可以是学号): " << endl;
	string myUserID = getInput();
	cout << "请输入用户名: " << endl;
	string myUserName = getInput();

	string password_1 = "1", password_2 = "2";
	while(password_1 != password_2)
	{
		cout << "请输入密码: " << endl;
		password_1 = getInput();
		cout << "请再次输入一次密码: " << endl;
		password_2 = getInput();
		if (password_1 != password_2)
		{
			cout << "[提示]对不起, 两次密码输入不一致, 请重新输入" << endl;
		}
	}
	cout << "请确认您的信息:" << endl;
	cout << "ID: " << myUserID << endl;
	cout << "用户名: " << myUserName << endl;
	cout << "密码位数: " << password_1.size() << " 位" << endl;
	cout << "\n以上信息如果确认请输入[ok], 输入其他任意键放弃" << endl;
	string check = getInput();
	if (check == "ok")
	{
		User newUser(myUserID, myUserName, password_1);
		userDataBase.emplace(newUser.getUserID(), newUser);
		cout << "[提示]已成功添加新用户: " << myUserName << endl;
	}
	cout << "[提示]: 您已放弃注册操作!" << endl;
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
	cout << "您可以输入: " << endl;
	cout << "    log  = 登陆" << endl;
	cout << "    reg  = 注册" << endl;
	cout << "    quit = 退出" << endl;
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

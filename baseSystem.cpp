#include "baseSystem.h"
#include <ctime>
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
		cout << "[提示] 用户名不存在, 请重新输入!" << endl;
		userID = getInput();
	}
	const User& thisUser = userDataBase.at(userID);
	cout << "请输入密码: " << endl;
	string password = getInput();
	while (toPassWord(password) != thisUser.getBadPassword())
	{
		cout << "[提示] 对不起, 密码输入错误, 请重新输入!" << endl;
		password = getInput();
	}
	this->Current_User_ID = userID;
	cout << "[成功登陆] 欢迎, " << userDataBase.at(Current_User_ID).getUserName() << endl;
}

void baseSystem::afterLogin()
{
	bool isAdmin = Current_User_ID == "admin";
	string toDo;
	if(!isAdmin)
	{
		while (toDo != "0")
		{
			cout << "请问您要做什么?" << endl;
			cout << "[1] 借书\n";
			cout << "[2] 还书\n";
			cout << "[3] 查看图书信息\n";
			cout << "[4] 查看用户信息\n";
			cout << "[0] 我什么都不想做, 退出系统" << endl;
			toDo = getInput();
			while (!(toDo.front() >= '0'&&toDo.front() <= '4'))
			{
				cerr << "[提示] 输入有误, 请重新输入!" << endl;
				toDo = getInput();
			}
			/* 借书 */
			if (toDo == "1")
			{
				cout << "现在藏有以下的书:" << endl;
				cout << toJson_Books().toStyledString() << endl;

				cout << "请输入要借的书的ISBN:" << endl;
				string myISBN = getInput();

				cout << "这是您要借的书的信息吗?(ok确认)" << endl;
				cout << Lib[myISBN].toJson().toStyledString() << endl;
				string check = getInput();
				if (check == "ok")
				{
					_Book& thisBook = Lib[myISBN];

					cout << "请输入要借的书的数量:" << endl;
					string amount = getInput();
					int num = amount.front() - '0';
					thisBook.setCurrentAmount(thisBook.getCurrentAmount() - num);

					const auto myTime = time(nullptr);
					string tString = ctime(&myTime);
					_Record newRecord(this->Current_User_ID, tString, string("30 days"));

					thisBook._recordArray.push_back(newRecord);
					cout << "[成功提示] 你成功借了 " << thisBook.getBookName() << ' ' << num << " 本" << endl;
					cout << "现在这本书的状态是:" << endl;
					cout << thisBook.toJson().toStyledString() << endl;
				}
			}

			/* 还书 */
			if (toDo == "2")
			{
				cout << "我现在已经借的书有:" << endl;
				cout << userDataBase[Current_User_ID].toJson()["HasBorrowed"].toStyledString() << endl;
				cout << "请输入要还书的ISBN编号:" << endl;
				string myISBN = getInput();
				auto& thisBook = Lib[myISBN];
				cout << thisBook.getBookName() << " 可以还 " << thisBook.getMaxAmount() - thisBook.getCurrentAmount() << " 本, 请输入要还的数量:" << endl;
				string amount = getInput();
				int num = amount.front() - '0';
				thisBook.setCurrentAmount(thisBook.getCurrentAmount() + num);
				cout << "[成功提示] 成功还书" << endl;
				cout << "现在书的状态:" << endl;
				cout << thisBook.toJson().toStyledString() << endl;
			}

			/* 查看用户信息 */
			if (toDo == "4")
				displayUserInfo();

			/* 查看图书信息 */
			if (toDo == "3")
				cout << toJson_Books().toStyledString() << endl;
		}

	}else
	{
		while (toDo != "0")
		{
			cout << "你好, 管理员! 请问您要做什么?" << endl;
			cout << "[1] 查看所有图书信息\n";
			cout << "[2] 查看所有用户信息\n";
			cout << "[3] 增加书\n";
			cout << "[4] 删除书\n";
			cout << "[0] 我什么都不想做, 退出系统" << endl;
			toDo = getInput();
			if (toDo.empty())
				toDo = getInput();
			while (!(toDo.front() >= '0'&&toDo.front() <= '4'))
			{
				cerr << "[提示] 输入有误, 请重新输入!" << endl;
				toDo = getInput();
			}
			/* 查看所有用户信息 */
			if (toDo == "2")
				cout << toJson_Users().toStyledString() << endl;

			/* 增加书 */
			if (toDo == "3")
			{
				_Book newBook = createBook();
				Lib.emplace(newBook.getISBN(), newBook);
				cout << "[成功提示] 成功加入了 " 
					<< newBook.getBookName() << " " 
					<< newBook.getMaxAmount() << " 本" << endl;
			}

			/* 查看所有书的信息 */
			if (toDo == "1")
				cout << toJson_Books().toStyledString() << endl;

			if (toDo == "4")
			{
				cout << toJson_Books().toStyledString() << endl;
				cout << "请输入要删除的书的ISBN:" << endl;
				string myISBN = getInput();
				Lib.erase(myISBN);
				cout << "[提示] 成功删除, 现在的状态:" << endl;
				cout << toJson_Books().toStyledString() << endl;
			}

		}

	}

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
			cout << "[提示] 对不起, 两次密码输入不一致, 请重新输入" << endl;
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
		cout << "[提示] 已成功添加新用户: " << myUserName << endl;
	}
	else
		cout << "[提示] 您已放弃注册操作!" << endl;
}

string baseSystem::getInput(string message)
{
	cin.clear();
	//cin.ignore();
	cout << message << ">>> ";
	string result;
	getline(cin, result, '\n');
	return result;
}

void baseSystem::displayFunction()
{
	cout << "您可以输入: " << endl;
	cout << "    log  = 登陆" << endl;
	cout << "    reg  = 注册" << endl;
	cout << "    quit = 退出" << endl;
}

void baseSystem::displayUserInfo() const
{
	try
	{
		if (userDataBase.find(Current_User_ID) == userDataBase.end())
			throw runtime_error("您没有登陆或者ID是不合法的");
		cout << userDataBase.at(Current_User_ID).toJson().toStyledString();
	}
	catch (runtime_error ex)
	{
		cerr << "[严重错误] " << ex.what() << endl;
	}
}

_Book baseSystem::createBook() const
{
	cout << "请输入书的ISBN编号:" << endl;
	string myISBN = getInput();
	if (Lib.find(myISBN) != Lib.end())
	{
		cerr << "[提示] 对不起, 编号重复了, 请重新输入" << endl;
		myISBN = getInput();
	}
	cout << "请输入书名:" << endl;
	string myBookName = getInput();
	cout << "请输入作者: " << endl;
	string myAuthor = getInput();
	cout << "请输入出版社名字: " << endl;
	string myPublishingHouse = getInput();
	cout << "请输入书本数量：\n>>> ";
	int Amount = 0;
	cin >> Amount;
	_Book newBook(myBookName, myISBN, myAuthor, myPublishingHouse, Amount);
	return newBook;
}

void baseSystem::switchor()
{
	displayFunction();
	string myChoice = getInput();
	if (myChoice == "log")
	{
		Login();
		afterLogin();
		return;
	}
	if (myChoice == "reg")
	{
		Register();
		return;
	}
	if (myChoice == "quit")
		return;
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

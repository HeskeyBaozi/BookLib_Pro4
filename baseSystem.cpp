#include "baseSystem.h"
#include <ctime>
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
		cout << "[��ʾ] �û���������, ����������!" << endl;
		userID = getInput();
	}
	const User& thisUser = userDataBase.at(userID);
	cout << "����������: " << endl;
	string password = getInput();
	while (toPassWord(password) != thisUser.getBadPassword())
	{
		cout << "[��ʾ] �Բ���, �����������, ����������!" << endl;
		password = getInput();
	}
	this->Current_User_ID = userID;
	cout << "[�ɹ���½] ��ӭ, " << userDataBase.at(Current_User_ID).getUserName() << endl;
}

void baseSystem::afterLogin()
{
	bool isAdmin = Current_User_ID == "admin";
	string toDo;
	if(!isAdmin)
	{
		while (toDo != "0")
		{
			cout << "������Ҫ��ʲô?" << endl;
			cout << "[1] ����\n";
			cout << "[2] ����\n";
			cout << "[3] �鿴ͼ����Ϣ\n";
			cout << "[4] �鿴�û���Ϣ\n";
			cout << "[0] ��ʲô��������, �˳�ϵͳ" << endl;
			toDo = getInput();
			while (!(toDo.front() >= '0'&&toDo.front() <= '4'))
			{
				cerr << "[��ʾ] ��������, ����������!" << endl;
				toDo = getInput();
			}
			/* ���� */
			if (toDo == "1")
			{
				cout << "���ڲ������µ���:" << endl;
				cout << toJson_Books().toStyledString() << endl;

				cout << "������Ҫ������ISBN:" << endl;
				string myISBN = getInput();

				cout << "������Ҫ��������Ϣ��?(okȷ��)" << endl;
				cout << Lib[myISBN].toJson().toStyledString() << endl;
				string check = getInput();
				if (check == "ok")
				{
					_Book& thisBook = Lib[myISBN];

					cout << "������Ҫ����������:" << endl;
					string amount = getInput();
					int num = amount.front() - '0';
					thisBook.setCurrentAmount(thisBook.getCurrentAmount() - num);

					const auto myTime = time(nullptr);
					string tString = ctime(&myTime);
					_Record newRecord(this->Current_User_ID, tString, string("30 days"));

					thisBook._recordArray.push_back(newRecord);
					cout << "[�ɹ���ʾ] ��ɹ����� " << thisBook.getBookName() << ' ' << num << " ��" << endl;
					cout << "�����Ȿ���״̬��:" << endl;
					cout << thisBook.toJson().toStyledString() << endl;
				}
			}

			/* ���� */
			if (toDo == "2")
			{
				cout << "�������Ѿ��������:" << endl;
				cout << userDataBase[Current_User_ID].toJson()["HasBorrowed"].toStyledString() << endl;
				cout << "������Ҫ�����ISBN���:" << endl;
				string myISBN = getInput();
				auto& thisBook = Lib[myISBN];
				cout << thisBook.getBookName() << " ���Ի� " << thisBook.getMaxAmount() - thisBook.getCurrentAmount() << " ��, ������Ҫ��������:" << endl;
				string amount = getInput();
				int num = amount.front() - '0';
				thisBook.setCurrentAmount(thisBook.getCurrentAmount() + num);
				cout << "[�ɹ���ʾ] �ɹ�����" << endl;
				cout << "�������״̬:" << endl;
				cout << thisBook.toJson().toStyledString() << endl;
			}

			/* �鿴�û���Ϣ */
			if (toDo == "4")
				displayUserInfo();

			/* �鿴ͼ����Ϣ */
			if (toDo == "3")
				cout << toJson_Books().toStyledString() << endl;
		}

	}else
	{
		while (toDo != "0")
		{
			cout << "���, ����Ա! ������Ҫ��ʲô?" << endl;
			cout << "[1] �鿴����ͼ����Ϣ\n";
			cout << "[2] �鿴�����û���Ϣ\n";
			cout << "[3] ������\n";
			cout << "[4] ɾ����\n";
			cout << "[0] ��ʲô��������, �˳�ϵͳ" << endl;
			toDo = getInput();
			if (toDo.empty())
				toDo = getInput();
			while (!(toDo.front() >= '0'&&toDo.front() <= '4'))
			{
				cerr << "[��ʾ] ��������, ����������!" << endl;
				toDo = getInput();
			}
			/* �鿴�����û���Ϣ */
			if (toDo == "2")
				cout << toJson_Users().toStyledString() << endl;

			/* ������ */
			if (toDo == "3")
			{
				_Book newBook = createBook();
				Lib.emplace(newBook.getISBN(), newBook);
				cout << "[�ɹ���ʾ] �ɹ������� " 
					<< newBook.getBookName() << " " 
					<< newBook.getMaxAmount() << " ��" << endl;
			}

			/* �鿴���������Ϣ */
			if (toDo == "1")
				cout << toJson_Books().toStyledString() << endl;

			if (toDo == "4")
			{
				cout << toJson_Books().toStyledString() << endl;
				cout << "������Ҫɾ�������ISBN:" << endl;
				string myISBN = getInput();
				Lib.erase(myISBN);
				cout << "[��ʾ] �ɹ�ɾ��, ���ڵ�״̬:" << endl;
				cout << toJson_Books().toStyledString() << endl;
			}

		}

	}

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
			cout << "[��ʾ] �Բ���, �����������벻һ��, ����������" << endl;
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
		cout << "[��ʾ] �ѳɹ�������û�: " << myUserName << endl;
	}
	else
		cout << "[��ʾ] ���ѷ���ע�����!" << endl;
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
	cout << "����������: " << endl;
	cout << "    log  = ��½" << endl;
	cout << "    reg  = ע��" << endl;
	cout << "    quit = �˳�" << endl;
}

void baseSystem::displayUserInfo() const
{
	try
	{
		if (userDataBase.find(Current_User_ID) == userDataBase.end())
			throw runtime_error("��û�е�½����ID�ǲ��Ϸ���");
		cout << userDataBase.at(Current_User_ID).toJson().toStyledString();
	}
	catch (runtime_error ex)
	{
		cerr << "[���ش���] " << ex.what() << endl;
	}
}

_Book baseSystem::createBook() const
{
	cout << "���������ISBN���:" << endl;
	string myISBN = getInput();
	if (Lib.find(myISBN) != Lib.end())
	{
		cerr << "[��ʾ] �Բ���, ����ظ���, ����������" << endl;
		myISBN = getInput();
	}
	cout << "����������:" << endl;
	string myBookName = getInput();
	cout << "����������: " << endl;
	string myAuthor = getInput();
	cout << "���������������: " << endl;
	string myPublishingHouse = getInput();
	cout << "�������鱾������\n>>> ";
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

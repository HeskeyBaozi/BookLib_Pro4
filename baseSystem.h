#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include "./json/json.h"
#include "_Book.h"
#include "User.h"

class baseSystem
{
public:
	baseSystem();
	~baseSystem();
	
	/* ��½ */
	void Login();
	void afterLogin();

	/* ע�� */
	void Register();

	/* ��ת�� */
	void switchor();
protected:
	std::map<std::string, _Book> Lib;
	Json::Value toJson_Books() const;

	std::map<std::string, User> userDataBase;
	Json::Value toJson_Users() const;
private:
	void load(const Json::Value& Books, const Json::Value& Users);
	void save()const;

	/* IO */
	static std::string getInput(std::string message = "");
	static void displayFunction();
	void displayUserInfo() const;
	
	/* ����ʹ�����ϵͳ���û�ID */
	std::string Current_User_ID;

	/* �鼮��� */
	_Book createBook() const;
};


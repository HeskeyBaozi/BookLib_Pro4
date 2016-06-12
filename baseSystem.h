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
	
	/* 登陆 */
	void Login();
	void afterLogin();

	/* 注册 */
	void Register();

	/* 跳转器 */
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
	
	/* 正在使用这个系统的用户ID */
	std::string Current_User_ID;

	/* 书籍相关 */
	_Book createBook() const;
};


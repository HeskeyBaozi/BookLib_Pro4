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
	/* 保存图书 */
	std::map<std::string, _Book> Lib;
	Json::Value toJson_Books() const;

	/* 用户图书 */
	std::map<std::string, User> userDataBase;
	Json::Value toJson_Users() const;
private:
	/* 文件加载与储存 */
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


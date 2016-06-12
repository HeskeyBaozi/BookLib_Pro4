#pragma once
#include <string>
#include <vector>
#include "json/json.h"

class User
{
public:
	explicit User(const Json::Value& User_Obj);
	User(const std::string& myUserID = "None",
		const std::string& myUserName = "None",
		const std::string& myPassWord = "None");
	~User();

	Json::Value toJson() const;
	std::string getUserID() const;
	std::string getUserName() const;
	std::string getBadPassword() const;
private:
	std::string userID;
	std::string userName;
	std::string password;
	std::vector<std::string> hasBorrowed;
};

std::string toPassWord(const std::string& NoEncodeString);


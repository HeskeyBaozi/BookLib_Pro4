#pragma once
#include <string>

#include "json/json.h"

class User
{
public:
	explicit User(const Json::Value& User_Obj);
	User(const std::string& myUserID, const std::string& myUserName, const std::string& myPassWord);
	~User();

	Json::Value toJson() const;
	std::string getUserID() const;
	std::string getUserName() const;
	std::string getBadPassword() const;
private:
	std::string userID;
	std::string userName;
	std::string password;
};

std::string toPassWord(const std::string& NoEncodeString);


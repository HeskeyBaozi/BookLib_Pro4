#include "User.h"
#define PassWordKey 8
using namespace std;

User::User(const Json::Value& UserObj)
{
	userID = UserObj["UserID"].asString();
	userName = UserObj["UserName"].asString();
	password = UserObj["PassWord"].asString();
}

User::User(const string& myUserID, const string& myUserName, const string& myPassWord)
	:userID(myUserID), userName(myUserName)
{
	password = toPassWord(myPassWord);
}

User::~User()
{
}

Json::Value User::toJson() const
{
	Json::Value UserObj;
	UserObj["UserID"] = Json::Value(userID);
	UserObj["UserName"] = Json::Value(userName);
	UserObj["PassWord"] = Json::Value(password);
	return UserObj;
}

string User::getUserID() const
{
	return userID;
}

std::string User::getUserName() const
{
	return userName;
}

std::string User::getBadPassword() const
{
	return password;
}

string toPassWord(const string& NoEncodeString)
{
	string Encoded(NoEncodeString);
	for (char& ch : Encoded)
	{
		ch ^= PassWordKey;
	}
	return Encoded;
}

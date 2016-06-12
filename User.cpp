#include "User.h"
#define PassWordKey 8
using namespace std;

User::User(const Json::Value& UserObj)
{
	userID = UserObj["UserID"].asString();
	userName = UserObj["UserName"].asString();
	password = UserObj["PassWord"].asString();
	Json::Value ISBNarray = UserObj["HasBorrowed"];
	for(const auto& ISBNObj:ISBNarray)
	{
		hasBorrowed.push_back(ISBNObj.asString());
	}
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
	Json::Value UserObj = Json::objectValue;
	UserObj["UserID"] = Json::Value(userID);
	UserObj["UserName"] = Json::Value(userName);
	UserObj["PassWord"] = Json::Value(password);
	UserObj["HasBorrowed"] = Json::arrayValue;
	for (const string& ISBN : hasBorrowed)
	{
		UserObj["HasBorrowed"].append(Json::Value(ISBN));	
	}
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

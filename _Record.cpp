#include "_Record.h"
using namespace std;

_Record::_Record(const Json::Value& json_Record)
{
	this->__record["KeeperID"] = json_Record["KeeperID"];
	this->__record["BorrowTime"] = json_Record["BorrowTime"];
	this->__record["TimeLimit"] = json_Record["TimeLimit"];
}

_Record::_Record(const string& KeeperID, const string& BorrowTime, const string& TimeLimit)
{
	Json::Value Obj;
	Obj["KeeperID"] = Json::Value(KeeperID);
	Obj["BorrowTime"] = Json::Value(BorrowTime);
	Obj["TimeLimit"] = Json::Value(TimeLimit);
	__record = Obj;
}

string _Record::getKeeperID() const
{
	return __record["KeeperID"].asString();
}

string _Record::getBorrowTime() const
{
	return __record["BorrowTime"].asString();
}

int _Record::getTimeLimit() const
{
	return __record["TimeLimit"].asInt();
}

Json::Value _Record::toJson() const
{
	return __record;
}

#pragma once
#include <string>
#include "./json/json.h"
class _Record
{
public:
	explicit _Record(const Json::Value& json_Record);
	explicit _Record(const std::string& KeeperID, const std::string& BorrowTime, const std::string& TimeLimit);
	std::string getKeeperID() const;
	std::string getBorrowTime() const;
	int getTimeLimit() const;
	Json::Value toJson() const;
private:
	Json::Value __record;
};


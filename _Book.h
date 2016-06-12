#pragma once
#include "_Record.h"
#include <string>
class _Book
{
	/*
	* Book Obj:
	*    BookName 书名
	*    ISBN 书的编号
	*    PublishHouse 出版社
	*    Records 书借阅记录集合
	*/
public:
	explicit _Book(const Json::Value& Book_Obj);
	~_Book();

	std::string getISBN() const;
	Json::Value toJson() const;
private:
	std::string bookName;
	std::string ISBN;
	std::string author;
	std::string publishingHouse;
	std::vector<_Record> _recordArray;
};



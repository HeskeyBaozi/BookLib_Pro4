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
	*    MaxAmount 书的最大容量
	*    CurrentAmount 书的当前数量
	*/
public:
	explicit _Book(const Json::Value& Book_Obj);
	_Book(const std::string& myBookName = "None", 
		const std::string& myISBN = "None",
		const std::string& myAuthor = "None",
		const std::string& myPublishHouse = "None",
		int Amount = 0);
	~_Book();

	std::string getISBN() const;
	std::string getBookName() const;
	int getMaxAmount() const;
	int getCurrentAmount() const;
	Json::Value toJson() const;
	bool isOnShelf() const;
	void setCurrentAmount(const int newAmount);

	std::vector<_Record> _recordArray;
private:
	std::string bookName;
	std::string ISBN;
	std::string author;
	std::string publishingHouse;
	int maxAmount;
	int currentAmount;
};



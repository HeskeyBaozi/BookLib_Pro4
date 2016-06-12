#pragma once
#include "_Record.h"
#include <string>
class _Book
{
	/*
	* Book Obj:
	*    BookName ����
	*    ISBN ��ı��
	*    PublishHouse ������
	*    Records ����ļ�¼����
	*    MaxAmount ����������
	*    CurrentAmount ��ĵ�ǰ����
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



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
	~_Book();

	std::string getISBN() const;
	Json::Value toJson() const;
	bool isOnShelf() const;
private:
	std::string bookName;
	std::string ISBN;
	std::string author;
	std::string publishingHouse;
	int maxAmount;
	int currentAmount;
	std::vector<_Record> _recordArray;
};



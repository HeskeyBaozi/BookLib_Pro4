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



#include "_Book.h"
#include <iostream>
using namespace std;


_Book::_Book(const Json::Value& Book_Obj)
{
	bookName = Book_Obj["BookName"].asString();
	ISBN = Book_Obj["ISBN"].asString();
	publishingHouse = Book_Obj["PublishHouse"].asString();
	maxAmount = Book_Obj["MaxAmount"].asInt();
	currentAmount = Book_Obj["CurrentAmount"].asInt();
	const Json::Value& Record_Set = Book_Obj["Records"];
	for (const auto& ele : Record_Set)
	{
		_recordArray.push_back(_Record(ele));
	}
}

_Book::_Book(const string& myBookName, 
	const string& myISBN, 
	const string& myAuthor, 
	const string& myPublishHouse,
	int Amount)
	: bookName(myBookName),
	ISBN(myISBN),
	author(myAuthor),
	publishingHouse(myPublishHouse),
	maxAmount(Amount),
	currentAmount(Amount)
{
}

_Book::~_Book()
{
}

string _Book::getISBN() const
{
	return ISBN;
}

string _Book::getBookName() const
{
	return bookName;
}

int _Book::getMaxAmount() const
{
	return maxAmount;
}

int _Book::getCurrentAmount() const
{
	return currentAmount;
}

Json::Value _Book::toJson() const
{
	Json::Value Book_Obj;
	Book_Obj["BookName"] = Json::Value(bookName).asString();
	Book_Obj["ISBN"] = Json::Value(ISBN).asString();
	Book_Obj["Author"] = Json::Value(author).asString();
	Book_Obj["PublishingHouse"] = Json::Value(publishingHouse).asString();
	Book_Obj["MaxAmount"] = maxAmount;
	Book_Obj["CurrentAmount"] = currentAmount;

	Json::Value Records_in_Total;
	for (const _Record& item : _recordArray)
	{
		Records_in_Total.append(item.toJson());
	}
	Book_Obj["Records"] = Records_in_Total;
	return Book_Obj;
}

bool _Book::isOnShelf() const
{
	if (currentAmount == 0)return false;
	return true;
}

void _Book::setCurrentAmount(const int newAmount)
{
	currentAmount = newAmount >= 0 ? newAmount : 0;
}

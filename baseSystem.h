#pragma once
#include <iostream>
#include <map>
#include "./json/json.h"
#include "Book.h"

class baseSystem
{
public:
	baseSystem();
	~baseSystem();

	static void Greeting();
protected:
	std::map<std::string, Book> Lib;
private:
	void load();
	void save()const;
};

